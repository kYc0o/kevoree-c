#ifndef __Repository_H
#define __Repository_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
#include "Visitor.h"

typedef struct _Repository Repository;

typedef char* (*fptrRepoMetaClassName)(Repository*);
typedef char* (*fptrRepoInternalGetKey)(Repository*);
typedef void (*fptrDeleteRepository)(Repository*);
typedef void (*fptrVisitAttrRepository)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsRepository)(void*, char*, Visitor*);

typedef struct _Repository {
	void* pDerivedObj;
	char* url;
	fptrRepoInternalGetKey InternalGetKey;
	fptrRepoMetaClassName MetaClassName;
	fptrDeleteRepository Delete;
	fptrVisitAttrRepository VisitAttributes;
	fptrVisitRefsRepository VisitReferences;
} Repository;

Repository* new_Repository(void);
char* Repository_MetaClassName(Repository* const this);
char* Repository_InternalGetKey(Repository* const this);
void delete_Repository(Repository* const this);
void Repository_VisitAttributes(void* const this, char* parent, Visitor* visitor);
/*void Repository_VisitReferences(void* const this, char* parent, Visitor* visitor);*/

#endif