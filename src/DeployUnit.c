#include "DeployUnit.h"

NamedElement* newPoly_DeployUnit()
{
	DeployUnit* pDepUnitObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pDepUnitObj = (DeployUnit*)malloc(sizeof(DeployUnit));

	if (pDepUnitObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pDepUnitObj; /* Pointing to derived object */
	pObj->MetaClassName = DeployUnit_MetaClassName;
	pObj->InternalGetKey = DeployUnit_InternalGetKey;
	
	/*pDepUnitObj->requiredLibs = hashmap_new();*/
	pDepUnitObj->requiredLibs = NULL;
	
	pDepUnitObj->AddRequiredLibs = DeployUnit_AddRequiredLibs;
	pDepUnitObj->RemoveRequiredLibs = DeployUnit_RemoveRequiredLibs;
	pDepUnitObj->FindRequiredLibsByID = DeployUnit_FindRequiredLibsByID;
	
	pObj->Delete = deletePoly_DeployUnit;

	return pObj;
}

DeployUnit* new_DeployUnit()
{
	DeployUnit* pDepUnitObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;
	
	/* Allocating memory */
	pDepUnitObj = (DeployUnit*)malloc(sizeof(DeployUnit));

	if (pDepUnitObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pDepUnitObj;  Pointing to derived object */
	pDepUnitObj->super = pObj; /* Pointing to the base object */
	
	pDepUnitObj->MetaClassName = DeployUnit_MetaClassName;
	pDepUnitObj->InternalGetKey = DeployUnit_InternalGetKey;
	
	/*pDepUnitObj->requiredLibs = hashmap_new();*/
	pDepUnitObj->requiredLibs = NULL;
	
	pDepUnitObj->AddRequiredLibs = DeployUnit_AddRequiredLibs;
	pDepUnitObj->RemoveRequiredLibs = DeployUnit_RemoveRequiredLibs;
	pDepUnitObj->FindRequiredLibsByID = DeployUnit_FindRequiredLibsByID;
	
	pDepUnitObj->Delete = delete_DeployUnit;

	return pDepUnitObj;
}

char* DeployUnit_InternalGetKey(DeployUnit* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->groupName) + strlen("/") /*+ strlen(this->hashcode)*/ + strlen("/") + strlen(this->super->name) + strlen("/") + strlen(this->version)) + 1);

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->groupName);
	strcat(internalKey, "/");
	/*strcat(internalKey, this->hashcode);
	strcat(internalKey, "/");*/
	strcat(internalKey, this->super->name);
	strcat(internalKey, "/");
	strcat(internalKey, this->version);
	

	/*printf("%s\n", internalKey);*/
	return internalKey;
}

char* DeployUnit_MetaClassName(DeployUnit* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("DeployUnit") + 1));
	strcpy(name, "DeployUnit");
	
	return name;
}

/*void DeployUnit::addrequiredLibs(DeployUnit *ptr)*/
void DeployUnit_AddRequiredLibs(DeployUnit* const this, DeployUnit* ptr)
{
	DeployUnit* container = (DeployUnit*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The DeployUnit cannot be added in DeployUnit because the key is not defined");*/
		printf("The DeployUnit cannot be added in DeployUnit because the key is not defined\n");
	}
	else
	{
		/*if(requiredLibs.find(container->internalGetKey()) == requiredLibs.end())*/
		if(this->requiredLibs == NULL)
		{
			this->requiredLibs = hashmap_new();
		}
		if(hashmap_get(this->requiredLibs, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*requiredLibs[container->internalGetKey()]=ptr;*/
			container = (DeployUnit*)ptr;
			hashmap_put(this->requiredLibs, container->InternalGetKey(container), ptr);
		}
	}
}

/*void DeployUnit::removerequiredLibs(DeployUnit *ptr)*/
void DeployUnit_RemoveRequiredLibs(DeployUnit* const this, DeployUnit *ptr)
{
	DeployUnit* container = (DeployUnit*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The DeployUnit cannot be removed in DeployUnit because the key is not defined");*/
		printf("The DeployUnit cannot be removed in DeployUnit because the key is not defined\n");
	}
	else
	{
		/*requiredLibs.erase( requiredLibs.find(container->internalGetKey()));*/
		hashmap_remove(this->requiredLibs, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

DeployUnit* DeployUnit_FindRequiredLibsByID(DeployUnit* const this, char* id)
{
	DeployUnit* value;

	if(hashmap_get(this->requiredLibs, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void deletePoly_DeployUnit(NamedElement* const this)
{
	DeployUnit* pDepUnitObj;
	pDepUnitObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pDepUnitObj->groupName);
	free(pDepUnitObj->version);
	free(pDepUnitObj->url);
	free(pDepUnitObj->hashcode);
	free(pDepUnitObj->type);
	hashmap_free(pDepUnitObj->requiredLibs);
	free(pDepUnitObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_DeployUnit(DeployUnit* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	free(this->groupName);
	free(this->version);
	free(this->url);
	free(this->hashcode);
	free(this->type);
	hashmap_free(this->requiredLibs);
	free(this);
}

/*int _acceptDeployUnit(DeployUnit* this, DeployUnit* c, Visitor* visitor)
{
	visitor->action((void*)this->groupName, (void*)c->groupName, 0);
	visitor->action((void*)this->version, (void*)c->version, 0);
	visitor->action((void*)this->url, (void*)c->url, 0);
	visitor->action((void*)this->hashcode, (void*)c->hashcode, 0);
	visitor->action((void*)this->type, (void*)c->type, 0);
}*/