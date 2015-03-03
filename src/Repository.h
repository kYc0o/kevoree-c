#ifndef __Repository_H
#define __Repository_H

#include "hashmap.h"
#include "KMF4C.h"

typedef struct _Repository Repository;
typedef struct _Visitor Visitor;

typedef char* (*fptrRepoMetaClassName)(Repository*);
typedef char* (*fptrRepoInternalGetKey)(Repository*);
typedef void (*fptrDeleteRepository)(Repository*);
typedef void (*fptrVisitAttrRepository)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathRepo)(char*, Repository*);

typedef struct _Repository {
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
	char* url;
} Repository;

Repository* new_Repository(void);
char* Repository_metaClassName(void * const this);
char* Repository_internalGetKey(void * const this);
void delete_Repository(void * const this);
void Repository_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Repository_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void* Repository_FindByPath(char* attribute, void * const this);

#endif
