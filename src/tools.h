/*#ifndef H_TOOLS
#define H_TOOLS

#include <string.h>
#include <stdlib.h>

typedef struct __visitor {
	void (*action)(void *val, void *val2, int type); // Implementation, for example VisitorCount or VisitorDesc
} Visitor;

size_t getsize(void *p);
void *realloc(void *ptr,size_t size);
#endif*/
