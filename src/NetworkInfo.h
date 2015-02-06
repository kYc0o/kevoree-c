#ifndef H_NetworkInfo
#define H_NetworkInfo

#include "hashmap.h"

typedef struct _NetworkInfo NetworkInfo;
typedef struct _NamedElement NamedElement;
typedef struct _NetworkProperty NetworkProperty;

typedef char* (*fptrNetInfoMetaClassName)(NetworkInfo*);
typedef char* (*fptrNetInfoInternalGetKey)(NetworkInfo*);
typedef void (*fptrNetInfoAddValues)(NetworkInfo*, NetworkProperty*);
typedef void (*fptrNetInfoRemoveValues)(NetworkInfo*, NetworkProperty*);
typedef NetworkProperty* (*fptrNetInfoFindValuesByID)(NetworkInfo*, char*);
typedef void (*fptrDeleteNetInfo)(NetworkInfo*);
typedef void (*fptrVisitAttrNetworkInfo)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsNetworkInfo)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathNetworkInfo)(char*, NetworkInfo*);

typedef struct _NetworkInfo {
	NamedElement *super;
	map_t values;
	char *eContainer;
	fptrNetInfoMetaClassName MetaClassName;
	fptrNetInfoInternalGetKey InternalGetKey;
	fptrNetInfoAddValues AddValues;
	fptrNetInfoRemoveValues RemoveValues;
	fptrNetInfoFindValuesByID FindValuesByID;
	fptrDeleteNetInfo Delete;
	fptrVisitAttrNetworkInfo VisitAttributes;
	fptrVisitAttrNetworkInfo VisitPathAttributes;
	fptrVisitRefsNetworkInfo VisitReferences;
	fptrVisitRefsNetworkInfo VisitPathReferences;
	fptrFindByPathNetworkInfo FindByPath;
} NetworkInfo;

NamedElement* newPoly_NetworkInfo(void);
NetworkInfo* new_NetworkInfo(void);
char* NetworkInfo_MetaClassName(NetworkInfo* const this);
char* NetworkInfo_InternalGetKey(NetworkInfo* const this);
void NetworkInfo_AddValues(NetworkInfo* const this, NetworkProperty* ptr);
void NetworkInfo_RemoveValues(NetworkInfo* const this, NetworkProperty* ptr);
NetworkProperty* NetworkInfo_FindValuesByID(NetworkInfo* const this, char* id);
void deletePoly_NetworkInfo(NamedElement* const this);
void delete_NetworkInfo(NetworkInfo* const this);
void NetworkInfo_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void NetworkInfo_VisitPathAttributes(void *const this, char *parent, Visitor *visitor);
void NetworkInfo_VisitReferences(void* const this, char* parent, Visitor* visitor);
void NetworkInfo_VisitPathReferences(void *const this, char *parent, Visitor *visitor);
void* NetworkInfo_FindByPath(char* attribute, NetworkInfo* const this);

#endif /* H_NetworkInfo */
