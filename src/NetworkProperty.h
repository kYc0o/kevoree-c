#ifndef H_NetworkProperty
#define H_NetworkProperty

#include <stdlib.h>
#include <string.h>
#include "NamedElement.h"

typedef struct _NetworkProperty NetworkProperty;

typedef char* (*fptrNetPropMetaClassName)(NetworkProperty*);
typedef char* (*fptrNetPropInternalGetKey)(NetworkProperty*);
typedef void (*fptrDeleteNetworkProperty)(NetworkProperty*);

typedef struct _NetworkProperty {
	NamedElement* super;
	char* value;
	/*int (*accept)(struct _NetworkProperty*, struct _NetworkProperty*, Visitor*);*/
	fptrNetPropMetaClassName MetaClassName;
	fptrNetPropInternalGetKey InternalGetKey;
	fptrDeleteNetworkProperty Delete;
} NetworkProperty;

NamedElement* newPoly_NetworkProperty(void);
NetworkProperty* new_NetworkProperty(void);
/*int _acceptNetworkProperty(NetworkProperty* this, NetworkProperty* c, Visitor* visitor);*/
char* NetworkProperty_MetaClassName(NetworkProperty* const this);
char* NetworkProperty_InternalGetKey(NetworkProperty* const this);
void deletePoly_NetworkProperty(NamedElement* const this);
void delete_NetworkProperty(NetworkProperty* const this);

#endif /* H_NetworkProperty */