/*
 * Planner.h
 *
 *  Created on: May 5, 2015 8:20:22 PM
 *      Author: Francisco Acosta
 *       eMail: fco.ja.ac@gmail.com
 */

#ifndef PLANNER_H_
#define PLANNER_H_

#include "Primitives.h"
#include "list.h"

/*typedef struct _Planner Planner;*/
typedef struct _AdaptationModel AdaptationModel;
typedef struct _ContainerRoot ContainerRoot;
typedef struct _TraceSequence TraceSequence;
typedef struct _AdaptationPrimitive AdaptationPrimitive;
typedef struct _KMFContainer KMFContainer;

/*typedef AdaptationModel *(*fptrCompareModels)(Planner*, ContainerRoot*, ContainerRoot*, char*, TraceSequence*);
typedef AdaptationModel *(*fptrSchedule)(Planner*, AdaptationModel*, char*);
typedef AdaptationPrimitive *(*fptrAdapt)(Planner*, Primitives, KMFContainer*);
typedef void (*fptrDelete)(Planner*);

typedef struct _Planner {
	fptrDelete delete;
	fptrCompareModels compareModels;
	fptrSchedule schedule;
	fptrAdapt adapt;
} Planner;

Planner *new_Planner(void);
void delete_Planner(Planner * const this);
AdaptationModel *Planner_compareModels(Planner * const this, ContainerRoot *currModel, ContainerRoot *targetModel, char *nodeName, TraceSequence *traces);
AdaptationModel *Planner_schedule(Planner * const this, AdaptationModel *adaptationModel, char *nodeName);
AdaptationPrimitive *Planner_adapt(Planner * const this, Primitives p, KMFContainer *elem);*/

void Planner_compareModels(ContainerRoot *currModel, ContainerRoot *targetModel, char *nodeName, TraceSequence *traces);
list_t Planner_schedule(void);
AdaptationPrimitive *Planner_adapt(Primitives p, KMFContainer *elem);

#endif /* SRC_PLANNER_H_ */
