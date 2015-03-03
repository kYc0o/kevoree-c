#ifndef H_DeployUnit
#define H_DeployUnit

#include "hashmap.h"

typedef struct _DeployUnit DeployUnit;
typedef struct _NamedElement NamedElement;
typedef struct _Visitor Visitor;

typedef char* (*fptrDepUnitMetaClassName)(DeployUnit*);
typedef char* (*fptrDepUnitInternalGetKey)(DeployUnit*);
typedef void (*fptrDepUnitAddRequiredLibs)(DeployUnit*, DeployUnit*);
typedef void (*fptrDepUnitRemoveRequiredLibs)(DeployUnit*, DeployUnit*);
typedef DeployUnit* (*fptrDepUnitFindRequiredLibsByID)(DeployUnit*, char*);
typedef void (*fptrDeleteDepUnit)(DeployUnit*);
typedef void (*fptrVisitAttrDeployUnit)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsDeployUnit)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathDeployUnit)(char*, DeployUnit*);

typedef struct _DeployUnit {
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
	NamedElement* super;
	char *groupName;
	char *version;
	char *url;
	char *hashcode;
	char *type;
	char *internalKey;
	map_t requiredLibs;
	fptrDepUnitAddRequiredLibs AddRequiredLibs;
	fptrDepUnitRemoveRequiredLibs RemoveRequiredLibs;
	fptrDepUnitFindRequiredLibsByID FindRequiredLibsByID;
} DeployUnit;

NamedElement* newPoly_DeployUnit(void);
DeployUnit* new_DeployUnit(void);
char* DeployUnit_metaClassName(void* const this);
char* DeployUnit_internalGetKey(void* const this);
void DeployUnit_AddRequiredLibs(DeployUnit* const this, DeployUnit* ptr);
void DeployUnit_RemoveRequiredLibs(DeployUnit* const this, DeployUnit* ptr);
DeployUnit* DeployUnit_FindRequiredLibsByID(DeployUnit* const this, char* id);
void deletePoly_DeployUnit(void* const this);
void delete_DeployUnit(void* const this);
void DeployUnit_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void DeployUnit_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void DeployUnit_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void DeployUnit_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* DeployUnit_FindByPath(char* attribute, void* const this);

#endif /* H_DeployUnit */
