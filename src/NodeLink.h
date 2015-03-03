#ifndef __NodeLink_H
#define __NodeLink_H

#include "hashmap.h"
#include "KMF4C.h"

typedef struct _NodeLink NodeLink;
typedef struct _NetworkProperty NetworkProperty;
typedef struct _Visitor Visitor;

typedef char* (*fptrNodeLinkMetaClassName)(NodeLink*);
typedef char* (*fptrNodeLinkInternalGetKey)(NodeLink*);
typedef void (*fptrNodeLinkAddNetworkProperties)(NodeLink*, NetworkProperty*);
typedef void (*fptrNodeLinkRemoveNetworkProperties)(NodeLink*, NetworkProperty*);
typedef NetworkProperty* (*fptrNodeLinkFindNetworkPropertiesByID)(NodeLink*, char*);
typedef void (*fptrDeleteNodeLink)(NodeLink*);
typedef void (*fptrVisitAttrNodeLink)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsNodeLink)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathNodeLink)(char*, NodeLink*);

typedef struct _NodeLink {
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
	char *networkType;
	int estimatedRate;
	char *lastCheck;
	char *zoneID;
	char generated_KMF_ID[9];
	map_t networkProperties;
	fptrNodeLinkFindNetworkPropertiesByID FindNetworkPropertiesByID;
	fptrNodeLinkAddNetworkProperties AddNetworkProperties;
	fptrNodeLinkRemoveNetworkProperties RemoveNetworkProperties;
} NodeLink;

NodeLink* new_NodeLink(void);
char* NodeLink_internalGetKey(void * const this);
NetworkProperty* NodeLink_FindNetworkPropertiesByID(NodeLink* const this, char* id);
void NodeLink_AddNetworkProperties(NodeLink* const this, NetworkProperty *ptr);
void NodeLink_RemoveNetworkProperties(NodeLink* const this, NetworkProperty *ptr);
char* NodeLink_metaClassName(void * const this);
void delete_NodeLink(void * const this);
void NodeLink_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void NodeLink_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void NodeLink_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void NodeLink_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* NodeLink_FindByPath(char* attribute, void * const this);

#endif /* __NodeLink_H */
