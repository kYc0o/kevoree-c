#ifndef H_Group
#define H_Group

#include <stdbool.h>
#include "hashmap.h"

typedef struct _ContainerNode ContainerNode;
typedef struct _Group Group;
typedef struct _Instance Instance;
typedef struct _Visitor Visitor;

typedef char* (*fptrGroupInternalGetKey)(Group*);
typedef char* (*fptrGroupMetaClassName)(Group*);
typedef ContainerNode* (*fptrGroupFindSubNodesByID)(Group*, char*);
typedef void (*fptrGroupAddSubNodes)(Group*, ContainerNode*);
typedef void (*fptrGroupRemoveSubNodes)(Group*, ContainerNode*);
typedef void (*fptrDeleteGroup)(Group*);
typedef void (*fptrVisitAttrGroup)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsGroup)(void*, char*, Visitor*, bool);
typedef void* (*fptrFindByPathGroup)(char*, Group*);

typedef struct _Group { 
	Instance *super;
	map_t subNodes;
	char *eContainer;
	fptrGroupAddSubNodes AddSubNodes;
	fptrGroupRemoveSubNodes RemoveSubNodes;
	fptrGroupInternalGetKey InternalGetKey;
	fptrGroupMetaClassName MetaClassName;
	fptrGroupFindSubNodesByID FindSubNodesByID;
	fptrDeleteGroup Delete;
	fptrVisitAttrGroup VisitAttributes;
	fptrVisitAttrGroup VisitPathAttributes;
	fptrVisitRefsGroup VisitReferences;
	fptrVisitRefsGroup VisitPathReferences;
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
void Group_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Group_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Group_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void Group_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* Group_FindByPath(char* attribute, Group* const this);

#endif /* H_Group */
