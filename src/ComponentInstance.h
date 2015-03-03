#ifndef H_ComponentInstance
#define H_ComponentInstance

#include "hashmap.h"
#include "KMF4C.h"

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
	Instance *super;
	map_t provided;
	map_t required;
	fptrCompInstFindProvidedByID FindProvidedByID;
	fptrCompInstFindRequiredByID FindRequiredByID;
	fptrCompInstAddProvided AddProvided;
	fptrCompInstAddRequired AddRequired;
	fptrCompInstRemoveProvided RemoveProvided;
	fptrCompInstRemoveRequired RemoveRequired;
} ComponentInstance ;

Instance* newPoly_ComponentInstance(void);
ComponentInstance* new_ComponentInstance(void);
void deletePoly_ComponentInstance(void* const this);
void delete_ComponentInstance(void* const this);
char* ComponentInstance_metaClassName(void* const this);
char* ComponentInstance_internalGetKey(void* const this);
Port* ComponentInstance_FindProvidedByID(ComponentInstance* const this, char* id);
Port* ComponentInstance_FindRequiredByID(ComponentInstance* const this, char* id);
void ComponentInstance_AddProvided(ComponentInstance* const this, Port* ptr);
void ComponentInstance_AddRequired(ComponentInstance* const this, Port* ptr);
void ComponentInstance_RemoveProvided(ComponentInstance* const this, Port* ptr);
void ComponentInstance_RemoveRequired(ComponentInstance* const this, Port* ptr);
void ComponentInstance_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void ComponentInstance_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void ComponentInstance_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void ComponentInstance_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* ComponentInstance_FindByPath(char* attribute, void* const this);

#endif /* H_ComponentInstance */
