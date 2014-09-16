#ifndef H_NetworkProperty
#define H_NetworkProperty

/*#include "NamedElement.h"*/
/*#include "NetworkInfo.h"*/
/*#include "NodeLink.h"*/

typedef struct _NetworkProperty NetworkProperty;
typedef struct _NamedElement NamedElement;
/*typedef struct _NetworkInfo NetworkInfo;
typedef struct _NodeLink NodeLink;*/
typedef struct _Visitor Visitor;

typedef char* (*fptrNetPropMetaClassName)(NetworkProperty*);
typedef char* (*fptrNetPropInternalGetKey)(NetworkProperty*);
typedef void (*fptrDeleteNetworkProperty)(NetworkProperty*);
typedef void (*fptrVisitAttrNetworkProperty)(void*, char*, Visitor*);
/*typedef void (*fptrVisitRefsNetworkProperty)(void*, char*, Visitor*);*/
typedef void* (*fptrFindByPathNetworkProperty)(char*, NetworkProperty*);

typedef struct _NetworkProperty {
	NamedElement *super;
	char *value;
	char *eContainerNL;
	char *eContainerNI;
	fptrNetPropMetaClassName MetaClassName;
	fptrNetPropInternalGetKey InternalGetKey;
	fptrDeleteNetworkProperty Delete;
	fptrVisitAttrNetworkProperty VisitAttributes;
	/*fptrVisitRefsNetworkProperty VisitReferences;*/
	fptrFindByPathNetworkProperty FindByPath;
} NetworkProperty;

NamedElement* newPoly_NetworkProperty(void);
NetworkProperty* new_NetworkProperty(void);
char* NetworkProperty_MetaClassName(NetworkProperty* const this);
char* NetworkProperty_InternalGetKey(NetworkProperty* const this);
void deletePoly_NetworkProperty(NamedElement* const this);
void delete_NetworkProperty(NetworkProperty* const this);
void NetworkProperty_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void* NetworkProperty_FindByPath(char* attribute, NetworkProperty* const this);

#endif /* H_NetworkProperty */
