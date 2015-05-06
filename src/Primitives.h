/*
 * Primitives.h
 *
 *  Created on: May 5, 2015 7:48:33 PM
 *      Author: Francisco Acosta
 *       eMail: fco.ja.ac@gmail.com
 */

#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#define PRIORITY_MAX 11

typedef enum Primitives Primitives;

enum  Primitives {
	StartInstance,
	UpdateInstance,
	UpdateDictionaryInstance,
	AddBinding,
	AddInstance,
	AddDeployUnit,
	UpdateDeployUnit,
	UpdateBinding,
	RemoveDeployUnit,
	RemoveInstance,
	RemoveBinding,
	StopInstance
};

// schedule

static const int Priority_Primitives(Primitives e)
{
	switch(e)
	{
	case StartInstance: return 11;
	case UpdateInstance: return 10;
	case UpdateDictionaryInstance : return 9;
	case AddBinding: return 8;
	case AddInstance: return 7;
	case AddDeployUnit : return 6;
	case UpdateDeployUnit: return 5;
	case UpdateBinding: return 4;
	case RemoveDeployUnit: return 3;
	case RemoveInstance: return 2;
	case RemoveBinding : return 1;
	case StopInstance: return 0;
	}
}

#endif /* PRIMITIVES_H_ */
