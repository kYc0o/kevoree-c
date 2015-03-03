#ifndef H_NodeNetwork
#define H_NodeNetwork

#include "hashmap.h"
#include "KMF4C.h"

typedef struct _NodeNetwork NodeNetwork;
typedef struct _ContainerNode ContainerNode;
typedef struct _NodeLink NodeLink;
typedef struct _Visitor Visitor;

typedef char* (*fptrNodeNetMetaClassName)(NodeNetwork*);
typedef char* (*fptrNodeNetInternalGetKey)(NodeNetwork*);
typedef NodeLink* (*fptrNodeNetFindLinkByID)(NodeNetwork*, char*);
typedef void (*fptrNodeNetAddLink)(NodeNetwork*, NodeLink*);
typedef void (*fptrNodeNetAddInitBy)(NodeNetwork*, ContainerNode*);
typedef void (*fptrNodeNetAddTarget)(NodeNetwork*, ContainerNode*);
typedef void (*fptrNodeNetRemoveLink)(NodeNetwork*, NodeLink*);
typedef void (*fptrNodeNetRemoveInitBy)(NodeNetwork*, ContainerNode*);
typedef void (*fptrNodeNetRemoveTarget)(NodeNetwork*, ContainerNode*);
typedef void (*fptrDeleteNodeNetwork)(NodeNetwork*);
typedef void (*fptrVisitAttrNodeNetwork)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsNodeNetwork)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathNodeNetwork)(char*, NodeNetwork*);

typedef struct _NodeNetwork {
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
	char generated_KMF_ID[9];
	map_t link;
	ContainerNode *initBy;
	ContainerNode *target;
	fptrNodeNetFindLinkByID FindLinkByID;
	fptrNodeNetAddLink AddLink;
	fptrNodeNetAddInitBy AddInitBy;
	fptrNodeNetAddTarget AddTarget;
	fptrNodeNetRemoveLink RemoveLink;
	fptrNodeNetRemoveInitBy RemoveInitBy;
	fptrNodeNetRemoveTarget RemoveTarget;
} NodeNetwork;

NodeNetwork* new_NodeNetwork(void);
char* NodeNetwork_metaClassName(void * const this);
char* NodeNetwork_internalGetKey(void * const this);
NodeLink* NodeNetwork_FindLinkByID(NodeNetwork* const this, char* id);
void NodeNetwork_AddLink(NodeNetwork* const this, NodeLink* ptr);
void NodeNetwork_AddInitBy(NodeNetwork* const this, ContainerNode* ptr);
void NodeNetwork_AddTarget(NodeNetwork* const this, ContainerNode* ptr);
void NodeNetwork_RemoveLink(NodeNetwork* const this, NodeLink* ptr);
void NodeNetwork_RemoveInitBy(NodeNetwork* const this, ContainerNode* ptr);
void NodeNetwork_RemoveTarget(NodeNetwork* const this, ContainerNode* ptr);
void delete_NodeNetwork(void * const this);
void NodeNetwork_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void NodeNetwork_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void NodeNetwork_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void NodeNetwork_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* NodeNetwork_FindByPath(char* attribute, void * const this);

#endif /* H_NodeNetwork */
