/*
 * AdaptationPrimitive.c
 *
 *  Created on: May 5, 2015 11:47:28 PM
 *      Author: Francisco Acosta
 *       eMail: fco.ja.ac@gmail.com
 */

#include "AdaptationPrimitive.h"

#include <stdlib.h>
#include <stdio.h>

#define DEBUG 1
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

AdaptationPrimitive *new_AdaptationPrimitive()
{
	AdaptationPrimitive *pObj = malloc(sizeof(AdaptationPrimitive));

	if (pObj == NULL) {
		PRINTF("ERROR: Cannot create AdaptationPrimitive!\n");
	}

	pObj->primitiveType = -1;
	pObj->priority = -1;
	pObj->ref = NULL;
	pObj->targetNodeName = NULL;
	pObj->delete = delete_AdaptationPrimitive;

	return pObj;
}

void delete_AdaptationPrimitive(AdaptationPrimitive * const this)
{
	if (this->targetNodeName != NULL) {
		free(this->targetNodeName);
	}
	free(this);
}
