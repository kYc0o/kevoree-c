/*
 * ActionType.c
 *
 *  Created on: May 6, 2015 2:44:33 PM
 *      Author: Francisco Acosta
 *       eMail: fco.ja.ac@gmail.com
 */

#include "ActionType.h"

char* ActionType(Actions e)
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
