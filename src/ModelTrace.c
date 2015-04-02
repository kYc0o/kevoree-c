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

ModelTrace* new_ModelTrace()
{
	ModelTrace* pObj = NULL;
	/* Allocating memory */
	pObj = (ModelTrace*)malloc(sizeof(ModelTrace));

	if (pObj == NULL)
	{
		return NULL;
	}

	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;
	
	pObj->srcPath = NULL;
	pObj->refName = NULL;
	
	pObj->ToString = ModelTrace_ToString;
	pObj->Delete = delete_ModelTrace;

	return pObj;
}

void delete_ModelTrace(void* const this)
{
	if(this != NULL)
	{
		free(((ModelTrace*)this)->srcPath);
		free(((ModelTrace*)this)->refName);
		free(this);
	}
}

char* ModelTrace_ToString(void* const this)
{
	return NULL;
}

ModelTrace* newPoly_ModelSetTrace(char* _srcPath, char* _refName, /*char* _objPath,*/ char* _content/*, char* _typeName*/)
{
	ModelSetTrace* pModSetTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModSetTraceObj = (ModelSetTrace*)malloc(sizeof(ModelSetTrace));

	if (pModSetTraceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pModSetTraceObj; /* Pointing to derived object */
	pModSetTraceObj->super = pObj;
	
	pObj->srcPath = malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModSetTraceObj->content = malloc(sizeof(char)*(strlen(_content)+1));
	strcpy(pModSetTraceObj->content, _content);
	
	pModSetTraceObj->Delete = delete_ModelSetTrace;
	pModSetTraceObj->ToString = ModelSetTrace_ToString;
	pObj->ToString = ModelSetTrace_ToString;

	return pObj;
}

ModelSetTrace* new_ModelSetTrace(char* _srcPath, char* _refName, /*char* _objPath,*/ char* _content/*, char* _typeName*/)
{
	ModelSetTrace* pModSetTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModSetTraceObj = (ModelSetTrace*)malloc(sizeof(ModelSetTrace));

	if (pModSetTraceObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pInstanceObj; Pointing to derived object */
	pModSetTraceObj->super = pObj;
	
	pObj->srcPath = malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModSetTraceObj->content = malloc(sizeof(char)*(strlen(_content)+1));
	strcpy(pModSetTraceObj->content, _content);
	
	pModSetTraceObj->Delete = delete_ModelSetTrace;
	pModSetTraceObj->ToString = ModelSetTrace_ToString;
	pObj->ToString = ModelSetTrace_ToString;

	return pModSetTraceObj;
}

void deletePoly_ModelSetTrace(void* const this)
{
	ModelSetTrace* pModSetTraceObj;
	pModSetTraceObj = ((ModelTrace*)this)->pDerivedObj;
	/*destroy derived obj*/
	free(pModSetTraceObj->content);
	free(pModSetTraceObj);
	/*destroy base Obj*/
	delete_ModelTrace(this);
}

void delete_ModelSetTrace(void* const this)
{
	/* destroy base object */
	delete_ModelTrace(((ModelSetTrace*)this)->super);
	/* destroy data memebers */
	free(((ModelSetTrace*)this)->content);
	free(this);
}

char *ModelSetTrace_ToString(void* const this)
{
	char *traceBuf = NULL;

	traceBuf = malloc(TRACE_BUF_SIZE);

	sprintf(traceBuf, "{ \"traceType\" : \"%s\", \"src\" : \"%s\", \"refname\" : \"%s\"",
			ActionType(SET),
			((ModelSetTrace*)this)->super->srcPath,
			((ModelSetTrace*)this)->super->refName);
	
	if(((ModelSetTrace*)this)->content != NULL)
	{
		sprintf(traceBuf, "%s, \"content\" : \"%s\"", traceBuf, ((ModelSetTrace*)this)->content);
	}
	
	sprintf(traceBuf, "%s }\n", traceBuf);

	return traceBuf;
}  

ModelTrace* newPoly_ModelAddTrace(char* _srcPath, char* _refName, char* _previousPath, char* _typeName)
{
	ModelAddTrace* pModAddTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModAddTraceObj = (ModelAddTrace*)malloc(sizeof(ModelAddTrace));

	if (pModAddTraceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pModAddTraceObj; /* Pointing to derived object */
	pModAddTraceObj->super = pObj;
	
	pObj->srcPath = malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModAddTraceObj->previousPath = malloc(sizeof(char)*(strlen(_previousPath)+1));
	strcpy(pModAddTraceObj->previousPath, _previousPath);
	if (_typeName != NULL) {
		pModAddTraceObj->typeName = malloc(sizeof(char)*(strlen(_typeName)+1));
		strcpy(pModAddTraceObj->typeName, _typeName);
	} else {
		pModAddTraceObj->typeName = NULL;
	}
	
	pModAddTraceObj->Delete = delete_ModelAddTrace;
	pModAddTraceObj->ToString = ModelAddTrace_ToString;
	pObj->ToString = ModelAddTrace_ToString;

	return pObj;
}

ModelAddTrace* new_ModelAddTrace(char* _srcPath, char* _refName, char* _previousPath, char* _typeName)
{
	ModelAddTrace* pModAddTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModAddTraceObj = (ModelAddTrace*)malloc(sizeof(ModelAddTrace));

	if (pModAddTraceObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pInstanceObj; Pointing to derived object */
	pModAddTraceObj->super = pObj;
	
	pObj->srcPath = malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModAddTraceObj->previousPath = malloc(sizeof(char)*(strlen(_previousPath)+1));
	strcpy(pModAddTraceObj->previousPath, _previousPath);
	pModAddTraceObj->typeName = malloc(sizeof(char)*(strlen(_typeName)+1));
	strcpy(pModAddTraceObj->typeName, _typeName);
	
	pModAddTraceObj->Delete = delete_ModelAddTrace;
	pModAddTraceObj->ToString = ModelAddTrace_ToString;
	pObj->ToString = ModelAddTrace_ToString;

	return pModAddTraceObj;
}

void deletePoly_ModelAddTrace(void* const this)
{
	ModelAddTrace* pModAddTraceObj;
	pModAddTraceObj = ((ModelTrace*)this)->pDerivedObj;
	/*destroy derived obj*/
	free(pModAddTraceObj->previousPath);
	free(pModAddTraceObj->typeName);
	/*destroy base Obj*/
	delete_ModelTrace(this);
}

void delete_ModelAddTrace(void* const this)
{
	/* destroy base object */
	delete_ModelTrace(((ModelAddTrace*)this)->super);
	/* destroy data memebers */
	free(((ModelAddTrace*)this)->previousPath);
	free(((ModelAddTrace*)this)->typeName);
	free(this);
}

char *ModelAddTrace_ToString(void* const this)
{
	/*string buffer = "";*/
	char *traceBuf = NULL;

	traceBuf = malloc(TRACE_BUF_SIZE);

	sprintf(traceBuf, "{ \"traceType\" : \"%s\", \"src\" : \"%s\", \"refname\" : \"%s\"",
			ActionType(ADD),
			((ModelAddTrace*)this)->super->srcPath,
			((ModelAddTrace*)this)->super->refName);
	
	if(((ModelAddTrace*)this)->previousPath != NULL)
	{
		sprintf(traceBuf, "%s, \"previouspath\" : \"%s\"", traceBuf, ((ModelAddTrace*)this)->previousPath);
	}

	if(((ModelAddTrace*)this)->typeName != NULL)
	{
		sprintf(traceBuf, "%s, \"typename\" : \"%s\"", traceBuf, ((ModelAddTrace*)this)->typeName);
	}

	sprintf(traceBuf, "%s }\n", traceBuf);
	return traceBuf;
}

ModelTrace *newPoly_ModelRemoveTrace(char* _srcPath, char* _refName, char* _objPath)
{
	ModelRemoveTrace* pModRemTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	/* Allocating memory */
	pModRemTraceObj = (ModelRemoveTrace*)malloc(sizeof(ModelRemoveTrace));

	if (pModRemTraceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pModRemTraceObj; /* Pointing to derived object */
	pModRemTraceObj->super = pObj;
	
	pObj->srcPath = malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModRemTraceObj->objPath = malloc(sizeof(char)*(strlen(_objPath)+1));
	strcpy(pModRemTraceObj->objPath, _objPath);
	
	pModRemTraceObj->Delete = delete_ModelRemoveTrace;
	pModRemTraceObj->ToString = ModelRemoveTrace_ToString;
	pObj->ToString = ModelRemoveTrace_ToString;

	return pObj;
}

void deletePoly_ModelRemoveTrace(void* const this)
{
	ModelSetTrace* pModSetTraceObj;
	pModSetTraceObj = ((ModelTrace*)this)->pDerivedObj;
	/*destroy derived obj*/
	free(pModSetTraceObj->content);
	/*destroy base Obj*/
	delete_ModelTrace(this);
}

void delete_ModelRemoveTrace(void* const this)
{
	/* destroy base object */
	delete_ModelTrace(((ModelRemoveTrace*)this)->super);
	/* destroy data memebers */
	free(((ModelRemoveTrace*)this)->objPath);
	free(this);
}

ModelRemoveTrace *new_ModelRemoveTrace(char* _srcPath, char* _refName, char* _objPath)
{
	ModelRemoveTrace* pModRemTraceObj = NULL;
	ModelTrace* pObj = new_ModelTrace();

	pModRemTraceObj = (ModelRemoveTrace*)malloc(sizeof(ModelRemoveTrace));

	if (pModRemTraceObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pInstanceObj; Pointing to derived object */
	pModRemTraceObj->super = pObj;

	pObj->srcPath = malloc(sizeof(char)*(strlen(_srcPath)+1));
	strcpy(pObj->srcPath, _srcPath);
	pObj->refName = malloc(sizeof(char)*(strlen(_refName)+1));
	strcpy(pObj->refName, _refName);
	pModRemTraceObj->objPath = malloc(sizeof(char)*(strlen(_objPath)+1));
	strcpy(pModRemTraceObj->objPath, _objPath);

	pModRemTraceObj->Delete = delete_ModelRemoveTrace;
	pModRemTraceObj->ToString = ModelRemoveTrace_ToString;
	pObj->ToString = ModelRemoveTrace_ToString;

	return pModRemTraceObj;
}

char *ModelRemoveTrace_ToString(void* const this)
{
	char *traceBuf = NULL;

	traceBuf = malloc(TRACE_BUF_SIZE);

	sprintf(traceBuf, "{ \"traceType\" : \"%s\" , \"src\" : \"%s\", \"refname\" : \"%s\", \"objpath\" : \"%s\" }\n",
			ActionType(REMOVE),
			((ModelRemoveTrace*)this)->super->srcPath,
			((ModelRemoveTrace*)this)->super->refName,
			((ModelRemoveTrace*)this)->objPath);

	return traceBuf;
}
