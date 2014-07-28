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
static char* ActionType(Actions e)
{
	switch(e)
	{
		case SET:
			return "SET";
			
		case ADD:
			return "ADD";

		case REMOVE:
			return "REMOVE";
			
		case ADD_ALL:
			return "ADD_ALL";
			
		case REMOVE_ALL:
			return "REMOVE_ALL";
			
		case RENEW_INDEX: 
			return "RENEW_INDEX";
			
		default:
			return "ERROR";
	}
}

#endif