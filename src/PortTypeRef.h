#ifndef __PortTypeRef_H
#define __PortTypeRef_H

#include <string.h>
#include "hashmap.h"
#include "NamedElement.h"
#include "PortType.h"
#include "PortTypeMapping.h"

typedef struct _PortTypeRef PortTypeRef;

typedef char* (*fptrPortTypeRefMetaClassName)(PortTypeRef*);
typedef char* (*fptrPortTypeRefInternalGetKey)(PortTypeRef*);
typedef PortTypeMapping* (*fptrPortTypeRefFindMappingsByID)(PortTypeRef*, char*);
typedef void (*fptrPortTypeRefAddRef)(PortTypeRef*, PortType*);
typedef void (*fptrPortTypeRefAddMappings)(PortTypeRef*, PortTypeMapping*);
typedef void (*fptrPortTypeRefRemoveRef)(PortTypeRef*, PortType*);
typedef void (*fptrPortTypeRefRemoveMappings)(PortTypeRef*, PortTypeMapping*);
typedef void (*fptrDeletePortTypeRef)(PortTypeRef*);
typedef void (*fptrVisitAttrPortTypeRef)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsPortTypeRef)(void*, char*, Visitor*);

typedef struct _PortTypeRef {
	NamedElement* super;
	int optional;
	int noDependency;
	PortType* ref;
	map_t mappings;
	fptrPortTypeRefMetaClassName MetaClassName;
	fptrPortTypeRefInternalGetKey InternalGetKey;
	fptrPortTypeRefFindMappingsByID FindMappingsByID;
	fptrPortTypeRefAddRef AddRef;
	fptrPortTypeRefAddMappings AddMappings;
	fptrPortTypeRefRemoveRef RemoveRef;
	fptrPortTypeRefRemoveMappings RemoveMappings;
	fptrDeletePortTypeRef Delete;
	fptrVisitAttrPortTypeRef VisitAttributes;
	fptrVisitRefsPortTypeRef VisitReferences;
} PortTypeRef;

NamedElement* newPoly_PortTypeRef(void);
PortTypeRef* new_PortTypeRef(void);
char* PortTypeRef_MetaClassName(PortTypeRef* const this);
char* PortTypeRef_InternalGetKey(PortTypeRef* const this);
PortTypeMapping* PortTypeRef_FindMappingsByID(PortTypeRef* const this, char* id);
void PortTypeRef_AddRef(PortTypeRef* const this, PortType* ptr);
void PortTypeRef_AddMappings(PortTypeRef* const this, PortTypeMapping* ptr);
void PortTypeRef_RemoveRef(PortTypeRef* const this, PortType* ptr);
void PortTypeRef_RemoveMappings(PortTypeRef* const this, PortTypeMapping* ptr);
void deletePoly_PortTypeRef(NamedElement* const this);
void delete_PortTypeRef(PortTypeRef* const this);
void PortTypeRef_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void PortTypeRef_VisitReferences(void* const this, char* parent, Visitor* visitor);

#endif /* __PortTypeRef_H */
