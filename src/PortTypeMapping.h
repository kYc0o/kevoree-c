#ifndef __PortTypeMapping_H
#define __PortTypeMapping_H

#include "hashmap.h"

typedef struct _PortTypeRef PortTypeRef;
typedef struct _PortTypeMapping PortTypeMapping;
typedef struct _Visitor Visitor;

typedef char* (*fptrPortTypMapMetaClassName)(PortTypeMapping*);
typedef char* (*fptrPortTypMapInternalGetKey)(PortTypeMapping*);
typedef void (*fptrDeletePortTypeMapping)(PortTypeMapping*);
typedef void (*fptrVisitAttrPortTypeMapping)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathPortTypeMapping)(char*, PortTypeMapping*);

typedef struct _PortTypeMapping {
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
	char *beanMethodName;
	char *serviceMethodName;
	char *paramTypes;
	char generated_KMF_ID[9];
} PortTypeMapping;

PortTypeMapping* new_PortTypeMapping(void);
char* PortTypeMapping_metaClassName(void * const this);
char* PortTypeMapping_internalGetKey(void * const this);
void delete_PortTypeMapping(void * const this);
void PortTypeMapping_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void PortTypeMapping_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void* PortTypeMapping_FindByPath(char* attribute, void * const this);

#endif /*__PortTypeMapping_H */
