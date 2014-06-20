#ifndef H_Instance
#define H_Instance

#include <stdlib.h>
#include "NamedElement.h"
#include "TypeDefinition.h"

typedef struct _Instance Instance;

typedef char* (*fptrInstInternalGetKey)(Instance*);
typedef char* (*fptrInstMetaClassName)(Instance*);
typedef void (*fptrAddTypeDefinition)(Instance*, TypeDefinition*);
typedef void (*fptrDeleteInstance)(Instance*);

typedef struct _Instance {
	NamedElement* super;
	void* pDerivedObj;
	char* metaData;
	int started;
	TypeDefinition* TypeDefinition;
	fptrAddTypeDefinition AddTypeDefinition;
	/*int (*accept)(struct _Instance*, struct _Instance*, Visitor*);*/
	fptrInstInternalGetKey InternalGetKey;
	fptrInstMetaClassName MetaClassName;
	fptrDeleteInstance Delete;
} Instance;

NamedElement* newPoly_Instance(void);
Instance* new_Instance(void);
void Instance_AddTypeDefinition(Instance* this, TypeDefinition* ptr);
/*int _acceptInstance(Instance* this, Instance* c, Visitor* visitor);*/
char* Instance_InternalGetKey(Instance* const this);
char* Instance_MetaClassName(Instance* const this);
void deletePoly_Instance(NamedElement* const this);
void delete_Instance(Instance* const this);

#endif /* H_Instance */
