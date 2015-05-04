#include "realloc.h"
#include <stdlib.h>
#include <string.h>

size_t getsize(void *p)
{
	size_t *in = p;

	if(in)
	{
		--in; 
		return *in;
	}

	return -1;
}

void *realloc(void *ptr, size_t size)
{
	void *newptr;
	int msize;
	msize = getsize(ptr);

	if (size <= msize)
		return ptr;

	newptr = malloc(size);
	memcpy(newptr, ptr, msize);
	free(ptr);

	return newptr;
}
