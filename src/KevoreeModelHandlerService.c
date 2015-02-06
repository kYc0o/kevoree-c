#include <stdlib.h>

#include "KevoreeModelHandlerService.h"

KevoreeModelHandlerService *new_KevoreeModelHandlerService()
{
	KevoreeModelHandlerService *pObj = malloc(sizeof(KevoreeModelHandlerService));

	if(pObj == NULL)
	{
		return NULL;
	}

	/*
	 * Pointing to itself since it's a parent
	 */
	pObj->pDerivedObj = pObj;

	pObj->getLastModel = KevoreeModelHandlerService_getLastModel;
	pObj->updateModel = KevoreeModelHandlerService_updateModel;
	pObj->getPreviousModels = KevoreeModelHandlerService_getPreviousModel;
	pObj->getNodeName = KevoreeModelHandlerService_getNodeName;
	pObj->checkModel = KevoreeModelHandlerService_checkModel;
	pObj->delete = delete_KevoreeModelHandlerService;

	return pObj;
}

void delete_KevoreeModelHandlerService(KevoreeModelHandlerService * const this)
{
	if(this != NULL) {
		free(this);
	}
}

ContainerRoot *KevoreeModelHandlerService_getLastModel(KevoreeModelHandlerService * const this)
{
	return NULL;
}

void KevoreeModelHandlerService_updateModel(KevoreeModelHandlerService * const this, ContainerRoot *model)
{

}

void KevoreeModelHandlerService_getPreviousModel(KevoreeModelHandlerService * const this, ContainerRoot *model)
{

}

char *KevoreeModelHandlerService_getNodeName(KevoreeModelHandlerService * const this)
{
	return NULL;
}

bool KevoreeModelHandlerService_checkModel(KevoreeModelHandlerService * const this, ContainerRoot *model)
{
	return false;
}
