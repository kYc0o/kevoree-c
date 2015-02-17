#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Port.h"
#include "Visitor.h"
#include "tools.h"
#include "PortTypeMapping.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

PortTypeMapping* new_PortTypeMapping()
{
	PortTypeMapping* pObj;
	/* Allocating memory */
	pObj = (PortTypeMapping*)malloc(sizeof(PortTypeMapping));

	if (pObj == NULL)
	{
		return NULL;
	}

	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;

	memset(&pObj->generated_KMF_ID[0], 0, sizeof(pObj->generated_KMF_ID));
	rand_str(pObj->generated_KMF_ID, 8);
	
	pObj->beanMethodName = NULL;
	pObj->serviceMethodName = NULL;
	pObj->paramTypes = NULL;
	pObj->eContainer = NULL;
	
	pObj->internalGetKey = PortTypeMapping_internalGetKey;
	pObj->metaClassName = PortTypeMapping_metaClassName;
	pObj->Delete = delete_PortTypeMapping;
	pObj->VisitAttributes = PortTypeMapping_VisitAttributes;
	pObj->VisitPathAttributes = PortTypeMapping_VisitPathAttributes;
	pObj->FindByPath = PortTypeMapping_FindByPath;
	
	return pObj;
}

char* PortTypeMapping_metaClassName(void * const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("PortTypeMapping")) + 1);
	if(name != NULL)
		strcpy(name, "PortTypeMapping");
	else
		return NULL;
	
	return name;
}

char* PortTypeMapping_internalGetKey(void * const this)
{
	PortTypeMapping *pObj = (PortTypeMapping*)this;
	return pObj->generated_KMF_ID;
}

void delete_PortTypeMapping(void * const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		PortTypeMapping *pObj = (PortTypeMapping*)this;
		free(pObj->beanMethodName);
		free(pObj->serviceMethodName);
		free(pObj->paramTypes);
		free(pObj->eContainer);
		free(pObj);
		/*this = NULL;*/
	}
}

void PortTypeMapping_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	char* cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	cClass = ((PortTypeMapping*)this)->metaClassName((PortTypeMapping*)this);
	visitor->action(path, STRING, cClass);
	/*free(cClass);*/
	free(cClass);

	sprintf(path,"%s\\ID",parent);
	visitor->action(path, STRING, ((PortTypeMapping*)(this))->generated_KMF_ID);
	
	sprintf(path,"%s\\beanMethodName",parent);
	visitor->action(path, STRING, ((PortTypeMapping*)(this))->beanMethodName);
	
	sprintf(path,"%s\\serviceMethodName",parent);
	visitor->action(path, STRING, ((PortTypeMapping*)(this))->serviceMethodName);
	
	sprintf(path,"%s\\paramTypes",parent);
	visitor->action(path, STRING, ((PortTypeMapping*)(this))->paramTypes);
}

void PortTypeMapping_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char* cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	cClass = ((PortTypeMapping*)this)->metaClassName((PortTypeMapping*)this);
	visitor->action(path, STRING, cClass);
	free(cClass);*/

	sprintf(path,"%s\\ID",parent);
	visitor->action(path, STRING, ((PortTypeMapping*)(this))->generated_KMF_ID);

	sprintf(path,"%s\\beanMethodName",parent);
	visitor->action(path, STRING, ((PortTypeMapping*)(this))->beanMethodName);

	sprintf(path,"%s\\serviceMethodName",parent);
	visitor->action(path, STRING, ((PortTypeMapping*)(this))->serviceMethodName);

	sprintf(path,"%s\\paramTypes",parent);
	visitor->action(path, STRING, ((PortTypeMapping*)(this))->paramTypes);
}

void* PortTypeMapping_FindByPath(char* attribute, void * const this)
{
	PortTypeMapping *pObj = (PortTypeMapping*)this;
	/* Local attributes */
	if(!strcmp("beanMethodName", attribute))
	{
		return pObj->beanMethodName;
	}
	else if(!strcmp("serviceMethodName", attribute))
	{
		return pObj->serviceMethodName;
	}
	else if(!strcmp("paramTypes", attribute))
	{
		return pObj->paramTypes;
	}
	else if(!strcmp("generated_KMF_ID", attribute))
	{
		return pObj->generated_KMF_ID;
	}
	/* There is no local references */
	else
	{
		PRINTF("Wrong path\n");
		return NULL;
	}
}
