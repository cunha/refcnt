#include <stdlib.h>
#include <stdio.h>

#include "refcnt.h"

struct refcnt * refcnt_create(void *ptr, void (*destructor)(void *, void *),
		void *destructor_data)
{
	struct refcnt *r = malloc(sizeof(struct refcnt));
	if(!r) { perror(NULL); return NULL; }
	r->ptr = ptr;
	r->cnt = 1;
	r->destructor = destructor;
	r->destructor_data = destructor_data;
	return r;
}

void refcnt_get(struct refcnt *ref)
{
	ref->cnt++;
}

void refcnt_del(struct refcnt *ref)
{
	ref->cnt--;
	if(ref->cnt > 0) return;
	if(ref->destructor && ref->ptr)
		ref->destructor(ref->ptr, ref->destructor_data);
	free(ref);
}


