#ifndef __ActionType_H
#define __ActionType_H

#include <string.h>
/**
 * Author: fco.ja.ac@gmail.com
 * Date: 21/07/14
 * Time: 16:34
 */

typedef enum Actions Actions;

enum Actions
{
	SET=0,
	ADD=1,
	REMOVE=2,
	ADD_ALL=3,
	REMOVE_ALL=4,
	RENEW_INDEX=5
};

// convert enum ActionType to String  improve later
/*static std::string ActionType(actions e)*/
char* ActionType(Actions e);

#endif
