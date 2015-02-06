#ifndef __ComponentType_H
#define __ComponentType_H

#include <stdbool.h>
#include "hashmap.h"

typedef struct _ComponentType ComponentType;
typedef struct _TypeDefinition TypeDefinition;
typedef struct _PortTypeRef PortTypeRef;
typedef struct _Visitor Visitor;

typedef char* (*fptrCompTypeMetaClassName)(ComponentType*);
typedef char* (*fptrCompTypeInternalGetKey)(void*);
typedef PortTypeRef* (*fptrCompTypeFindRequiredByID)(TypeDefinition*, char*);
typedef PortTypeRef* (*fptrCompTypeFindProvidedByID)(TypeDefinition*, char*);
typedef void (*fptrCompTypeAddRequired)(ComponentType*, PortTypeRef*);
typedef void (*fptrCompTypeAddProvided)(ComponentType*, PortTypeRef*);
typedef void (*fptrCompTypeRemoveRequired)(TypeDefinition*, PortTypeRef*);
typedef void (*fptrCompTypeRemoveProvided)(TypeDefinition*, PortTypeRef*);
typedef void (*fptrDeleteComponentType)(ComponentType*);
typedef void (*fptrVisitAttrComponentType)(void*, char*, Visitor*, bool);
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
	fptrVisitAttrComponentType VisitPathAttributes;
	fptrVisitRefsComponentType VisitReferences;
	fptrVisitRefsComponentType VisitPathReferences;
	fptrFindByPathComponentType FindByPath;
} ComponentType;

TypeDefinition* newPoly_ComponentType(void);
ComponentType* new_ComponentType(void);
char* ComponentType_MetaClassName(ComponentType* const this);
char* ComponentType_InternalGetKey(void* const this);
PortTypeRef* ComponentType_FindRequiredByID(TypeDefinition* const this, char*);
PortTypeRef* ComponentType_FindProvidedByID(TypeDefinition* const this, char*);
void ComponentType_AddRequired(ComponentType* const this, PortTypeRef* ptr);
void ComponentType_AddProvided(ComponentType* const this, PortTypeRef* ptr);
void ComponentType_RemoveRequired(TypeDefinition* const this, PortTypeRef* ptr);
void ComponentType_RemoveProvided(TypeDefinition* const this, PortTypeRef* ptr);
void deletePoly_ComponentType(TypeDefinition* const this);
void delete_ComponentType(ComponentType* const this);
void ComponentType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void ComponentType_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void ComponentType_VisitReferences(void* const this, char* parent, Visitor* visitor);
void ComponentType_VisitPathReferences(void* const this, char* parent, Visitor* visitor);
void* ComponentType_FindByPath(char* attribute, TypeDefinition* const this);
 
#endif /* __ComponentType_H */
