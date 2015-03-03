#ifndef H_Group
#define H_Group

#include <stdbool.h>
#include "hashmap.h"
#include "KMF4C.h"

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
	Instance *super;
	map_t subNodes;
	fptrGroupAddSubNodes AddSubNodes;
	fptrGroupRemoveSubNodes RemoveSubNodes;
	fptrGroupFindSubNodesByID FindSubNodesByID;
} Group;

Instance* newPoly_Group(void);
Group* new_Group(void);
char* Group_internalGetKey(void* const this);
char* Group_metaClassName(void* const this);
ContainerNode* Group_FindSubNodesByID(Group* const this, char* id);
void Group_AddSubNodes(Group* const this, ContainerNode* ptr);
void Group_RemoveSubNodes(Group* const this, ContainerNode* ptr);
void deletePoly_Group(void * const this);
void delete_Group(void * const this);
void Group_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Group_VisitPathAttributes(void* const this, char* parent, Visitor* visitor, bool recursive);
void Group_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void Group_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive);
void* Group_FindByPath(char *attribute, void * const this);

#endif /* H_Group */
