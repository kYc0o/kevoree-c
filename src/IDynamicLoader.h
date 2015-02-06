#ifndef __DynamicLoader_H
#define __DynamicLoader_H

#include <stdbool.h>
/*#include "KevoreeModelHandlerService.h"
#include "AbstractTypeDefinition.h"
#include "AbstractNodeType.h"
#include "AbstractComponent.h"
#include "Bootstraper.h"

#include "TypeDefinition.h"
#include "DeployUnit.h"*/

typedef struct _IDynamicLoader IDynamicLoader;
typedef struct _Instance Instance;
typedef struct _AbstractTypeDefinition AbstractTypeDefinition;

typedef bool (*fptrRegisterInstance)(IDynamicLoader*, Instance*);
typedef AbstractTypeDefinition *(*fptrCreateInstance)(IDynamicLoader*, Instance*);
typedef AbstractTypeDefinition *(*fptrGetInstance)(IDynamicLoader*, Instance*);
typedef bool (*fptrDestroyInstance)(IDynamicLoader*, Instance*);
typedef bool (*fptrStartInstance)(IDynamicLoader*, Instance*);
typedef bool (*fptrStopInstance)(IDynamicLoader*, Instance*);
typedef bool (*fptrUpdateInstance)(IDynamicLoader*, Instance*);
typedef void (*fptrIDLDelete)(IDynamicLoader*);

typedef struct _IDynamicLoader {
	void *pDerivedObj;
	fptrRegisterInstance register_instance;
	fptrCreateInstance create_instance;
	fptrGetInstance get_instance;
	fptrDestroyInstance destroy_instance;
	fptrStartInstance start_instance;
	fptrStopInstance stop_instance;
	fptrUpdateInstance update_instance;
	fptrIDLDelete delete;
} IDynamicLoader;

IDynamicLoader *new_IDynamicLoader(void);
void delete_IDynamicLoader(IDynamicLoader * const this);

/*
 * Only prototypes are provided since all functions are virtual
 */
bool IDynamicLoader_register_instance(IDynamicLoader * const this, Instance *i);
AbstractTypeDefinition *IDynamicLoader_create_instance(IDynamicLoader * const this, Instance *i);
AbstractTypeDefinition *IDynamicLoader_get_instance(IDynamicLoader * const this, Instance *i);
bool IDynamicLoader_destroy_instance(IDynamicLoader * const this, Instance *i);
bool IDynamicLoader_start_instance(IDynamicLoader * const this, Instance *i);
bool IDynamicLoader_stop_instance(IDynamicLoader * const this, Instance *i);
bool IDynamicLoader_update_instance(IDynamicLoader * const this, Instance *i);
#endif
