#ifndef H_Group
#define H_Group
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include <string.h>
#include "ContainerNode.h"
#include "Instance.h"
#include "hashmap.h"

typedef struct _ContainerNode ContainerNode;
typedef struct _Group Group;

typedef char* (*fptrGroupInternalGetKey)(Group*);
typedef char* (*fptrGroupMetaClassName)(Group*);
typedef void (*fptrGroupAddSubNodes)(Group*, ContainerNode*);
typedef void (*fptrGroupRemoveSubNodes)(Group*, ContainerNode*);
typedef void (*fptrDeleteGroup)(Group*);

typedef struct _Group { 
	Instance* super;
	fptrGroupInternalGetKey InternalGetKey;
	fptrGroupMetaClassName MetaClassName;
	/*int count_subNodes;
	struct ContainerNode **subNodes;*/
	map_t subNodes;
	/*int (*accept)(struct _Group*, struct _Group*, Visitor*);*/
	fptrGroupAddSubNodes AddSubNodes;
	fptrGroupRemoveSubNodes RemoveSubNodes;
	fptrDeleteGroup Delete;
} Group;

Instance* newPoly_Group(void);
Group* new_Group(void);
char* Group_InternalGetKey(Group* const this);
char* Group_MetaClassName(Group* const this);
void Group_AddSubNodes(Group* const this, ContainerNode* ptr);
void Group_RemoveSubNodes(Group* const this, ContainerNode* ptr);
/*int _acceptGroup(Group* this, Group* c, Visitor* visitor);*/
void deletePoly_Group(Instance*);
void delete_Group(Group*);

#endif /* H_Group */
