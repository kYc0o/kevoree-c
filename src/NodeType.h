#ifndef H_NodeType
#define H_NodeType

#include <stdbool.h>
#include "KMF4C.h"
/*#include "TypeDefinition.h"*/

typedef struct _NodeType NodeType;
typedef struct _TypeDefinition TypeDefinition;
typedef struct _Visitor Visitor;

typedef char* (*fptrNodeTypeMetaClassName)(NodeType*);
typedef char* (*fptrNodeTypeInternalGetKey)(void*);
typedef void (*fptrDeleteNodeType)(NodeType*);
typedef void (*fptrVisitAttrNodeType)(void*, char*, Visitor*, bool);
typedef void (*fptrVisitRefsNodeType)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathNodeType)(char*, TypeDefinition*);

typedef struct _NodeType {
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
	TypeDefinition* super;
} NodeType;

TypeDefinition* newPoly_NodeType(void);
NodeType* new_NodeType(void);
void deletePoly_NodeType(void * const this);
void delete_NodeType(void * const this);
char* NodeType_metaClassName(void * const this);
char* NodeType_internalGetKey(void * const this);
void NodeType_VisitAttributes(void * const this, char* parent, Visitor* visitor, bool recursive);
void NodeType_VisitPathAttributes(void * const this, char* parent, Visitor* visitor, bool recursive);

#endif /* H_NodeType */
