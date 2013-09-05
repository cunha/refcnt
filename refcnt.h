#ifndef __REFCNT_H__
#define __REFCNT_H__

/* This module implements a reference counter.  A reference counter keeps a
 * pointer =ptr=, a counter of the number of existing references =cnt=, and an
 * optional pointer to a =destructor= function to free any memory used by
 * =ptr= when there are no more references.
 *
 * When a reference counter is created, its counter =cnt= is initialized with
 * 1.  Each new reference increments the counter, and each reference closed
 * decrements the counter.  When the counter reaches zero, =destructor= gets
 * called on =ptr= if both are non-null, and the reference counter itself is
 * freed (and thus cannot be used further).
 */

struct refcnt {
	void *ptr;
	int cnt;
	void (*destructor)(void *ptr, void *data);
	void *destructor_data;
};

struct refcnt * refcnt_create(void *ptr, void (*destructor)(void *, void *),
		void *destructor_data);

void refcnt_get(struct refcnt *ref);
void refcnt_del(struct refcnt *ref);

#endif

