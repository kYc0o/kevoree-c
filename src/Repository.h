#ifndef __Repository_H
#define __Repository_H

#include "hashmap.h"

typedef struct _Repository Repository;
typedef struct _Visitor Visitor;

typedef char* (*fptrRepoMetaClassName)(Repository*);
typedef char* (*fptrRepoInternalGetKey)(Repository*);
typedef void (*fptrDeleteRepository)(Repository*);
typedef void (*fptrVisitAttrRepository)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathRepo)(char*, Repository*);

typedef struct _Repository {
	char* url;
	char* eContainer;
	fptrRepoInternalGetKey InternalGetKey;
	fptrRepoMetaClassName MetaClassName;
	fptrDeleteRepository Delete;
	fptrVisitAttrRepository VisitAttributes;
	fptrVisitAttrRepository VisitPathAttributes;
	fptrFindByPathRepo FindByPath;
} Repository;

Repository* new_Repository(void);
char* Repository_MetaClassName(Repository* const this);
char* Repository_InternalGetKey(Repository* const this);
void delete_Repository(Repository* const this);
void Repository_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void Repository_VisitPathAttributes(void* const this, char* parent, Visitor* visitor);
void* Repository_FindByPath(char* attribute, Repository* const this);

#endif
