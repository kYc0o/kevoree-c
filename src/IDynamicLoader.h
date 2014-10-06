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
typedef bool (*fptrDestroyInstance)(IDynamicLoader*, Instance);
typedef bool (*fptrStartInstance)(IDynamicLoader*, Instance*);
typedef bool (*fptrStopInstance)(IDynamicLoader*, Instance*);
typedef bool (*fptrUpdateInstance)(IDynamicLoader*, Instance*);

typedef struct _IDynamicLoader {
	fptrRegisterInstance register_instance;
	fptrCreateInstance create_instance;
	fptrGetInstance get_instance;
	fptrDestroyInstance destroy_instance;
	fptrStartInstance start_instance;
	fptrStopInstance stop_instance;
	fptrUpdateInstance update_instance;
} IDynamicLoader;

#endif
