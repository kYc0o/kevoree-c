#ifndef __ComponentType_H
#define __ComponentType_H

#include <string.h>
#include "hashmap.h"
#include "TypeDefinition.h"
#include "PortTypeRef.h"

typedef struct _ComponentType ComponentType;

typedef char* (*fptrCompTypeMetaClassName)(ComponentType*);
typedef char* (*fptrCompTypeInternalGetKey)(void*);
typedef PortTypeRef* (*fptrCompTypeFindRequiredByID)(ComponentType*, char*);
typedef PortTypeRef* (*fptrCompTypeFindProvidedByID)(ComponentType*, char*);
typedef void (*fptrCompTypeAddRequired)(ComponentType*, PortTypeRef*);
typedef void (*fptrCompTypeAddProvided)(ComponentType*, PortTypeRef*);
typedef void (*fptrCompTypeRemoveRequired)(ComponentType*, PortTypeRef*);
typedef void (*fptrCompTypeRemoveProvided)(ComponentType*, PortTypeRef*);
typedef void (*fptrDeleteComponentType)(ComponentType*);
typedef void (*fptrVisitAttrComponentType)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsComponentType)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathComponentType)(char*, TypeDefinition*);

typedef struct _ComponentType {
	TypeDefinition* super;
	map_t required;
	map_t provided;
	fptrCompTypeMetaClassName MetaClassName;
	fptrCompTypeInternalGetKey InternalGetKey;
	fptrCompTypeFindRequiredByID FindRequiredByID;
	fptrCompTypeFindProvidedByID FindProvidedByID;
	fptrCompTypeAddRequired AddRequired;
	fptrCompTypeAddProvided AddProvided;
	fptrCompTypeRemoveRequired RemoveRequired;
	fptrCompTypeRemoveProvided RemoveProvided;
	fptrDeleteComponentType Delete;
	fptrVisitAttrComponentType VisitAttributes;
	fptrVisitRefsComponentType VisitReferences;
	fptrFindByPathComponentType FindByPath;
} ComponentType;

TypeDefinition* newPoly_ComponentType(void);
ComponentType* new_ComponentType(void);
char* ComponentType_MetaClassName(ComponentType* const this);
char* ComponentType_InternalGetKey(void* const this);
PortTypeRef* ComponentType_FindRequiredByID(ComponentType* const this, char*);
PortTypeRef* ComponentType_FindProvidedByID(ComponentType* const this, char*);
void ComponentType_AddRequired(ComponentType* const this, PortTypeRef* ptr);
void ComponentType_AddProvided(ComponentType* const this, PortTypeRef* ptr);
void ComponentType_RemoveRequired(ComponentType* const this, PortTypeRef* ptr);
void ComponentType_RemoveProvided(ComponentType* const this, PortTypeRef* ptr);
void deletePoly_ComponentType(TypeDefinition* const this);
void delete_ComponentType(ComponentType* const this);
void ComponentType_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void ComponentType_VisitReferences(void* const this, char* parent, Visitor* visitor);
void* ComponentType_FindByPath(char* attribute, TypeDefinition* const this);
 
#endif /* __ComponentType_H */