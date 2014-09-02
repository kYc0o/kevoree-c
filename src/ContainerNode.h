#ifndef H_ContainerNode
#define H_ContainerNode
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashmap.h"
/*#include "Instance.h"*/
/*#include "ComponentInstance.h"*/
/*#include "Group.h"*/
/*#include "Visitor.h"*/
/*#include "NetworkInfo.h"
#include "tools.h"*/

typedef struct _ContainerNode ContainerNode;
typedef struct _Instance Instance;
typedef struct _ContainerRoot ContainerRoot;
typedef struct _ComponentInstance ComponentInstance;
typedef struct _Group Group;
typedef struct _NetworkInfo NetworkInfo;
typedef struct _Visitor Visitor;

typedef char* (*fptrContNodeMetaClassName)(ContainerNode*);
typedef char* (*fptrContNodeInternalGetKey)(ContainerNode*);
typedef ComponentInstance* (*fptrContNodeFindComponentsByID)(ContainerNode*, char*);
typedef ContainerNode* (*fptrContNodeFindHostsByID)(ContainerNode*, char*);
typedef Group* (*fptrContNodeFindGroupsByID)(ContainerNode*, char*);
typedef NetworkInfo* (*fptrContNodeFindNetworkInformationByID)(ContainerNode*, char*);
typedef void (*fptrContNodeAddComponents)(ContainerNode*, ComponentInstance*);
typedef void (*fptrContNodeAddHosts)(ContainerNode*, ContainerNode*);
typedef void (*fptrContNodeAddHost)(ContainerNode*, ContainerNode*);
typedef void (*fptrContNodeAddGroups)(ContainerNode*, Group*);
typedef void (*fptrContNodeAddNetworkInformation)(ContainerNode*, NetworkInfo*);
typedef void (*fptrContNodeRemoveComponents)(ContainerNode*, ComponentInstance*);
typedef void (*fptrContNodeRemoveHosts)(ContainerNode*, ContainerNode*);
typedef void (*fptrContNodeRemoveHost)(ContainerNode*, ContainerNode*);
typedef void (*fptrContNodeRemoveGroups)(ContainerNode*, Group*);
typedef void (*fptrContNodeRemoveNetworkInformation)(ContainerNode*, NetworkInfo*);
typedef void (*fptrDeleteContNode)(ContainerNode*);
typedef void (*fptrVisitAttrContainerNode)(void*, char*, Visitor*, int);
typedef void (*fptrVisitRefsContainerNode)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathContainerNode)(char*, ContainerNode*);

typedef struct _ContainerNode {
	Instance *super;
	map_t components;
	map_t hosts;
	ContainerNode *host;
	map_t networkInformation;
	map_t groups;
	ContainerRoot *eContainer;
	fptrContNodeMetaClassName MetaClassName;
	fptrContNodeInternalGetKey InternalGetKey;
	fptrContNodeFindComponentsByID FindComponentsByID;
	fptrContNodeFindHostsByID FindHostsByID;
	fptrContNodeFindGroupsByID FindGroupsByID;
	fptrContNodeFindNetworkInformationByID FindNetworkInformationByID;
	fptrContNodeAddComponents AddComponents;
	fptrContNodeAddHosts AddHosts;
	fptrContNodeAddHost AddHost;
	fptrContNodeAddGroups AddGroups;
	fptrContNodeAddNetworkInformation AddNetworkInformation;
	fptrContNodeRemoveComponents RemoveComponents;
	fptrContNodeRemoveHost RemoveHost;
	fptrContNodeRemoveHosts RemoveHosts;
	fptrContNodeRemoveGroups RemoveGroups;
	fptrContNodeRemoveNetworkInformation RemoveNetworkInformation;
	fptrDeleteContNode Delete;
	fptrVisitAttrContainerNode VisitAttributes;
	fptrVisitRefsContainerNode VisitReferences;
	fptrFindByPathContainerNode FindByPath;
} ContainerNode ;

Instance* newPoly_ContainerNode(void);
ContainerNode* new_ContainerNode(void);
char* ContainerNode_MetaClassName(ContainerNode* const this);
char* ContainerNode_InternalGetKey(ContainerNode* const this);
ComponentInstance* ContainerNode_FindComponentsByID(ContainerNode* const this, char* id);
ContainerNode* ContainerNode_FindHostsByID(ContainerNode* const this, char* id);
Group* ContainerNode_FindGroupsByID(ContainerNode* const this, char* id);
NetworkInfo* ContainerNode_FindNetworkInformationByID(ContainerNode* const this, char* id);
void ContainerNode_AddComponents(ContainerNode* const this, ComponentInstance* ptr);
void ContainerNode_AddHosts(ContainerNode* const this, ContainerNode* ptr);
void ContainerNode_AddHost(ContainerNode* const this, ContainerNode* ptr);
void ContainerNode_AddGroups(ContainerNode* const this, Group* ptr);
void ContainerNode_AddNetworkInformation(ContainerNode* const this, NetworkInfo* ptr);
void ContainerNode_RemoveComponents(ContainerNode* const this, ComponentInstance* ptr);
void ContainerNode_RemoveHost(ContainerNode* const this, ContainerNode* ptr);
void ContainerNode_RemoveHosts(ContainerNode* const this, ContainerNode* ptr);
void ContainerNode_RemoveGroups(ContainerNode* const this, Group* ptr);
void ContainerNode_RemoveNetworkInformation(ContainerNode* const this, NetworkInfo* ptr);
void deletePoly_ContainerNode(Instance* const this);
void delete_ContainerNode(ContainerNode* const this);
void ContainerNode_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive);
void ContainerNode_VisitReferences(void* const this, char* parent, Visitor* visitor);
void* ContainerNode_FindByPath(char* attribute, ContainerNode* const this);

#endif /* H_ContainerNode */
