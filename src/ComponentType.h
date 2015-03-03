#ifndef __ComponentType_H
#define __ComponentType_H

#include <stdbool.h>
#include "hashmap.h"
#include "KMF4C.h"

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
	map_t required;
	map_t provided;
	fptrCompTypeFindRequiredByID FindRequiredByID;
	fptrCompTypeFindProvidedByID FindProvidedByID;
	fptrCompTypeAddRequired AddRequired;
	fptrCompTypeAddProvided AddProvided;
	fptrCompTypeRemoveRequired RemoveRequired;
	fptrCompTypeRemoveProvided RemoveProvided;
} ComponentType;

TypeDefinition* newPoly_ComponentType(void);
ComponentType* new_ComponentType(void);
char* ComponentType_metaClassName(void* const this);
char* ComponentType_internalGetKey(void* const this);
PortTypeRef* ComponentType_FindRequiredByID(TypeDefinition* const this, char*);
PortTypeRef* ComponentType_FindProvidedByID(TypeDefinition* const this, char*);
void ComponentType_AddRequired(ComponentType* const this, PortTypeRef* ptr);
void ComponentType_AddProvided(ComponentType* const this, PortTypeRef* ptr);
void ComponentType_RemoveRequired(TypeDefinition* const this, PortTypeRef* ptr);
void ComponentType_RemoveProvided(TypeDefinition* const this, PortTypeRef* ptr);
void deletePoly_ComponentType(void* const this);
void delete_ComponentType(void* const this);
void ComponentType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void ComponentType_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void ComponentType_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void ComponentType_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* ComponentType_FindByPath(char* attribute, void* const this);
 
#endif /* __ComponentType_H */
