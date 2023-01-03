/* See LICENSE file for copyright and license details. */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <err.h>
#include <curses.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct slide {
	char *buf;
	size_t siz;
};

static void
printslide(struct slide *s)
{
	printw("%.*s", (int)s->siz, s->buf);
}

int
main(int argc, char *argv[])
{
	int c, i, fd;
	struct slide *s;
	struct stat sb;

	if (argc == 1)
		errx(1, "usage: %s file ...", argv[0]);
	argv++;
	argc--;

	setlocale(LC_ALL, "");

	s = malloc(argc * sizeof(struct slide));
	if (s == NULL)
		err(1, "malloc");

	/* map files to mem */
	for (i = 0; argv[i] != NULL; i++) {
		fd = open(argv[i], O_RDONLY);
		if (fd == -1)
			err(1, "open: %s", argv[i]);
		fstat(fd, &sb);
		s[i].buf = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		if (s[i].buf == MAP_FAILED)
			err(1, "mmap");
		s[i].siz = sb.st_size;
		close(fd);
	}

	/* init curses */
	initscr();
	cbreak();
	noecho();
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	curs_set(FALSE); /* hide cursor */

	/* start */
	i = 0;
show:
	/* display slide */
	clear();
	printslide(&s[i]);
again:
	c = getch();
	switch (c) {
	case 'q':
		break;
	/* next */
	case 'l':
	case 'j':
	case KEY_RIGHT:
	case KEY_DOWN:
		if (i < argc - 1) {
			i++;
			goto show;
		}
		goto again;
	/* prev */
	case 'h':
	case 'k':
	case KEY_LEFT:
	case KEY_UP:
		if (i > 0) {
			i--;
			goto show;
		}
		goto again;
	default:
		goto again;
	}

	/* unmap mem */
	for (i = 0; argv[i] != NULL; i++)
		munmap(s[i].buf, s[i].siz);
	free(s);

	endwin(); /* restore terminal */

	return (0);
}
