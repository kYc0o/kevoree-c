#include "Instance.h"

NamedElement* newPoly_Instance()
{
	Instance* pInstanceObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pInstanceObj = (Instance*)malloc(sizeof(Instance));

	if (pInstanceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pInstanceObj; /* Pointing to derived object */
	
	pInstanceObj->metaData = NULL;
	pInstanceObj->started = -1;
	
	pInstanceObj->AddTypeDefinition = Instance_AddTypeDefinition;
	pObj->MetaClassName = Instance_MetaClassName;
	pObj->InternalGetKey = Instance_InternalGetKey;
	pObj->Delete = deletePoly_Instance;
	pObj->VisitAttributes = Instance_VisitAttributes;
	pObj->VisitReferences = Instance_VisitReferences;

	return pObj;
}

Instance* new_Instance()
{
	Instance* pInstanceObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pInstanceObj = (Instance*)malloc(sizeof(Instance));

	if (pInstanceObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pInstanceObj; Pointing to derived object */
	pInstanceObj->super = pObj;
	
	pInstanceObj->metaData = NULL;
	pInstanceObj->started = -1;
	
	pInstanceObj->AddTypeDefinition = Instance_AddTypeDefinition;
	pInstanceObj->MetaClassName = Instance_MetaClassName;
	pInstanceObj->InternalGetKey = Instance_InternalGetKey;
	pInstanceObj->Delete = delete_Instance;
	pInstanceObj->VisitAttributes = Instance_VisitAttributes;
	pInstanceObj->VisitReferences = Instance_VisitReferences;

	return pInstanceObj;
}

void Instance_AddTypeDefinition(Instance* this, TypeDefinition* ptr)
{
	this->typeDefinition = ptr;
}

char* Instance_InternalGetKey(Instance* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->name)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->name);

	return internalKey;
}

char* Instance_MetaClassName(Instance* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("Instance") + 1));
	strcpy(name, "Instance");
	
	return name;
}

void deletePoly_Instance(NamedElement* const this)
{
	Instance* pInstanceObj;
	pInstanceObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pInstanceObj->metaData);
	free(pInstanceObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_Instance(Instance* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	free(this->metaData);
	free(this);
	
}

void Instance_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path, "%s/%s", parent, ((Instance*)(this))->super->name);*/

	/*sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((Instance*)(this))->super->name);*/
	/*sprintf(path, "%s", parent);*/
	NamedElement_VisitAttributes(((Instance*)(this))->super, parent, visitor);
	
	sprintf(path,"%s\\metaData", parent);
	visitor->action(path, STRING, ((Instance*)(this))->metaData);
	
	sprintf(path,"%s\\started", parent);
	visitor->action(path, BOOL, (void*)((Instance*)(this))->started);
}

void Instance_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((Instance*)(this))->typeDefinition != NULL)
	{
		sprintf(path, "%s/typeDefinition[%s]", parent, /*((Instance*)(this))->typeDefinition->super->name*/((Instance*)(this))->typeDefinition->InternalGetKey(((Instance*)(this))->typeDefinition));
		((Instance*)(this))->typeDefinition->VisitAttributes(((Instance*)(this))->typeDefinition, path, visitor);
		((Instance*)(this))->typeDefinition->VisitReferences(((Instance*)(this))->typeDefinition, path, visitor);
	}
}

void* Instance_FindByPath(char* attribute, Instance* const this)
{
	/* NamedElement attributes */
	if(!strcmp("name",attribute))
	{
		return this->super->FindByPath(attribute, this->super);
	}
	/* Local attributes */
	else if(!strcmp("metaData",attribute))
	{
		return this->metaData;
	}
	else if(!strcmp("started",attribute))
	{
		return this->started;
	}
	/* Local references */
	else
	{
		char* nextAttribute = NULL;
		char* path = strdup(attribute);
		char* pch;

		if(indexOf(path,"/") != -1)
		{
			pch = strtok (path,"/");
			/*nextAttribute = strtok(NULL, "\\");
			sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));*/
			/*printf("pch: %s\n", pch);*/
			if(strchr(attribute,'\\') != NULL)
			{
				/*printf("Attribute found at: %d\n", strchr(attribute,'\\')-attribute+1);*/
				nextAttribute = strtok(NULL, "\\");
				sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));
			}
			else
			{
				/*printf("Attribute not found, looking for path\n");*/
				nextAttribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			nextAttribute = strtok(pch, "\\");
			nextAttribute = strtok(NULL, "\\");
		}
		
		/*printf("Token: %s\n", pch);*/

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
		
		/*printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("next attribute: %s\n", nextAttribute);*/
		
		if(!strcmp("typeDefinition", relationName))
		{
			/*printf("relationName: %s\n", relationName);*/
			if(nextAttribute == NULL)
			{
				return this->typeDefinition;
			}
			else
			{
				return this->typeDefinition->FindByPath(nextAttribute, this->typeDefinition);
			}
		}
		else
		{
			/*printf("relationName: %s\n", relationName);*/
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}

/*int _acceptInstance(Instance* this, Instance* c, Visitor* visitor)
{
	visitor->action((void*)this->metaData, (void*)c->metaData, 0);
	visitor->action((void*)this->started, (void*)c->started, 1);
	visitor->action((void*)this->typeDefinition, (void*)c->typeDefinition, 0);
}*/