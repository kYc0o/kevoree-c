/*
 * IDynamicLoader.c
 *
 *  Created on: Jan 28, 2015 11:36:46 AM
 *      Author: facosta
 */

#include <stdlib.h>

#include "IDynamicLoader.h"

IDynamicLoader *new_IDynamicLoader()
{
	IDynamicLoader *pObj = malloc(sizeof(IDynamicLoader));

	if(pObj == NULL) {
		return NULL;
	}

	/*
	 * Pointing to itself since it's a parent
	 */
	pObj->pDerivedObj = pObj;

	pObj->register_instance = IDynamicLoader_register_instance;
	pObj->create_instance = IDynamicLoader_create_instance;
	pObj->get_instance = IDynamicLoader_get_instance;
	pObj->destroy_instance = IDynamicLoader_destroy_instance;
	pObj->start_instance = IDynamicLoader_start_instance;
	pObj->stop_instance = IDynamicLoader_stop_instance;
	pObj->update_instance = IDynamicLoader_update_instance;
	pObj->delete = delete_IDynamicLoader;

	return pObj;
}

void delete_IDynamicLoader(IDynamicLoader * const this)
{
	if(this != NULL) {
		free(this);
	}
}

bool IDynamicLoader_register_instance(IDynamicLoader * const this, Instance *i)
{
	return false;
}

AbstractTypeDefinition *IDynamicLoader_create_instance(IDynamicLoader * const this, Instance *i)
{
	return NULL;
}

AbstractTypeDefinition *IDynamicLoader_get_instance(IDynamicLoader * const this, Instance *i)
{
	return NULL;
}

bool IDynamicLoader_destroy_instance(IDynamicLoader * const this, Instance *i)
{
	return false;
}

bool IDynamicLoader_start_instance(IDynamicLoader * const this, Instance *i)
{
	return false;
}

bool IDynamicLoader_stop_instance(IDynamicLoader * const this, Instance *i)
{
	return false;
}

bool IDynamicLoader_update_instance(IDynamicLoader * const this, Instance *i)
{
	return false;
}
