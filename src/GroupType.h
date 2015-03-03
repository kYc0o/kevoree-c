#ifndef __GroupType_H
#define __GroupType_H

#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
#include "KMF4C.h"
/*#include "TypeDefinition.h"*/

typedef struct _GroupType GroupType;
typedef struct _TypeDefinition TypeDefinition;
typedef struct _Visitor Visitor;

typedef char* (*fptrGroupTypeMetaClassName)(GroupType*);
typedef char* (*fptrGroupTypeInternalGetKey)(GroupType*);
typedef void (*fptrDeleteGroupType)(GroupType*);
typedef void (*fptrVisitAttrGroupType)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsGroupType)(void*, char*, Visitor*);

typedef struct _GroupType {
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
	TypeDefinition* super;
} GroupType;

TypeDefinition* newPoly_GroupType(void);
GroupType* new_GroupType(void);
char* GroupType_metaClassName(void * const this);
char* GroupType_internalGetKey(void * const this);
void deletePoly_GroupType(void * const this);
void delete_GroupType(void * const this);
void GroupType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void GroupType_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);

#endif /* __GroupType_H */
