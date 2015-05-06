#include <string.h>

#include "ModelTrace.h"
#include "ActionType.h"

/**
 * Author: fco.ja.ac@gmail.com
 * Date: 21/07/2014
 * Time: 17:55
 */

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#define TRACE_BUF_SIZE 400
#define PATH_OK  1
#define PATH_ERROR -1

static void
deletePoly_ModelSetTrace(void* const this)
{
	ModelSetTrace* pModSetTraceObj = ((ModelSetTrace*)this);
	/*destroy derived obj*/
	free(pModSetTraceObj->content);
	free(pModSetTraceObj->srcPath);
	free(pModSetTraceObj->refName);
	/*destroy base Obj*/
	free(pModSetTraceObj);
}

static char
*ModelSetTrace_ToString(void* const this)
{
	char *traceBuf = NULL;

	traceBuf = malloc(TRACE_BUF_SIZE);

	sprintf(traceBuf, "{ \"traceType\" : \"%s\", \"src\" : \"%s\", \"refname\" : \"%s\"",
			ActionType(SET),
			((ModelSetTrace*)this)->srcPath,
			((ModelSetTrace*)this)->refName);

	if(((ModelSetTrace*)this)->content != NULL)
	{
		sprintf(traceBuf, "%s, \"content\" : \"%s\"", traceBuf, ((ModelSetTrace*)this)->content);
	}

	sprintf(traceBuf, "%s }\n", traceBuf);
	char *r = strdup(traceBuf);
	free(traceBuf);

	return r;
}

static int
ModelSetTrace_getType()
{
	return SET;
}

static const
ModelTrace_VT modelSetTrace_VT = {
		.ToString = ModelSetTrace_ToString,
		.Delete = deletePoly_ModelSetTrace,
		.getType = ModelSetTrace_getType
};

ModelTrace* newPoly_ModelSetTrace(char* _srcPath, char* _refName, /*char* _objPath,*/ char* _content/*, char* _typeName*/)
{
	/* Allocating memory */
	ModelSetTrace* pModSetTraceObj = (ModelSetTrace*)malloc(sizeof(ModelSetTrace));

	if (pModSetTraceObj == NULL) return NULL;

	pModSetTraceObj->srcPath = strdup(_srcPath);
	pModSetTraceObj->refName = strdup(_refName);
	pModSetTraceObj->content = strdup(_content);

	// hey, use this virtual method table
	pModSetTraceObj->vt = &modelSetTrace_VT;

	return (ModelTrace*)pModSetTraceObj;
}

/**
	================================================
	Done with add trace
	================================================
 */
static void
deletePoly_ModelAddTrace(void* const this)
{
	ModelAddTrace* pModAddTraceObj = ((ModelAddTrace*)this);
	/*destroy derived obj*/
	free(pModAddTraceObj->previousPath);
	if (pModAddTraceObj->typeName)
		free(pModAddTraceObj->typeName);
	/*destroy base Obj*/
	free(pModAddTraceObj->srcPath);
	free(pModAddTraceObj->refName);
	free(this);
}

static char
*ModelAddTrace_ToString(void* const this)
{
	ModelAddTrace* pModAddTraceObj = ((ModelAddTrace*)this);
	char *traceBuf = NULL;

	traceBuf = malloc(TRACE_BUF_SIZE);

	sprintf(traceBuf, "{ \"traceType\" : \"%s\", \"src\" : \"%s\", \"refname\" : \"%s\"",
			ActionType(ADD),
			pModAddTraceObj->srcPath,
			pModAddTraceObj->refName);

	if(pModAddTraceObj->previousPath != NULL)
	{
		sprintf(traceBuf, "%s, \"previouspath\" : \"%s\"", traceBuf, ((ModelAddTrace*)this)->previousPath);
	}

	if(pModAddTraceObj->typeName != NULL)
	{
		sprintf(traceBuf, "%s, \"typename\" : \"%s\"", traceBuf, ((ModelAddTrace*)this)->typeName);
	}

	sprintf(traceBuf, "%s }\n", traceBuf);
	char *r = strdup(traceBuf);
	free(traceBuf);
	return r;
}

static int
ModelAddTrace_getType()
{
	return ADD;
}

static const
ModelTrace_VT modelAddTrace_VT = {
		.ToString = ModelAddTrace_ToString,
		.Delete = deletePoly_ModelAddTrace,
		.getType = ModelAddTrace_getType
};

ModelTrace* newPoly_ModelAddTrace(char* _srcPath, char* _refName, char* _previousPath, char* _typeName)
{
	ModelAddTrace* pModAddTraceObj = NULL;

	/* Allocating memory */
	pModAddTraceObj = (ModelAddTrace*)malloc(sizeof(ModelAddTrace));

	if (pModAddTraceObj == NULL) return NULL;

	pModAddTraceObj->srcPath = strdup(_srcPath);
	pModAddTraceObj->refName = strdup(_refName);
	pModAddTraceObj->previousPath = strdup(_previousPath);

	pModAddTraceObj->typeName = (_typeName != NULL)?strdup(_typeName):NULL;

	pModAddTraceObj->vt = &modelAddTrace_VT;

	return (ModelTrace*)pModAddTraceObj;
}

/**
	================================================
	Done with remove trace
	================================================
 */

static void
deletePoly_ModelRemoveTrace(void* const this)
{
	ModelRemoveTrace* pModRemoveTraceObj = ((ModelRemoveTrace*)this);
	/*destroy derived obj*/
	free(pModRemoveTraceObj->objPath);
	/*destroy base Obj*/
	free(pModRemoveTraceObj->srcPath);
	free(pModRemoveTraceObj->refName);
	free(this);
}

static char
*ModelRemoveTrace_ToString(void* const this)
{
	char *traceBuf = malloc(TRACE_BUF_SIZE);

	sprintf(traceBuf, "{ \"traceType\" : \"%s\" , \"src\" : \"%s\", \"refname\" : \"%s\", \"objpath\" : \"%s\" }\n",
			ActionType(REMOVE),
			((ModelRemoveTrace*)this)->srcPath,
			((ModelRemoveTrace*)this)->refName,
			((ModelRemoveTrace*)this)->objPath);

	char *r = strdup(traceBuf);
	free(traceBuf);
	return r;
}

static int
ModelRemoveTrace_getType()
{
	return REMOVE;
}

static const
ModelTrace_VT modelRemoveTrace_VT = {
		.ToString = ModelRemoveTrace_ToString,
		.Delete = deletePoly_ModelRemoveTrace,
		.getType = ModelRemoveTrace_getType
};

ModelTrace *newPoly_ModelRemoveTrace(char* _srcPath, char* _refName, char* _objPath)
{
	ModelRemoveTrace* pModRemTraceObj = NULL;

	/* Allocating memory */
	pModRemTraceObj = (ModelRemoveTrace*)malloc(sizeof(ModelRemoveTrace));

	if (pModRemTraceObj == NULL) return NULL;

	pModRemTraceObj->srcPath = strdup(_srcPath);
	pModRemTraceObj->refName = strdup(_refName);
	pModRemTraceObj->objPath = strdup(_objPath);

	pModRemTraceObj->vt = &modelRemoveTrace_VT;

	return (ModelTrace*)pModRemTraceObj;
}
