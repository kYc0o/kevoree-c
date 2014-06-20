#ifndef __GroupType_H
#define __GroupType_H

#include <string.h>
#include "hashmap.h"
#include "TypeDefinition.h"

typedef struct _GroupType GroupType;

typedef char* (*fptrGroupTypeMetaClassName)(GroupType*);
typedef char* (*fptrGroupTypeInternalGetKey)(GroupType*);
typedef void (*fptrDeleteGroupType)(GroupType*);

typedef struct _GroupType {
	TypeDefinition* super;
	fptrGroupTypeMetaClassName MetaClassName;
	fptrGroupTypeInternalGetKey InternalGetKey;
	fptrDeleteGroupType Delete;  
} GroupType;

TypeDefinition* newPoly_GroupType(void);
GroupType* new_GroupType(void);
char* GroupType_MetaClassName(GroupType* const this);
char* GroupType_InternalGetKey(GroupType* const this);
void deletePoly_GroupType(TypeDefinition* const this);
void delete_GroupType(GroupType* const this);

#endif /* __GroupType_H */
