#ifndef __PortType_H
#define __PortType_H

#include <stdbool.h>
#include "KMF4C.h"

typedef struct _PortType PortType;
typedef struct _TypeDefinition TypeDefinition;
typedef struct _Visitor Visitor;

typedef char* (*fptrPortTypeMetaClassName)(PortType*);
typedef char* (*fptrPortTypeInternalGetKey)(PortType*);
typedef void (*fptrDeletePortType)(PortType*);
typedef void (*fptrVisitAttrPortType)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsPortType)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathPortType)(char*, TypeDefinition*);

typedef struct _PortType {
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
	bool synchrone;
} PortType;

TypeDefinition* newPoly_PortType(void);
PortType* new_PortType(void);
char* PortType_metaClassName(void * const this);
char* PortType_internalGetKey(void * const this);
void deletePoly_PortType(void * const this);
void delete_PortType(void * const this);
void PortType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void PortType_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void* PortType_FindByPath(char* attribute, void * const this);

#endif /*__PortType_H */
