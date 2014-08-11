#include "PortTypeMapping.h"

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

	/*pObj->generated_KMF_ID = malloc(sizeof(char) * (strlen("dummyKMFID_PortTypeMapping") + 1));Uuid::getSingleton().generateUUID();
	strcpy(pObj->generated_KMF_ID, "dummyKMFID_PortTypeMapping");*/
	pObj->generated_KMF_ID = malloc(sizeof(char) * 8 + 1);
	rand_str(pObj->generated_KMF_ID, 8);
	
	pObj->beanMethodName = NULL;
	pObj->serviceMethodName = NULL;
	pObj->paramTypes = NULL;
	
	pObj->InternalGetKey = PortTypeMapping_InternalGetKey;
	pObj->MetaClassName = PortTypeMapping_MetaClassName;
	pObj->Delete = delete_PortTypeMapping;
	pObj->VisitAttributes = PortTypeMapping_VisitAttributes;
	/*pObj->VisitReferences = PortTypeMapping_VisitAttributes;*/
	pObj->FindByPath = PortTypeMapping_FindByPath;
	
	return pObj;
}

char* PortTypeMapping_MetaClassName(PortTypeMapping* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("PortTypeMapping") + 1));
	strcpy(name, "PortTypeMapping");
	
	return name;
}

char* PortTypeMapping_InternalGetKey(PortTypeMapping* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->generated_KMF_ID)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->generated_KMF_ID);

	return internalKey;
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
		free(this);
	}
}

void PortTypeMapping_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path, "%s/%s", parent, ((PortTypeMapping*)(this))->generated_KMF_ID);*/

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
		printf("Wrong path\n");
		return NULL;
	}
}