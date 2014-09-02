#ifndef H_ComponentInstance
#define H_ComponentInstance

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "hashmap.h"
/*#include "Instance.h"
#include "Port.h"
#include "Visitor.h"*/

typedef struct _ComponentInstance ComponentInstance;
typedef struct _Instance Instance;
typedef struct _Port Port;
typedef struct _Visitor Visitor;

typedef char* (*fptrCompInstInternalGetKey)(ComponentInstance*);
typedef char* (*fptrCompInstMetaClassName)(ComponentInstance*);
typedef void (*fptrDeleteComponentInstance)(ComponentInstance*);
typedef Port* (*fptrCompInstFindProvidedByID)(ComponentInstance*, char*);
typedef Port* (*fptrCompInstFindRequiredByID)(ComponentInstance*, char*);
typedef void (*fptrCompInstAddProvided)(ComponentInstance*, Port*);
typedef void (*fptrCompInstAddRequired)(ComponentInstance*, Port*);
typedef void (*fptrCompInstRemoveProvided)(ComponentInstance*, Port*);
typedef void (*fptrCompInstRemoveRequired)(ComponentInstance*, Port*);
typedef void (*fptrVisitAttrComponentInstance)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsComponentInstance)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathComponentInstance)(char*, ComponentInstance*);

typedef struct _ComponentInstance { 
	Instance* super;
	map_t provided;
	map_t required;
	fptrCompInstInternalGetKey InternalGetKey;
	fptrCompInstMetaClassName MetaClassName;
	fptrDeleteComponentInstance Delete;
	fptrCompInstFindProvidedByID FindProvidedByID;
	fptrCompInstFindRequiredByID FindRequiredByID;
	fptrCompInstAddProvided AddProvided;
	fptrCompInstAddRequired AddRequired;
	fptrCompInstRemoveProvided RemoveProvided;
	fptrCompInstRemoveRequired RemoveRequired;
	fptrVisitAttrComponentInstance VisitAttributes;
	fptrVisitRefsComponentInstance VisitReferences;
	fptrFindByPathComponentInstance FindByPath;
} ComponentInstance ;

Instance* newPoly_ComponentInstance(void);
ComponentInstance* new_ComponentInstance(void);
void deletePoly_ComponentInstance(Instance* const this);
void delete_ComponentInstance(ComponentInstance* const this);
char* ComponentInstance_MetaClassName(ComponentInstance* const this);
char* ComponentInstance_InternalGetKey(ComponentInstance* const this);
Port* ComponentInstance_FindProvidedByID(ComponentInstance* const this, char* id);
Port* ComponentInstance_FindRequiredByID(ComponentInstance* const this, char* id);
void ComponentInstance_AddProvided(ComponentInstance* const this, Port* ptr);
void ComponentInstance_AddRequired(ComponentInstance* const this, Port* ptr);
void ComponentInstance_RemoveProvided(ComponentInstance* const this, Port* ptr);
void ComponentInstance_RemoveRequired(ComponentInstance* const this, Port* ptr);
void ComponentInstance_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void ComponentInstance_VisitReferences(void* const this, char* parent, Visitor* visitor);
void* ComponentInstance_FindByPath(char* attribute, ComponentInstance* const this);

#endif /* H_ComponentInstance */
