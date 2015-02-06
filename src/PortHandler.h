/*
 * PortHandler.h
 *
 *  Created on: Jan 27, 2015
 *      Author: facosta
 */

#ifndef APPS_KEVOREE_PORTHANDLER_H_
#define APPS_KEVOREE_PORTHANDLER_H_

typedef struct _PortHandler PortHandler;

typedef void (*fptrWriteMsg)(PortHandler*, char*);
typedef void (*fptrPHDelete)(PortHandler*);

typedef struct _PortHandler {
	void *pDerivedObj;
	fptrWriteMsg writeMsg;
	fptrPHDelete delete;
} PortHandler;

PortHandler *new_PortHandler(void);
void delete_PortHandler(PortHandler * const this);

/*
 * INFO Only prototypes are provided since all functions are virtual
 */
void PortHandler_writeMsg(PortHandler * const this, char *msg);

#endif /* APPS_KEVOREE_PORTHANDLER_H_ */
