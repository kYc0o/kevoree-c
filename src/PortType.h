#ifndef __PortType_H
#define __PortType_H

#include <string.h>
#include <stdlib.h>
#include "TypeDefinition.h"

typedef struct _PortType PortType;

typedef char* (*fptrPortTypeMetaClassName)(PortType*);
typedef char* (*fptrPortTypeInternalGetKey)(PortType*);
typedef void (*fptrDeletePortType)(PortType*);
typedef void (*fptrVisitAttrPortType)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsPortType)(void*, char*, Visitor*);

typedef struct _PortType {
	void* pDerivedObj;
	TypeDefinition* super;
	int synchrone;
	fptrPortTypeMetaClassName MetaClassName;
	fptrPortTypeInternalGetKey InternalGetKey;
	fptrDeletePortType Delete;
	fptrVisitAttrPortType VisitAttributes;
	fptrVisitRefsPortType VisitReferences;
} PortType;

TypeDefinition* newPoly_PortType(void);
PortType* new_PortType(void);
char* PortType_MetaClassName(PortType* const this);
char* PortType_InternalGetKey(PortType* const this);
void deletePoly_PortType(TypeDefinition* const this);
void delete_PortType(PortType* const this);
void PortType_VisitAttributes(void* const this, char* parent, Visitor* visitor);

#endif /*__PortType_H */