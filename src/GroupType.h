#ifndef __GroupType_H
#define __GroupType_H

#include <string.h>
#include <stdbool.h>
#include "hashmap.h"
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
	TypeDefinition* super;
	fptrGroupTypeMetaClassName MetaClassName;
	fptrGroupTypeInternalGetKey InternalGetKey;
	fptrDeleteGroupType Delete;
	fptrVisitAttrGroupType VisitAttributes;
	fptrVisitAttrGroupType VisitPathAttributes;
	fptrVisitRefsGroupType VisitReferences;
	fptrVisitRefsGroupType VisitPathReferences;
} GroupType;

TypeDefinition* newPoly_GroupType(void);
GroupType* new_GroupType(void);
char* GroupType_MetaClassName(GroupType* const this);
char* GroupType_InternalGetKey(void* const this);
void deletePoly_GroupType(TypeDefinition* const this);
void delete_GroupType(GroupType* const this);
void GroupType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void GroupType_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);

#endif /* __GroupType_H */
