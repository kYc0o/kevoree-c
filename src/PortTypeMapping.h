#ifndef __PortTypeMapping_H
#define __PortTypeMapping_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
#include "Visitor.h"

typedef struct _PortTypeMapping PortTypeMapping;

typedef char* (*fptrPortTypMapMetaClassName)(PortTypeMapping*);
typedef char* (*fptrPortTypMapInternalGetKey)(PortTypeMapping*);
typedef void (*fptrDeletePortTypeMapping)(PortTypeMapping*);
typedef void (*fptrVisitAttrPortTypeMapping)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsPortTypeMapping)(void*, char*, Visitor*);

typedef struct _PortTypeMapping {
	void* pDerivedObj;
	char* beanMethodName;
	char* serviceMethodName;
	char* paramTypes;
	char* generated_KMF_ID;
	fptrPortTypMapMetaClassName MetaClassName;
	fptrPortTypMapInternalGetKey InternalGetKey;
	fptrDeletePortTypeMapping Delete;
	fptrVisitAttrPortTypeMapping VisitAttributes;
	fptrVisitRefsPortTypeMapping VisitReferences;
} PortTypeMapping;

PortTypeMapping* new_PortTypeMapping(void);
char* PortTypeMapping_MetaClassName(PortTypeMapping* const this);
char* PortTypeMapping_InternalGetKey(PortTypeMapping* const this);
void delete_PortTypeMapping(PortTypeMapping* const this);
void PortTypeMapping_VisitAttributes(void* const this, char* parent, Visitor* visitor);

#endif /*__PortTypeMapping_H */