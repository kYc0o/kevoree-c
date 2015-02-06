#include <stdlib.h>

#include "KevoreeModelHandlerService.h"
#include "AbstractTypeDefinition.h"
#include "ContainerRoot.h"

AbstractTypeDefinition *new_AbstractTypeDefinition()
{
	AbstractTypeDefinition *pAbstTypDef = NULL;

	/* Allocating memory */
	/* TODO Change for MEMB */
	pAbstTypDef = (AbstractTypeDefinition*)malloc(sizeof(AbstractTypeDefinition));

	if (pAbstTypDef == NULL)
	{
		return NULL;
	}

	/*
	 * Pointing to itself since it's a parent
	 */
	pAbstTypDef->pDerivedObj = pAbstTypDef;

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

void delete_AbstractTypeDefinition(AbstractTypeDefinition *const this)
{
	if(this != NULL)
	{
		free(this->path);
		if(this->params != NULL) {
			hashmap_free(this->params);
		}
		free(this);
	}
}

void AbstractTypeDefinition_start(AbstractTypeDefinition *const this)
{
	/*
	 * Virtual function
	 */
}

void AbstractTypeDefinition_stop(AbstractTypeDefinition *const this)
{
	/*
	 * Virtual function
	 */
}

void AbstractTypeDefinition_update(AbstractTypeDefinition *const this, int value)
{
	/*
	 * Virtual function
	 */
}

/*
 * TODO Implement model services
 */
void AbstractTypeDefinition_setModelService(AbstractTypeDefinition *const this, KevoreeModelHandlerService *handler)
{
	this->service = handler;
}

KevoreeModelHandlerService *AbstractTypeDefinition_getModelService(AbstractTypeDefinition *const this)
{
	return this->service;
}

/*
 * TODO Implement Bootstrapper
 */
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
	this->path = malloc(sizeof(char) * strlen(path) + 1);
	if(this->path != NULL) {
		strcpy(this->path, path);
	} else {
		printf("ERROR: There is no enough memory\n");
	}
}

void *AbstractTypeDefinition_getModelElement(AbstractTypeDefinition *const this)
{
	KevoreeModelHandlerService *kevService = this->service;

	if(kevService != NULL && kevService->getLastModel(kevService) != NULL)
	{
		ContainerRoot *lastmodel = kevService->getLastModel(kevService);
		return lastmodel->FindByPath(this->path, lastmodel);
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
