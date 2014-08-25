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
typedef ContainerNode* (*fptrGroupFindSubNodesByID)(Group*, char*);
typedef void (*fptrGroupAddSubNodes)(Group*, ContainerNode*);
typedef void (*fptrGroupRemoveSubNodes)(Group*, ContainerNode*);
typedef void (*fptrDeleteGroup)(Group*);
typedef void (*fptrVisitAttrGroup)(void*, char*, Visitor*, int);
typedef void (*fptrVisitRefsGroup)(void*, char*, Visitor*, int);
typedef void* (*fptrFindByPathGroup)(char*, Group*);

typedef struct _Group { 
	Instance* super;
	map_t subNodes;
	fptrGroupAddSubNodes AddSubNodes;
	fptrGroupRemoveSubNodes RemoveSubNodes;
	fptrGroupInternalGetKey InternalGetKey;
	fptrGroupMetaClassName MetaClassName;
	fptrGroupFindSubNodesByID FindSubNodesByID;
	fptrDeleteGroup Delete;
	fptrVisitAttrGroup VisitAttributes;
	fptrVisitRefsGroup VisitReferences;
	fptrFindByPathGroup FindByPath;
} Group;

Instance* newPoly_Group(void);
Group* new_Group(void);
char* Group_InternalGetKey(Group* const this);
char* Group_MetaClassName(Group* const this);
ContainerNode* Group_FindSubNodesByID(Group* const this, char* id);
void Group_AddSubNodes(Group* const this, ContainerNode* ptr);
void Group_RemoveSubNodes(Group* const this, ContainerNode* ptr);
void deletePoly_Group(Instance*);
void delete_Group(Group*);
void Group_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive);
void Group_VisitReferences(void* const this, char* parent, Visitor* visitor, int recursive);
void* Group_FindByPath(char* attribute, Group* const this);

#endif /* H_Group */
