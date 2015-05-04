#ifndef TraceSequence_H
#define TraceSequence_H

/*#include <list>
#include <iostream>*/
#include "list.h"
#include "KMF4C.h"
/*#include <microframework/api/trace/ModelTrace.h>*/
#include "ModelTrace.h"
/*#include <microframework/api/KMFFactory.h>
#include <microframework/api/utils/KevoreeException.h>*/


/**
 * Author: fco.ja.ac@gmail.com
 * Date: 16/12/14
 * Time: 16:56
 */

typedef struct _TraceSequence TraceSequence;
typedef struct _ContainerRoot ContainerRoot;

typedef TraceSequence* (*fptrPopulate)(TraceSequence*, list_t);
typedef void (*fptrAppend)(TraceSequence*, TraceSequence*);
typedef char *(*fptrTracesToString)(TraceSequence*);

typedef struct _TraceSequence {
	LIST_STRUCT(traces_list);
	fptrAppend append;
	fptrPopulate populate;
	fptrTracesToString toString;
	fptrDelete delete;
} TraceSequence;

TraceSequence *new_TraceSequence(void);
void delete_TraceSequence(void *const this);
void TraceSequence_append(TraceSequence *const this, TraceSequence *seq);
TraceSequence *TraceSequence_populate(TraceSequence *const this, list_t addTraces);
char *TraceSequence_toString(TraceSequence *const this);

/*class TraceSequence
{

public:
	TraceSequence();
	~TraceSequence();

	TraceSequence* populate(list<ModelTrace*> *addtraces);
	void append(TraceSequence *seq);
	TraceSequence* populateFromString(string addtracesTxt);
	TraceSequence* populateFromStream(istream &inputStream );
	string exportToString();
	string toString ();
	void reverse();

	list<ModelTrace*> traces;
	KMFFactory *factory;
};*/


#endif
