/*
 * AbstractComponent.c
 *
 *  Created on: Jan 27, 2015 6:43:15 PM
 *      Author: facosta
 */
#include <stdlib.h>

#include "AbstractComponent.h"
#include "AbstractTypeDefinition.h"
#include "ComponentInstance.h"
#include "Port.h"
#include "PortHandler.h"
#include "MBinding.h"
#include "NamedElement.h"

AbstractTypeDefinition *newPoly_AbstractComponent()
{
	AbstractTypeDefinition *pObj = new_AbstractTypeDefinition();
	AbstractComponent *pAbsCompObj = NULL;

	if(pObj != NULL) {
		pAbsCompObj = malloc(sizeof(AbstractComponent));
		if(pAbsCompObj == NULL) {
			return NULL;
		}
	}

	pObj->pDerivedObj = pAbsCompObj;
	pAbsCompObj->super = pObj;

	pAbsCompObj->ports = NULL;
	pAbsCompObj->receive = AbstractComponent_receive;
	pAbsCompObj->send = AbstractComponent_send;
	pAbsCompObj->delete = delete_AbstractComponent;
	pAbsCompObj->deletePoly = deletePoly_AbstractComponent;

	return pObj;
}

void AbstractComponent_receive(AbstractComponent * const this, char *msg)
{

}

void deletePoly_AbstractComponent(AbstractTypeDefinition * const this)
{
	if(this != NULL) {
		AbstractComponent *absCmp = this->pDerivedObj;
		absCmp->delete(absCmp);

		this->delete(this);
	}
}

void delete_AbstractComponent(AbstractComponent * const this)
{
	if(this != NULL) {
		if (this->ports != NULL) {
			hashmap_free(this->ports);
		}
		free(this);
	}
}

void AbstractComponent_send(AbstractComponent * const this, char *id, char *msg)
{
	AbstractTypeDefinition *pTypDefObj = this->super;
	ComponentInstance *element = (ComponentInstance*)pTypDefObj->getModelElement(pTypDefObj);
	Port *port;
	int i;

	if(element != NULL) {
		char *portName = id;

		if(hashmap_get(element->required, portName, (void**)(&port)) == MAP_OK) {
			hashmap_map *m = (hashmap_map*)port->bindings;

			for(i = 0; i < m->table_size; i++) {
				if(m->data[i].in_use != 0) {
					any_t data = (any_t)(m->data[i].data);
					MBinding *binding = (MBinding*)data;
					PortHandler *handler;
					if(hashmap_get(this->ports, binding->port->super->name, (void**)(&handler)) == MAP_OK) {
						if(handler != NULL) {
							handler->writeMsg(handler, msg);
						}
					} else {
						printf("ERROR: port not found!\n");
					}
				}
			}
		} else {
			printf("ERROR: port not found!\n");
		}
	}
}
