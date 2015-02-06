/*
 * PortHandler.c
 *
 *  Created on: Jan 27, 2015
 *      Author: facosta
 */
#include <stdlib.h>

#include "PortHandler.h"

PortHandler *new_PortHandler()
{
	PortHandler *pObj = malloc(sizeof(PortHandler));

	if(pObj == NULL) {
		return NULL;
	}

	/*
	 * Pointing to itself since it's a parent
	 */
	pObj->pDerivedObj = pObj;

	pObj->writeMsg = PortHandler_writeMsg;
	pObj->delete = delete_PortHandler;

	return pObj;
}

void delete_PortHandler(PortHandler * const this)
{
	if(this != NULL) {
		free(this);
	}
}

void PortHandler_writeMsg(PortHandler * const this, char *msg)
{

}
