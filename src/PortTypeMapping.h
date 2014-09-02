#ifndef __PortTypeMapping_H
#define __PortTypeMapping_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashmap.h"
/*#include "Visitor.h"
#include "PortTypeRef.h"*/

typedef struct _PortTypeMapping PortTypeMapping;
typedef struct _PortTypeRef PortTypeRef;
typedef struct _Visitor Visitor;

typedef char* (*fptrPortTypMapMetaClassName)(PortTypeMapping*);
typedef char* (*fptrPortTypMapInternalGetKey)(PortTypeMapping*);
typedef void (*fptrDeletePortTypeMapping)(PortTypeMapping*);
typedef void (*fptrVisitAttrPortTypeMapping)(void*, char*, Visitor*);
/*typedef void (*fptrVisitRefsPortTypeMapping)(void*, char*, Visitor*);*/
typedef void* (*fptrFindByPathPortTypeMapping)(char*, PortTypeMapping*);

typedef struct _PortTypeMapping {
	void *pDerivedObj;
	char *beanMethodName;
	char *serviceMethodName;
	char *paramTypes;
	char generated_KMF_ID[9];
	PortTypeRef *eContainer;
	fptrPortTypMapMetaClassName MetaClassName;
	fptrPortTypMapInternalGetKey InternalGetKey;
	fptrDeletePortTypeMapping Delete;
	fptrVisitAttrPortTypeMapping VisitAttributes;
	/*fptrVisitRefsPortTypeMapping VisitReferences;*/
	fptrFindByPathPortTypeMapping FindByPath;
} PortTypeMapping;

PortTypeMapping* new_PortTypeMapping(void);
char* PortTypeMapping_MetaClassName(PortTypeMapping* const this);
char* PortTypeMapping_InternalGetKey(PortTypeMapping* const this);
void delete_PortTypeMapping(PortTypeMapping* const this);
void PortTypeMapping_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void* PortTypeMapping_FindByPath(char* attribute, PortTypeMapping* const this);

#endif /*__PortTypeMapping_H */
