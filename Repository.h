#ifndef __Repository_H
#define __Repository_H

#include <string.h>
#include <stdlib.h>
#include "hashmap.h"

typedef struct _Repository Repository;

typedef char* (*fptrRepoMetaClassName)(Repository*);
typedef char* (*fptrRepoInternalGetKey)(Repository*);
typedef void (*fptrDeleteRepository)(Repository*);

typedef struct _Repository {
	void* pDerivedObj;
	char* url;
	fptrRepoInternalGetKey InternalGetKey;
	fptrRepoMetaClassName MetaClassName;
	fptrDeleteRepository Delete;
} Repository;

Repository* new_Repository(void);
char* Repository_MetaClassName(Repository* const this);
char* Repository_InternalGetKey(Repository* const this);
void delete_Repository(Repository* const this);

#endif