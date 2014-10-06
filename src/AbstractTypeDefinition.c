#include "KevoreeModelHandlerService.h"
#include "Bootstraper.h"
#include "AbstractTypeDefinition.h"

AbstractTypeDefinition *new_AbstractTypeDefinition()
{
	AbstractTypeDefinition *pAbstTypDef = NULL;

	/* Allocating memory */
	/* TODO Change for MEMB */
	pAbstTypDef = (AbstractTypeDefinition*)my_malloc(sizeof(AbstractTypeDefinition));

	if (pAbstTypDef == NULL)
	{
		return NULL;
	}

	pAbstTypDef->pDerivedObj = pAbstTypDef;  /* Pointing to derived object */

	pAbstTypDef->service = NULL;
	pAbstTypDef->bootstrapService = NULL;
	pAbstTypDef->path = NULL;
	pAbstTypDef->params = NULL;
	pAbstTypDef->start = AbstractTypeDefinition_start;
	pAbstTypDef->stop = AbstractTypeDefinition_stop;
	pAbstTypDef->update = AbstractTypeDefinition_update;
	pAbstTypDef->setModelService = AbstractTypeDefinition_setModelService;
	pAbstTypDef->getModelService = AbstractTypeDefinition_getModelService;
	pAbstTypDef->setBootStrapperService = AbstractTypeDefinition_setBootStrapperService;
	pAbstTypDef->getBootStrapperService = AbstractTypeDefinition_getBootStrapperService;
	pAbstTypDef->setPath = AbstractTypeDefinition_setPath;
	pAbstTypDef->getModelElement = AbstractTypeDefinition_getModelElement;
	pAbstTypDef->updateParam = AbstractTypeDefinition_updateParam;
	pAbstTypDef->delete = delete_AbstractTypeDefinition;

	return pAbstTypDef;
}

void delete_AbstractTypeDefinition(void *const this)
{
	AbstractTypeDefinition *pAbstTypDef = (AbstractTypeDefinition*)this;

	if(pAbstTypDef != NULL)
	{
		free(pAbstTypDef->path);
		hashmap_free(pAbstTypDef->params);
		free(pAbstTypDef);
	}
}

void AbstractTypeDefinition_start(AbstractTypeDefinition *const this)
{

}

void AbstractTypeDefinition_stop(AbstractTypeDefinition *const this)
{

}

void AbstractTypeDefinition_update(AbstractTypeDefinition *const this)
{

}

void AbstractTypeDefinition_setModelService(AbstractTypeDefinition *const this, KevoreeModelHandlerService *handler)
{
	this->service = handler;
}

KevoreeModelHandlerService *AbstractTypeDefinition_getModelService(AbstractTypeDefinition *const this)
{
	return this->service;
}

void AbstractTypeDefinition_setBootStrapperService(AbstractTypeDefinition *const this, Bootstraper *bootstrapService)
{
	this->bootstrapService = bootstrapService;
}

Bootstraper *AbstractTypeDefinition_getBootStrapperService(AbstractTypeDefinition *const this)
{
	return this->bootstrapService;
}

void AbstractTypeDefinition_setPath(AbstractTypeDefinition *const this, char *path)
{
	this->path = path;
}

KMFContainer *AbstractTypeDefinition_getModelElement(AbstractTypeDefinition *const this)
{
	KevoreeModelHandlerService *kevService = this->service;

	if(kevService != NULL && kevService->getLastModel(kevService) != NULL )
	{
		ContainerRoot *lastmodel = kevService->getLastModel(kevService);
		return lastmodel->findByPath(this->path);
	}
	else
	{
		return NULL;
	}
}

void AbstractTypeDefinition_updateParam(AbstractTypeDefinition *const this, char *key, char *value)
{
	if(this->params == NULL)
	{
		this->params = hashmap_new();
		hashmap_put(this->params, key, value);
	}
	else if(hashmap_get(this->params, key, (void**)(&value)) == MAP_MISSING)
	{
		hashmap_put(this->params, key, value);
	}
	else
	{
		hashmap_remove(this->params, key);
		hashmap_put(this->params, key, value);
	}
}
