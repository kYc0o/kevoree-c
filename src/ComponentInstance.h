#ifndef H_ComponentInstance
#define H_ComponentInstance
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include <string.h>
#include "Instance.h"
#include "Visitor.h"

typedef struct _ComponentInstance ComponentInstance;

typedef char* (*fptrCompInstInternalGetKey)(ComponentInstance*);
typedef char* (*fptrCompInstMetaClassName)(ComponentInstance*);
typedef void (*fptrDeleteComponentInstance)(ComponentInstance*);
typedef void (*fptrVisitAttrComponentInstance)(void*, char*, Visitor*);
typedef void (*fptrVisitRefsComponentInstance)(void*, char*, Visitor*);
typedef void* (*fptrFindByPathComponentInstance)(char*, ComponentInstance*);

typedef struct _ComponentInstance { 
	Instance* super;
	fptrCompInstInternalGetKey InternalGetKey;
	fptrCompInstMetaClassName MetaClassName;
	fptrDeleteComponentInstance Delete;
	/*int (*accept)(struct _ComponentInstance*,struct _ComponentInstance*, Visitor*);*/
	fptrVisitAttrComponentInstance VisitAttributes;
	fptrVisitRefsComponentInstance VisitReferences;
	fptrFindByPathComponentInstance FindByPath;
} ComponentInstance ;

Instance* newPoly_ComponentInstance(void);
ComponentInstance* new_ComponentInstance(void);
/*int _acceptComponentInstance(ComponentInstance* this, ComponentInstance* c, Visitor* visitor);*/
void deletePoly_ComponentInstance(Instance* const this);
void delete_ComponentInstance(ComponentInstance* const this);
char* ComponentInstance_MetaClassName(ComponentInstance* const this);
char* ComponentInstance_InternalGetKey(ComponentInstance* const this);
void ComponentInstance_VisitAttributes(void* const this, char* parent, Visitor* visitor);
void ComponentInstance_VisitReferences(void* const this, char* parent, Visitor* visitor);
void* ComponentInstance_FindByPath(char* attribute, ComponentInstance* const this);

#endif /* H_ComponentInstance */
