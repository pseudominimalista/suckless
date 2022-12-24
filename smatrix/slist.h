#ifndef _slist_h
#define _slist_h

typedef struct _slist slist;

typedef struct _slist
{
	slist *prev;
	slist *next;
	drop *data;

} slist;

#endif
