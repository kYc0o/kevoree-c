#ifndef H_NetworkProperty
#define H_NetworkProperty

#include <stdbool.h>
#include "KMF4C.h"

typedef struct _NetworkProperty NetworkProperty;
typedef struct _NamedElement NamedElement;
typedef struct _Visitor Visitor;

typedef char* (*fptrNetPropMetaClassName)(NetworkProperty*);
typedef char* (*fptrNetPropInternalGetKey)(NetworkProperty*);
typedef void (*fptrDeleteNetworkProperty)(NetworkProperty*);
typedef void (*fptrVisitAttrNetworkProperty)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathNetworkProperty)(char*, NetworkProperty*);

typedef struct _NetworkProperty {
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
	NamedElement *super;
	char *value;
} NetworkProperty;

NamedElement* newPoly_NetworkProperty(void);
NetworkProperty* new_NetworkProperty(void);
char* NetworkProperty_metaClassName(void * const this);
char* NetworkProperty_internalGetKey(void * const this);
void deletePoly_NetworkProperty(void * const this);
void delete_NetworkProperty(void * const this);
void NetworkProperty_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void NetworkProperty_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive);
void* NetworkProperty_FindByPath(char* attribute, void * const this);

#endif /* H_NetworkProperty */
