#ifndef __NodeLink_H
#define __NodeLink_H

#include <string.h>
#include <stdio.h>
#include "hashmap.h"
#include "NetworkProperty.h"

typedef struct _NodeLink NodeLink;

typedef char* (*fptrNodeLinkMetaClassName)(NodeLink*);
typedef char* (*fptrNodeLinkInternalGetKey)(NodeLink*);
typedef void (*fptrNodeLinkAddNetworkProperties)(NodeLink*, NetworkProperty*);
typedef void (*fptrNodeLinkRemoveNetworkProperties)(NodeLink*, NetworkProperty*);
typedef NetworkProperty* (*fptrNodeLinkFindNetworkPropertiesByID)(NodeLink*, char*);
typedef void (*fptrDeleteNodeLink)(NodeLink*);

typedef struct _NodeLink {
	void* pDerivedObj;
	char* networkType;
	int estimatedRate;
	char* lastCheck;
	char* zoneID;
	char* generated_KMF_ID;
	map_t networkProperties;
	fptrNodeLinkInternalGetKey InternalGetKey;
	fptrNodeLinkFindNetworkPropertiesByID FindNetworkPropertiesByID;
	fptrNodeLinkAddNetworkProperties AddNetworkProperties;
	fptrNodeLinkRemoveNetworkProperties RemoveNetworkProperties;
	fptrNodeLinkMetaClassName MetaClassName;
	fptrDeleteNodeLink Delete;
} NodeLink;

NodeLink* new_NodeLink(void);
char* NodeLink_InternalGetKey(NodeLink* const this);
NetworkProperty* NodeLink_FindNetworkPropertiesByID(NodeLink* const this, char* id);
void NodeLink_AddNetworkProperties(NodeLink* const this, NetworkProperty *ptr);
void NodeLink_RemoveNetworkProperties(NodeLink* const this, NetworkProperty *ptr);
char* NodeLink_MetaClassName(NodeLink* const this);
void delete_NodeLink(NodeLink* const this);

#endif /* __NodeLink_H */