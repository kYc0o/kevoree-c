/*
 * Planner.c
 *
 *  Created on: May 5, 2015 9:57:23 PM
 *      Author: Francisco Acosta
 *       eMail: fco.ja.ac@gmail.com
 */

#include "Planner.h"
#include "ContainerRoot.h"
#include "TraceSequence.h"
#include "AdaptationPrimitive.h"
#include "Primitives.h"
#include "KMF4C.h"
#include "ContainerNode.h"
#include "Instance.h"
#include "DictionaryValue.h"
#include "ActionType.h"
#include "TypeDefinition.h"
#include "DeployUnit.h"
#include "ComponentInstance.h"

#include "list.h"

#include <stdbool.h>

#define DEBUG 1
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif
LIST(adaptations);

static void AdaptationModel_add(AdaptationPrimitive *ptr)
{
	PRINTF("INFO: Adding trace %s\n", ptr->ref->path);
	list_add(adaptations, ptr);
}

void Planner_compareModels(ContainerRoot *currModel, ContainerRoot *targetModel, char *nodeName, TraceSequence *traces)
{
	ContainerNode *currentNode = currModel->FindNodesByID(currModel, nodeName);
	ContainerNode *targetNode = targetModel->FindNodesByID(currModel, nodeName);
	int tracesLength, i;
	bool isFirst = true;

	tracesLength = list_length(traces->traces_list);
	PRINTF("INFO: Received traces of length %d\n", tracesLength);
	ModelTrace *trace;

	list_init(adaptations);

	for (trace = list_head(traces->traces_list); trace != NULL; trace = list_item_next(trace)) {
		PRINTF("INFO: Passing trace %s\n", trace->refName);

		KMFContainer *modelElement = targetModel->FindByPath(trace->srcPath, targetModel);

		if(!strcmp(trace->refName, "components"))
		{
			if(!strcmp(trace->srcPath, targetNode->path))
			{
				if (trace->vt->getType() == ADD) {
					KMFContainer *elemToAdd = targetModel->FindByPath(((ModelAddTrace*)trace)->previousPath, targetModel);
					AdaptationModel_add(Planner_adapt(AddInstance, elemToAdd));
				} else if (trace->vt->getType() == REMOVE) {
					KMFContainer *elemToAdd = currModel->FindByPath(((ModelRemoveTrace*)trace)->objPath, currModel);
					AdaptationModel_add(Planner_adapt(StopInstance, elemToAdd));
					AdaptationModel_add(Planner_adapt(RemoveInstance, elemToAdd));
				} else {
					PRINTF("ERROR: Cannot cast ModelTrace!\n");
				}
			}

		} else if(!strcmp(trace->refName, "started")) {
			if (
					(
							(!strcmp(modelElement->metaClassName(modelElement), "ComponentInstance")) /*||
							(!strcmp(modelElement->metaClassName(modelElement), "ContainerNode")) ||
							(!strcmp(modelElement->metaClassName(modelElement), "Group"))*/
					) &&
					(trace->vt->getType() == SET)
				) {
				ModelSetTrace *modelsettrace = (ModelSetTrace*)trace;

				if (!strcmp(modelsettrace->srcPath, targetNode->path)) {
					PRINTF("HARAKIRI: %s\n", modelsettrace->vt->ToString(modelsettrace));
				} else {
					if (!strcmp(modelsettrace->content, "1")) {
						AdaptationModel_add(Planner_adapt(StartInstance, modelElement));
					} else {
						AdaptationModel_add(Planner_adapt(StopInstance, modelElement));
					}
				}
			}
		} else if(!strcmp(trace->refName, "value")) {
			if (!strcmp(modelElement->metaClassName(modelElement), "DictionaryValue")) {
				KMFContainer *container = targetModel->FindByPath(modelElement->eContainer, targetModel);
				KMFContainer *container2 = targetModel->FindByPath(container->eContainer, targetModel);
				AdaptationModel_add(Planner_adapt(UpdateDictionaryInstance, container2));
				/*
				 * Check why modelElement->eContainer->eContainer
				 */
			}
		} else if (!strcmp(trace->refName, "typeDefinition")) {
			if (!strcmp(modelElement->metaClassName(modelElement), "ComponentInstance")) {
				ComponentInstance *ci = (ComponentInstance*)modelElement;
				TypeDefinition *t = ci->super->typeDefinition;
				DeployUnit *du = t->deployUnits;
				AdaptationModel_add(Planner_adapt(AddDeployUnit, du));
			}
		}

	}
}

list_t Planner_schedule()
{
	int i, j, adaptLength;
	bool isFirst = true;
	LIST(sortedAdapt);
	list_init(sortedAdapt);

	AdaptationPrimitive *ap;

	for (j = 0; j <= PRIORITY_MAX; ++j) {
		adaptLength = list_length(adaptations);
		for (i = 0; i < adaptLength; ++i) {
			ap = list_pop(adaptations);
			if (ap->priority == j) {
				list_add(sortedAdapt, ap);
			} else {
				list_add(adaptations, ap);
			}
		}
	}

	return sortedAdapt;
}

AdaptationPrimitive *Planner_adapt(Primitives p, KMFContainer *elem)
{
	AdaptationPrimitive *ccmd = new_AdaptationPrimitive();

	if (ccmd == NULL) {
		PRINTF("ERROR: AdaptationPrimitive cannot be created!\n");
		return NULL;
	}

	ccmd->primitiveType = p;
	ccmd->priority = Priority_Primitives(p);
	ccmd->ref = elem;
	return ccmd;
}
