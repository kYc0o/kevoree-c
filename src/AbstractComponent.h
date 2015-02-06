/*
 * AbstractComponent.h
 *
 *  Created on: Jan 27, 2015 6:06:56 PM
 *      Author: facosta
 */

#ifndef APPS_KEVOREE_ABSTRACTCOMPONENT_H_
#define APPS_KEVOREE_ABSTRACTCOMPONENT_H_

#include "hashmap.h"

typedef struct _AbstractComponent AbstractComponent;
typedef struct _AbstractTypeDefinition AbstractTypeDefinition;

typedef void (*fptrReceive)(AbstractComponent*, char*);
typedef void (*fptrSend)(AbstractComponent*, char*, char*);
typedef void (*fptrACDelete)(AbstractComponent*);
typedef void (*fptrDeletePoly)(AbstractTypeDefinition*);

typedef struct _AbstractComponent {
	void *pDerivedObj;
	AbstractTypeDefinition *super;
	fptrReceive receive;
	fptrSend send;
	map_t ports;
	fptrACDelete delete;
	fptrDeletePoly deletePoly;
} AbstractComponent;

AbstractTypeDefinition *newPoly_AbstractComponent(void);
void deletePoly_AbstractComponent(AbstractTypeDefinition * const this);
void delete_AbstractComponent(AbstractComponent * const this);
void AbstractComponent_receive(AbstractComponent * const this, char *msg);
void AbstractComponent_send(AbstractComponent * const this, char *id, char *msg);

#endif /* APPS_KEVOREE_ABSTRACTCOMPONENT_H_ */
