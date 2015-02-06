#ifndef __KevoreeModelHandlerService_H
#define __KevoreeModelHandlerService_H

#include <stdbool.h>

typedef struct _KevoreeModelHandlerService KevoreeModelHandlerService;
typedef struct _ContainerRoot ContainerRoot;

typedef ContainerRoot *(*fptrGetLastModel)(KevoreeModelHandlerService*);
typedef void (*fptrUpdateModel)(KevoreeModelHandlerService*, ContainerRoot*);
typedef void (*fptrGetPreviousModel)(KevoreeModelHandlerService*, ContainerRoot*);
typedef char *(*fptrGetNodeName)(KevoreeModelHandlerService*);
typedef bool (*fptrCheckModel)(KevoreeModelHandlerService*, ContainerRoot*);
typedef void (*fptrDelete)(KevoreeModelHandlerService*);

typedef struct _KevoreeModelHandlerService {
	void *pDerivedObj;
	fptrGetLastModel getLastModel;
	fptrUpdateModel updateModel;
	fptrGetPreviousModel getPreviousModels;
	fptrGetNodeName getNodeName;
	fptrCheckModel checkModel;
	fptrDelete delete;
} KevoreeModelHandlerService;

KevoreeModelHandlerService *new_KevoreeModelHandlerService(void);
void delete_KevoreeModelHandlerService(KevoreeModelHandlerService * const this);

/*
 * INFO Only prototypes are provided since all functions are virtual
 */
ContainerRoot *KevoreeModelHandlerService_getLastModel(KevoreeModelHandlerService * const this);
void KevoreeModelHandlerService_updateModel(KevoreeModelHandlerService * const this, ContainerRoot *model);
void KevoreeModelHandlerService_getPreviousModel(KevoreeModelHandlerService * const this, ContainerRoot *model);
char *KevoreeModelHandlerService_getNodeName(KevoreeModelHandlerService * const this);
bool KevoreeModelHandlerService_checkModel(KevoreeModelHandlerService * const this, ContainerRoot *model);

#endif /* __KevoreeModelHandlerService_H */
