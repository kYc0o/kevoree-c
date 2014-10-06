#ifndef __KevoreeModelHandlerService_H
#define __KevoreeModelHandlerService_H

/*#include "ContainerRoot.h"*/
#include "lib/list.h"
#include <stdbool.h>

typedef struct _KevoreeModelHandlerService KevoreeModelHandlerService;
typedef struct _ContainerRoot ContainerRoot;

typedef ContainerRoot *(*fptrGetLastModel)(KevoreeModelHandlerService*);
typedef void (*fptrUpdateModel)(KevoreeModelHandlerService*, ContianerRoot*);
typedef void (*fptrGetPreviousModels)(KevoreeModelHandlerService*, list_t);
typedef char *(*fptrGetNodeName)(KevoreeModelHandlerService*);
typedef bool (*fptrCheckModel)(KevoreeModelHandlerService*, ContainerRoot*);

typedef struct _KevoreeModelHandlerService {
	fptrGetLastModel getLastModel;
	fptrUpdateModel updateModel;
	fptrGetPreviousModels getPreviousModels;
	fptrGetNodeName getNodeName;
	fptrCheckModel checkModel;
} KevoreeModelHandlerService;

#endif /* __KevoreeModelHandlerService_H */
