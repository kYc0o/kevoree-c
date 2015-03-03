#ifndef __PortTypeRef_H
#define __PortTypeRef_H

#include <stdbool.h>
#include "hashmap.h"
#include "KMF4C.h"

typedef struct _PortTypeRef PortTypeRef;
typedef struct _NamedElement NamedElement;
typedef struct _PortType PortType;
typedef struct _PortTypeMapping PortTypeMapping;
typedef struct _Visitor Visitor;

typedef char* (*fptrPortTypeRefMetaClassName)(PortTypeRef*);
typedef char* (*fptrPortTypeRefInternalGetKey)(PortTypeRef*);
typedef PortTypeMapping* (*fptrPortTypeRefFindMappingsByID)(PortTypeRef*, char*);
typedef void (*fptrPortTypeRefAddRef)(PortTypeRef*, PortType*);
typedef void (*fptrPortTypeRefAddMappings)(PortTypeRef*, PortTypeMapping*);
typedef void (*fptrPortTypeRefRemoveRef)(PortTypeRef*, PortType*);
typedef void (*fptrPortTypeRefRemoveMappings)(PortTypeRef*, PortTypeMapping*);
typedef void (*fptrDeletePortTypeRef)(PortTypeRef*);
typedef void (*fptrVisitAttrPortTypeRef)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsPortTypeRef)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathPortTypeRef)(char*, PortTypeRef*);

typedef struct _PortTypeRef {
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
	bool optional;
	bool noDependency;
	PortType *ref;
	map_t mappings;
	fptrPortTypeRefFindMappingsByID FindMappingsByID;
	fptrPortTypeRefAddRef AddRef;
	fptrPortTypeRefAddMappings AddMappings;
	fptrPortTypeRefRemoveRef RemoveRef;
	fptrPortTypeRefRemoveMappings RemoveMappings;
} PortTypeRef;

NamedElement* newPoly_PortTypeRef(void);
PortTypeRef* new_PortTypeRef(void);
char* PortTypeRef_metaClassName(void * const this);
char* PortTypeRef_internalGetKey(void * const this);
PortTypeMapping* PortTypeRef_FindMappingsByID(PortTypeRef* const this, char* id);
void PortTypeRef_AddRef(PortTypeRef* const this, PortType* ptr);
void PortTypeRef_AddMappings(PortTypeRef* const this, PortTypeMapping* ptr);
void PortTypeRef_RemoveRef(PortTypeRef* const this, PortType* ptr);
void PortTypeRef_RemoveMappings(PortTypeRef* const this, PortTypeMapping* ptr);
void deletePoly_PortTypeRef(void * const this);
void delete_PortTypeRef(void * const this);
void PortTypeRef_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void PortTypeRef_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void PortTypeRef_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void PortTypeRef_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* PortTypeRef_FindByPath(char* attribute, void * const this);

#endif /* __PortTypeRef_H */
