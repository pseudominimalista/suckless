.POSIX:

NAME = saait
VERSION = 0.8

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/man
DOCPREFIX = ${PREFIX}/share/doc/${NAME}

# use system flags.
SAAIT_CFLAGS = ${CFLAGS}
SAAIT_LDFLAGS = ${LDFLAGS}
SAAIT_CPPFLAGS = -D_DEFAULT_SOURCE

SRC = \
	saait.c
BIN = \
	saait
MAN1 = \
	saait.1
DOC = \
	LICENSE\
	README\
	Makefile.example

OBJ = ${SRC:.c=.o}

all: ${BIN}

.o:
	${CC} ${SAAIT_LDFLAGS} -o $@

.c.o:
	${CC} ${SAAIT_CFLAGS} ${SAAIT_CPPFLAGS} -o $@ -c $<

dist:
	rm -rf ${NAME}-${VERSION}
	mkdir -p ${NAME}-${VERSION}
	cp -f ${MAN1} ${SRC} ${DOC} \
		Makefile \
		config.cfg print.css style.css \
		${NAME}-${VERSION}
	# pages and templates examples.
	cp -rf pages templates ${NAME}-${VERSION}
	# make tarball
	tar -cf - ${NAME}-${VERSION} | \
		gzip -c > ${NAME}-${VERSION}.tar.gz
	rm -rf ${NAME}-${VERSION}

${OBJ}:

saait: saait.o
	${CC} -o $@ saait.o ${LDFLAGS}

clean:
	rm -f ${BIN} ${OBJ} ${NAME}-${VERSION}.tar.gz

install: all
	# installing executable files.
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f ${BIN} ${DESTDIR}${PREFIX}/bin
	for f in ${BIN}; do chmod 755 ${DESTDIR}${PREFIX}/bin/$$f; done
	# installing example files.
	mkdir -p ${DESTDIR}${DOCPREFIX}
	cp -f \
		README\
		Makefile.example\
		print.css\
		style.css\
		config.cfg\
		${DESTDIR}${DOCPREFIX}
	# pages and templates examples.
	cp -rf pages templates ${DESTDIR}${DOCPREFIX}
	# installing manual pages.
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	cp -f ${MAN1} ${DESTDIR}${MANPREFIX}/man1
	for m in ${MAN1}; do chmod 644 ${DESTDIR}${MANPREFIX}/man1/$$m; done

uninstall:
	# removing executable files.
	for f in ${BIN}; do rm -f ${DESTDIR}${PREFIX}/bin/$$f; done
	# removing example files.
	rm -f \
		${DESTDIR}${DOCPREFIX}/README\
		${DESTDIR}${DOCPREFIX}/Makefile.example\
		${DESTDIR}${DOCPREFIX}/print.css\
		${DESTDIR}${DOCPREFIX}/style.css\
		${DESTDIR}${DOCPREFIX}/config.cfg
	# pages and templates examples.
	rm -rf ${DESTDIR}${DOCPREFIX}/templates \
		${DESTDIR}${DOCPREFIX}/pages
	-rmdir ${DESTDIR}${DOCPREFIX}
	# removing manual pages.
	for m in ${MAN1}; do rm -f ${DESTDIR}${MANPREFIX}/man1/$$m; done

.PHONY: all clean dist install uninstall
