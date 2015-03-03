#ifndef __KMF4C_H
#define __KMF4C_H

#include <stdbool.h>
#include "hashmap.h"

typedef struct _KMFContainer KMFContainer;
typedef struct _Visitor Visitor;

typedef char* (*fptrKMFMetaClassName)(void*);
typedef char* (*fptrKMFInternalGetKey)(void*);
/*
 * TODO fix to single visitor function pointer
 */
typedef void (*fptrVisitAttr)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefs)(void*, char*, Visitor*, bool);
typedef void* (*fptrFindByPath)(char*, void*);
typedef void (*fptrDelete)(void*);

typedef struct _KMFContainer {
	void *pDerivedObj;
	char *eContainer;
	char *path;
	map_t refs;
	fptrKMFMetaClassName metaClassName;
	fptrKMFInternalGetKey internalGetKey;
	fptrVisitAttr VisitAttributes;
	fptrVisitAttr VisitPathAttributes;
	fptrVisitRefs VisitReferences;
	fptrVisitRefs VisitPathReferences;
	fptrFindByPath FindByPath;
	fptrDelete Delete;
} KMFContainer;


#endif
