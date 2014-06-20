#ifndef H_ContainerNode
#define H_ContainerNode
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include <string.h>
#include "Instance.h"
#include "ComponentInstance.h"
#include "Group.h"
#include "NetworkInfo.h"
#include "hashmap.h"

typedef struct _ContainerNode ContainerNode;
typedef struct _Group Group;

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

typedef struct _ContainerNode {
	Instance* super;
	/*int count_components;
	struct ComponentInstance** components;*/
	map_t components;
	map_t hosts;
	ContainerNode* host;
	/*int count_networkInformation;
	struct NetworkInfo** networkInformation;*/
	map_t networkInformation;
	/*int count_groups;
	struct Group** groups;*/
	map_t groups;
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
	/*int (*accept)(struct _ContainerNode*, struct _ContainerNode*, Visitor*);*/
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
/*int _acceptContainerNode(ContainerNode* this, ContainerNode* c, Visitor* visitor);*/
void deletePoly_ContainerNode(Instance* const this);
void delete_ContainerNode(ContainerNode* const this);

#endif
