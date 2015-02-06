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
	
	pObj->InternalGetKey = PortTypeMapping_InternalGetKey;
	pObj->MetaClassName = PortTypeMapping_MetaClassName;
	pObj->Delete = delete_PortTypeMapping;
	pObj->VisitAttributes = PortTypeMapping_VisitAttributes;
	pObj->VisitPathAttributes = PortTypeMapping_VisitPathAttributes;
	pObj->FindByPath = PortTypeMapping_FindByPath;
	
	return pObj;
}

char* PortTypeMapping_MetaClassName(PortTypeMapping* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("PortTypeMapping")) + 1);
	if(name != NULL)
		strcpy(name, "PortTypeMapping");
	else
		return NULL;
	
	return name;
}

char* PortTypeMapping_InternalGetKey(PortTypeMapping* const this)
{
	return this->generated_KMF_ID;
}

void delete_PortTypeMapping(PortTypeMapping* const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		free(this->beanMethodName);
		free(this->serviceMethodName);
		free(this->paramTypes);
		free(this->generated_KMF_ID);
		free(this->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

void PortTypeMapping_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	char* cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	cClass = ((PortTypeMapping*)this)->MetaClassName((PortTypeMapping*)this);
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

void PortTypeMapping_VisitPathAttributes(void *const this, char *parent, Visitor *visitor)
{
	char path[256];
	char* cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	cClass = ((PortTypeMapping*)this)->MetaClassName((PortTypeMapping*)this);
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

void* PortTypeMapping_FindByPath(char* attribute, PortTypeMapping* const this)
{
	/* Local attributes */
	if(!strcmp("beanMethodName", attribute))
	{
		return this->beanMethodName;
	}
	else if(!strcmp("serviceMethodName", attribute))
	{
		return this->serviceMethodName;
	}
	else if(!strcmp("paramTypes", attribute))
	{
		return this->paramTypes;
	}
	else if(!strcmp("generated_KMF_ID", attribute))
	{
		return this->generated_KMF_ID;
	}
	/* There is no local references */
	else
	{
		PRINTF("Wrong path\n");
		return NULL;
	}
}
