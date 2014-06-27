#ifndef H_NodeNetwork
#define H_NodeNetwork
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include <string.h>
#include "NodeLink.h"
#include "ContainerNode.h"

/*typedef struct _ContainerNode ContainerNode;*/
typedef struct _NodeNetwork NodeNetwork;

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

typedef struct _NodeNetwork {
	void* pDerivedObj;
	char* generated_KMF_ID;
	/*int count_links;
	NodeLink** links;*/
	map_t link;
	ContainerNode* initBy;
	ContainerNode* target;
	fptrNodeNetMetaClassName MetaClassName;
	fptrNodeNetInternalGetKey InternalGetKey;
	fptrNodeNetFindLinkByID FindLinkByID;
	fptrNodeNetAddLink AddLink;
	fptrNodeNetAddInitBy AddInitBy;
	fptrNodeNetAddTarget AddTarget;
	fptrNodeNetRemoveLink RemoveLink;
	fptrNodeNetRemoveInitBy RemoveInitBy;
	fptrNodeNetRemoveTarget RemoveTarget;
	fptrDeleteNodeNetwork Delete;
	/*int (*accept)(struct _NodeNetwork* this, struct _NodeNetwork* c, Visitor* visitor);*/
} NodeNetwork;

NodeNetwork* new_NodeNetwork(void);
char* NodeNetwork_MetaClassName(NodeNetwork* const this);
char* NodeNetwork_InternalGetKey(NodeNetwork* const this);
NodeLink* NodeNetwork_FindLinkByID(NodeNetwork* const this, char* id);
void NodeNetwork_AddLink(NodeNetwork* const this, NodeLink* ptr);
void NodeNetwork_AddInitBy(NodeNetwork* const this, ContainerNode* ptr);
void NodeNetwork_AddTarget(NodeNetwork* const this, ContainerNode* ptr);
void NodeNetwork_RemoveLink(NodeNetwork* const this, NodeLink* ptr);
void NodeNetwork_RemoveInitBy(NodeNetwork* const this, ContainerNode* ptr);
void NodeNetwork_RemoveTarget(NodeNetwork* const this, ContainerNode* ptr);
void delete_NodeNetwork(NodeNetwork* const this);

/*int _acceptNodeNetwork(NodeNetwork* this, NodeNetwork* c, Visitor* visitor);*/
#endif
