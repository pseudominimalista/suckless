#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* OpenBSD pledge(2) */
#ifdef __OpenBSD__
#include <unistd.h>
#else
#define pledge(p1,p2) 0
#endif

/* This is the blocksize of my disk, use atleast an equal or higher value and
  a multiple of 2 for better performance ((struct stat).st_blksize). */
#define READ_BUF_SIZ 16384
#define LEN(s)     (sizeof(s)/sizeof(*s))

enum { BlockHeader = 0, BlockItem, BlockFooter, BlockLast };

struct variable {
	char *key, *value;
	struct variable *next;
};

struct block {
	char *name; /* filename */
	char *data; /* content (set at runtime) */
};

struct template {
	char *name;
	/* blocks: header, item, footer */
	struct block blocks[BlockLast];
	/* output FILE * (set at runtime) */
	FILE *fp;
};

static const char *configfile  = "config.cfg";
static const char *outputdir   = "output";
static const char *templatedir = "templates";

static struct variable *global; /* global config variables */

char *
estrdup(const char *s)
{
	char *p;

	if (!(p = strdup(s))) {
		fprintf(stderr, "strdup: %s\n", strerror(errno));
		exit(1);
	}
	return p;
}

void *
ecalloc(size_t nmemb, size_t size)
{
	void *p;

	if (!(p = calloc(nmemb, size))) {
		fprintf(stderr, "calloc: %s\n", strerror(errno));
		exit(1);
	}
	return p;
}

void *
erealloc(void *ptr, size_t size)
{
	void *p;

	if (!(p = realloc(ptr, size))) {
		fprintf(stderr, "realloc: %s\n", strerror(errno));
		exit(1);
	}
	return p;
}

FILE *
efopen(const char *path, const char *mode)
{
	FILE *fp;

	if (!(fp = fopen(path, mode))) {
		fprintf(stderr, "fopen: %s, mode: %s: %s\n",
			path, mode, strerror(errno));
		exit(1);
	}
	return fp;
}

void
catfile(FILE *fpin, const char *ifile, FILE *fpout, const char *ofile)
{
	char buf[READ_BUF_SIZ];
	size_t r;

	while (!feof(fpin)) {
		if (!(r = fread(buf, 1, sizeof(buf), fpin)))
			break;
		if ((fwrite(buf, 1, r, fpout)) != r)
			break;
		if (r != sizeof(buf))
			break;
	}
	if (ferror(fpin)) {
		fprintf(stderr, "%s -> %s: error reading data from stream: %s\n",
		        ifile, ofile, strerror(errno));
		exit(1);
	}
	if (ferror(fpout)) {
		fprintf(stderr, "%s -> %s: error writing data to stream: %s\n",
		        ifile, ofile, strerror(errno));
		exit(1);
	}
}

char *
readfile(const char *file)
{
	FILE *fp;
	char *buf;
	size_t n, len = 0, size = 0;

	fp = efopen(file, "rb");
	buf = ecalloc(1, size + 1); /* always allocate an empty buffer */
	while (!feof(fp)) {
		if (len + READ_BUF_SIZ + 1 > size) {
			/* allocate size: common case is small textfiles */
			size += READ_BUF_SIZ;
			buf = erealloc(buf, size + 1);
		}
		if (!(n = fread(&buf[len], 1, READ_BUF_SIZ, fp)))
			break;
		len += n;
		buf[len] = '\0';
		if (n != READ_BUF_SIZ)
			break;
	}
	if (ferror(fp)) {
		fprintf(stderr, "fread: file: %s: %s\n", file, strerror(errno));
		exit(1);
	}
	fclose(fp);

	return buf;
}

struct variable *
newvar(const char *key, const char *value)
{
	struct variable *v;

	v = ecalloc(1, sizeof(*v));
	v->key = estrdup(key);
	v->value = estrdup(value);

	return v;
}

/* uses var->key as key */
void
setvar(struct variable **vars, struct variable *var, int override)
{
	struct variable *p, *v;

	/* new */
	if (!*vars) {
		*vars = var;
		return;
	}

	/* search: set or append */
	for (p = NULL, v = *vars; v; v = v->next, p = v) {
		if (!strcmp(var->key, v->key)) {
			if (!override)
				return;
			/* NOTE: keep v->next */
			var->next = v->next;
			if (p)
				p->next = var;
			else
				*vars = var;
			free(v->key);
			free(v->value);
			free(v);
			return;
		}
		/* append */
		if (!v->next) {
			var->next = NULL;
			v->next = var;
			return;
		}
	}
}

struct variable *
getvar(struct variable *vars, char *key)
{
	struct variable *v;

	for (v = vars; v; v = v->next)
		if (!strcmp(key, v->key))
			return v;
	return NULL;
}

void
freevars(struct variable *vars)
{
	struct variable *v, *tmp;

	for (v = vars; v; ) {
		tmp = v->next;
		free(v->key);
		free(v->value);
		free(v);
		v = tmp;
	}
}

struct variable *
parsevars(const char *file, const char *s)
{
	struct variable *vars = NULL, *v;
	const char *keystart, *keyend, *valuestart, *valueend;
	size_t linenr = 1;

	for (; *s; ) {
		if (*s == '\r' || *s == '\n') {
			linenr += (*s == '\n');
			s++;
			continue;
		}

		/* comment start with #, skip to newline */
		if (*s == '#') {
			s++;
			s = &s[strcspn(s, "\n")];
			continue;
		}

		/* trim whitespace before key */
		s = &s[strspn(s, " \t")];

		keystart = s;
		s = &s[strcspn(s, "=\r\n")];
		if (*s != '=') {
			fprintf(stderr, "%s:%zu: error: no variable\n",
			        file, linenr);
			exit(1);
		}

		/* trim whitespace at end of key: but whitespace inside names
		   are allowed */
		for (keyend = s++; keyend > keystart &&
		                 (keyend[-1] == ' ' || keyend[-1] == '\t');
		     keyend--)
			;
		/* no variable name: skip */
		if (keystart == keyend) {
			fprintf(stderr, "%s:%zu: error: invalid variable\n",
			        file, linenr);
			exit(1);
		}

		/* trim whitespace before value */
		valuestart = &s[strspn(s, " \t")];
		s = &s[strcspn(s, "\r\n")];
		valueend = s;

		v = ecalloc(1, sizeof(*v));
		v->key = ecalloc(1, keyend - keystart + 1);
		memcpy(v->key, keystart, keyend - keystart);
		v->value = ecalloc(1, valueend - valuestart + 1);
		memcpy(v->value, valuestart, valueend - valuestart);

		setvar(&vars, v, 1);
	}
	return vars;
}

struct variable *
readconfig(const char *file)
{
	struct variable *c;
	char *data;

	data = readfile(file);
	c = parsevars(file, data);
	free(data);

	return c;
}

/* Escape characters below as HTML 2.0 / XML 1.0. */
void
xmlencode(const char *s, FILE *fp)
{
	for (; *s; s++) {
		switch (*s) {
		case '<':  fputs("&lt;",   fp); break;
		case '>':  fputs("&gt;",   fp); break;
		case '\'': fputs("&#39;",  fp); break;
		case '&':  fputs("&amp;",  fp); break;
		case '"':  fputs("&quot;", fp); break;
		default:   fputc(*s, fp);
		}
	}
}

void
writepage(FILE *fp, const char *name, const char *forname,
	struct variable *c, char *s)
{
	FILE *fpin;
	struct variable *v;
	char *key;
	size_t keylen, linenr = 1;
	int op, tmpc;

	for (; *s; s++) {
		op = *s;
		switch (*s) {
		case '#': /* insert value non-escaped */
		case '$': /* insert value escaped */
		case '%': /* insert contents of filename set in variable */
			if (*(s + 1) == '{') {
				s += 2;
				break;
			}
			fputc(*s, fp);
			continue;
		case '\n':
			linenr++; /* FALLTHROUGH */
		default:
			fputc(*s, fp);
			continue;
		}

		/* variable case */
		for (; *s && isspace((unsigned char)*s); s++)
			;
		key = s;
		for (keylen = 0; *s && *s != '}'; s++)
			keylen++;
		/* trim right whitespace */
		for (; keylen && isspace((unsigned char)key[keylen - 1]); )
			keylen--;

		/* temporary NUL terminate */
		tmpc = key[keylen];
		key[keylen] = '\0';

		/* lookup variable in config, if no config or not found look in
		   global config */
		if (!c || !(v = getvar(c, key)))
			v = getvar(global, key);
		key[keylen] = tmpc; /* restore NUL terminator to original */

		if (!v) {
			fprintf(stderr, "%s:%zu: error: undefined variable: '%.*s'%s%s\n",
			        name, linenr, (int)keylen, key,
			        forname ? " for " : "", forname ? forname : "");
			exit(1);
		}

		switch (op) {
		case '#':
			fputs(v->value, fp);
			break;
		case '$':
			xmlencode(v->value, fp);
			break;
		case '%':
			if (!v->value[0])
				break;
			fpin = efopen(v->value, "rb");
			catfile(fpin, v->value, fp, name);
			fclose(fpin);
			break;
		}
	}
}

void
usage(const char *argv0)
{
	fprintf(stderr, "%s [-c configfile] [-o outputdir] [-t templatesdir] "
	                "pages...\n", argv0);
	exit(1);
}

int
main(int argc, char *argv[])
{
	struct template *t, *templates = NULL;
	struct block *b;
	struct variable *c, *v;
	DIR *bdir, *idir;
	struct dirent *ir, *br;
	char file[PATH_MAX + 1], contentfile[PATH_MAX + 1], path[PATH_MAX + 1];
	char outputfile[PATH_MAX + 1], *p, *filename;
	size_t i, j, k, templateslen;
	int argi, r;

	if (pledge("stdio cpath rpath wpath", NULL) == -1) {
		fprintf(stderr, "pledge: %s\n", strerror(errno));
		return 1;
	}

	for (argi = 1; argi < argc; argi++) {
		if (argv[argi][0] != '-')
			break;
		if (argi + 1 >= argc)
			usage(argv[0]);
		switch (argv[argi][1]) {
		case 'c': configfile = argv[++argi]; break;
		case 'o': outputdir = argv[++argi]; break;
		case 't': templatedir = argv[++argi]; break;
		default: usage(argv[0]); break;
		}
	}

	/* global config */
	global = readconfig(configfile);

	/* load templates, must start with "header.", "item." or "footer." */
	templateslen = 0;
	if (!(bdir = opendir(templatedir))) {
		fprintf(stderr, "opendir: %s: %s\n", templatedir, strerror(errno));
		exit(1);
	}

	while ((br = readdir(bdir))) {
		if (br->d_name[0] == '.')
			continue;

		r = snprintf(path, sizeof(path), "%s/%s", templatedir,
		             br->d_name);
		if (r < 0 || (size_t)r >= sizeof(path)) {
			fprintf(stderr, "path truncated: '%s/%s'\n",
			        templatedir, br->d_name);
			exit(1);
		}

		if (!(idir = opendir(path))) {
			fprintf(stderr, "opendir: %s: %s\n", path, strerror(errno));
			exit(1);
		}

		templateslen++;
		/* check overflow */
		if (SIZE_MAX / templateslen < sizeof(*templates)) {
			fprintf(stderr, "realloc: too many templates: %zu\n", templateslen);
			exit(1);
		}
		templates = erealloc(templates, templateslen * sizeof(*templates));
		t = &templates[templateslen - 1];
		memset(t, 0, sizeof(struct template));
		t->name = estrdup(br->d_name);

		while ((ir = readdir(idir))) {
			if (!strncmp(ir->d_name, "header.", sizeof("header.") - 1))
				b = &(t->blocks[BlockHeader]);
			else if (!strncmp(ir->d_name, "item.", sizeof("item.") - 1))
				b = &(t->blocks[BlockItem]);
			else if (!strncmp(ir->d_name, "footer.", sizeof("footer.") - 1))
				b = &(t->blocks[BlockFooter]);
			else
				continue;

			r = snprintf(file, sizeof(file), "%s/%s", path,
			             ir->d_name);
			if (r < 0 || (size_t)r >= sizeof(file)) {
				fprintf(stderr, "path truncated: '%s/%s'\n",
				        path, ir->d_name);
				exit(1);
			}
			b->name = estrdup(file);
			b->data = readfile(file);
		}
		closedir(idir);
	}
	closedir(bdir);

	/* open output files for templates and write header, except for "page" */
	for (i = 0; i < templateslen; i++) {
		/* "page" is a special case */
		if (!strcmp(templates[i].name, "page"))
			continue;
		r = snprintf(file, sizeof(file), "%s/%s", outputdir,
		             templates[i].name);
		if (r < 0 || (size_t)r >= sizeof(file)) {
			fprintf(stderr, "path truncated: '%s/%s'\n", outputdir,
			        templates[i].name);
			exit(1);
		}
		templates[i].fp = efopen(file, "wb");

		/* header */
		b = &templates[i].blocks[BlockHeader];
		if (b->name)
			writepage(templates[i].fp, b->name, NULL, NULL, b->data);
	}

	/* pages */
	for (i = argi; i < (size_t)argc; i++) {
		c = readconfig(argv[i]);

		if ((p = strrchr(argv[i], '.')))
			r = snprintf(contentfile, sizeof(contentfile), "%.*s.html",
			             (int)(p - argv[i]), argv[i]);
		else
			r = snprintf(contentfile, sizeof(contentfile), "%s.html", argv[i]);
		if (r < 0 || (size_t)r >= sizeof(contentfile)) {
			fprintf(stderr, "path truncated for file: '%s'\n", argv[i]);
			exit(1);
		}
		/* set contentfile, but allow to override it */
		setvar(&c, newvar("contentfile", contentfile), 0);

		if ((v = getvar(c, "filename"))) {
			filename = v->value;
		} else {
			/* set output filename (with path removed), but allow
			   to override it */
			if ((p = strrchr(contentfile, '/')))
				filename = &contentfile[p - contentfile + 1];
			else
				filename = contentfile;

			setvar(&c, newvar("filename", filename), 0);
		}

		/* item blocks */
		for (j = 0; j < templateslen; j++) {
			/* "page" is a special case */
			if (!strcmp(templates[j].name, "page")) {
				r = snprintf(outputfile, sizeof(outputfile), "%s/%s",
				             outputdir, filename);
				if (r < 0 || (size_t)r >= sizeof(outputfile)) {
					fprintf(stderr, "path truncated: '%s/%s'\n",
					        outputdir, filename);
					exit(1);
				}

				/* "page" template files are opened per item
				   as opposed to other templates */
				templates[j].fp = efopen(outputfile, "wb");
				for (k = 0; k < LEN(templates[j].blocks); k++) {
					b = &templates[j].blocks[k];
					if (b->name)
						writepage(templates[j].fp,
						          b->name, argv[i], c,
						          b->data);
				}
				fclose(templates[j].fp);
			} else {
				b = &templates[j].blocks[BlockItem];
				if (b->name)
					writepage(templates[j].fp, b->name,
					          argv[i], c, b->data);
			}
		}
		freevars(c);
	}

	/* write footer, except for "page" */
	for (i = 0; i < templateslen; i++) {
		if (!strcmp(templates[i].name, "page"))
			continue;
		b = &templates[i].blocks[BlockFooter];
		if (b->name)
			writepage(templates[i].fp, b->name, NULL, NULL, b->data);
	}

	return 0;
}
