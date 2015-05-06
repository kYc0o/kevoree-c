/*
 * AdaptationPrimitive.h
 *
 *  Created on: May 5, 2015 7:31:12 PM
 *      Author: Francisco Acosta
 *       eMail: fco.ja.ac@gmail.com
 */

#ifndef ADAPTATIONPRIMITIVE_H_
#define ADAPTATIONPRIMITIVE_H_

typedef struct _AdaptationPrimitive AdaptationPrimitive;
typedef struct _KMFContainer KMFContainer;

typedef void (*fptrDeleteAP)(AdaptationPrimitive*);

typedef struct _AdaptationPrimitive {
	fptrDeleteAP delete;
	int priority;
	int primitiveType;
	char *targetNodeName;
	KMFContainer *ref;
} AdaptationPrimitive;

AdaptationPrimitive *new_AdaptationPrimitive(void);
void delete_AdaptationPrimitive(AdaptationPrimitive * const this);

#endif /* ADAPTATIONPRIMITIVE_H_ */
