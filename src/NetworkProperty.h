#ifndef H_NetworkProperty
#define H_NetworkProperty

#include <stdlib.h>
#include <string.h>
#include "NamedElement.h"

typedef struct _NetworkProperty NetworkProperty;

typedef char* (*fptrNetPropMetaClassName)(NetworkProperty*);
typedef char* (*fptrNetPropInternalGetKey)(NetworkProperty*);
typedef void (*fptrDeleteNetworkProperty)(NetworkProperty*);
typedef void (*fptrVisitAttrNetworkProperty)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsNetworkProperty)(void*, char*, Visitor*);

typedef struct _NetworkProperty {
	NamedElement* super;
	char* value;
	/*int (*accept)(struct _NetworkProperty*, struct _NetworkProperty*, Visitor*);*/
	fptrNetPropMetaClassName MetaClassName;
	fptrNetPropInternalGetKey InternalGetKey;
	fptrDeleteNetworkProperty Delete;
	fptrVisitAttrNetworkProperty VisitAttributes;
	fptrVisitRefsNetworkProperty VisitReferences;
} NetworkProperty;

NamedElement* newPoly_NetworkProperty(void);
NetworkProperty* new_NetworkProperty(void);
/*int _acceptNetworkProperty(NetworkProperty* this, NetworkProperty* c, Visitor* visitor);*/
char* NetworkProperty_MetaClassName(NetworkProperty* const this);
char* NetworkProperty_InternalGetKey(NetworkProperty* const this);
void deletePoly_NetworkProperty(NamedElement* const this);
void delete_NetworkProperty(NetworkProperty* const this);
void NetworkProperty_VisitAttributes(void* const this, char* parent, Visitor* visitor);

#endif /* H_NetworkProperty */