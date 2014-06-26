#ifndef __TypeLibrary_H
#define __TypeLibrary_H

#include <string.h>
#include "hashmap.h"
#include "NamedElement.h"
#include "TypeDefinition.h"

typedef struct _TypeLibrary TypeLibrary;

typedef char* (*fptrTypeLibMetaClassName)(TypeLibrary*);
typedef char* (*fptrTypeLibInternalGetKey)(TypeLibrary*);
typedef TypeDefinition* (*fptrTypeLibFindSubTypesByID)(TypeLibrary*, char*);
typedef void (*fptrTypeLibAddSubTypes)(TypeLibrary*, TypeDefinition*);
typedef void (*fptrTypeLibRemoveSubTypes)(TypeLibrary*, TypeDefinition*);
typedef void (*fptrDeleteTypeLib)(TypeLibrary*);

typedef struct _TypeLibrary {
	NamedElement* super;
	map_t subTypes;
	fptrTypeLibMetaClassName MetaClassName;
	fptrTypeLibInternalGetKey InternalGetKey;
	fptrTypeLibFindSubTypesByID FindSubTypesByID;
	fptrTypeLibAddSubTypes AddSubTypes;
	fptrTypeLibRemoveSubTypes RemoveSubTypes;
	fptrDeleteTypeLib Delete;  
} TypeLibrary;

NamedElement* newPoly_TypeLibrary(void);
TypeLibrary* new_TypeLibrary(void);
char* TypeLibrary_MetaClassname(TypeLibrary* const this);
char* TypeLibrary_InternalGetKey(TypeLibrary* const this);
TypeDefinition* TypeLibrary_FindSubTypesByID(TypeLibrary* const this, char* id);
void TypeLibrary_AddSubTypes(TypeLibrary* const this, TypeDefinition* ptr);
void TypeLibrary_RemoveSubTypes(TypeLibrary* const this, TypeDefinition* ptr);
void deletePoly_TypeLibrary(NamedElement* const this);
void delete_TypeLibrary(TypeLibrary* const this);

#endif /* __TypeLibrary_H */