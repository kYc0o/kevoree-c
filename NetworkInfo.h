#ifndef H_NetworkInfo
#define H_NetworkInfo

#include <stdlib.h>
#include <stdio.h>
#include "NamedElement.h"
#include "NetworkProperty.h"
#include "hashmap.h"

typedef struct _NetworkInfo NetworkInfo;

typedef char* (*fptrNetInfoMetaClassName)(NetworkInfo*);
typedef char* (*fptrNetInfoInternalGetKey)(NetworkInfo*);
typedef void (*fptrNetInfoAddValues)(NetworkInfo*, NetworkProperty*);
typedef void (*fptrNetInfoRemoveValues)(NetworkInfo*, NetworkProperty*);
typedef NetworkInfo* (*fptrNetInfoFindValuesByID)(NetworkInfo*, char*);
typedef void (*fptrDeleteNetInfo)(NetworkInfo*);

typedef struct _NetworkInfo {
	NamedElement* super;
	/*int count_values;
	NetworkProperty** values;*/
	map_t values;
	/*int (*accept)(struct _NetworkInfo*, struct _NetworkInfo*, Visitor*);*/
	fptrNetInfoMetaClassName MetaClassName;
	fptrNetInfoInternalGetKey InternalGetKey;
	fptrNetInfoAddValues AddValues;
	fptrNetInfoRemoveValues RemoveValues;
	fptrNetInfoFindValuesByID FindValuesByID;
	fptrDeleteNetInfo Delete;
} NetworkInfo;

NamedElement* newPoly_NetworkInfo(void);
NetworkInfo* new_NetworkInfo(void);
/*int _acceptNetworkInfo(NetworkInfo* this, NetworkInfo* c, Visitor* visitor);*/
char* NetworkInfo_MetaClassName(NetworkInfo* const this);
char* NetworkInfo_InternalGetKey(NetworkInfo* const this);
void NetworkInfo_AddValues(NetworkInfo* const this, NetworkProperty* ptr);
void NetworkInfo_RemoveValues(NetworkInfo* const this, NetworkProperty* ptr);
NetworkInfo* NetworkInfo_FindValuesByID(NetworkInfo* const this, char* id);
void deletePoly_NetworkInfo(NamedElement* const this);
void delete_NetworkInfo(NetworkInfo* const this);

#endif /* H_NetworkInfo */