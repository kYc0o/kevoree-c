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
	
	/*pDepUnitObj->requiredLibs = hashmap_new();*/
	pDepUnitObj->groupName = NULL;
	pDepUnitObj->version = NULL;
	pDepUnitObj->url = NULL;
	pDepUnitObj->hashcode = NULL;
	pDepUnitObj->type = NULL;
	pDepUnitObj->requiredLibs = NULL;
	
	pDepUnitObj->AddRequiredLibs = DeployUnit_AddRequiredLibs;
	pDepUnitObj->RemoveRequiredLibs = DeployUnit_RemoveRequiredLibs;
	pDepUnitObj->FindRequiredLibsByID = DeployUnit_FindRequiredLibsByID;
	
	pObj->MetaClassName = DeployUnit_MetaClassName;
	pObj->InternalGetKey = DeployUnit_InternalGetKey;
	pObj->VisitAttributes = DeployUnit_VisitAttributes;
	pObj->VisitReferences = DeployUnit_VisitReferences;
	
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
	
	/*pDepUnitObj->requiredLibs = hashmap_new();*/
	pDepUnitObj->groupName = NULL;
	pDepUnitObj->version = NULL;
	pDepUnitObj->url = NULL;
	pDepUnitObj->hashcode = NULL;
	pDepUnitObj->type = NULL;
	pDepUnitObj->requiredLibs = NULL;
	
	pDepUnitObj->AddRequiredLibs = DeployUnit_AddRequiredLibs;
	pDepUnitObj->RemoveRequiredLibs = DeployUnit_RemoveRequiredLibs;
	pDepUnitObj->FindRequiredLibsByID = DeployUnit_FindRequiredLibsByID;
	
	pDepUnitObj->MetaClassName = DeployUnit_MetaClassName;
	pDepUnitObj->InternalGetKey = DeployUnit_InternalGetKey;
	pDepUnitObj->VisitAttributes = DeployUnit_VisitAttributes;
	pDepUnitObj->VisitReferences = DeployUnit_VisitReferences;
	
	pDepUnitObj->Delete = delete_DeployUnit;

	return pDepUnitObj;
}

char* DeployUnit_InternalGetKey(DeployUnit* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->groupName) + strlen("_") + /*strlen(this->hashcode) + strlen("_") +*/ strlen(this->super->name) + strlen("_") + strlen(this->version)) + 1);

	if (internalKey == NULL)
		return NULL;

	sprintf(internalKey, "%s_%s_%s", this->groupName, /*this->hashcode,*/ this->super->name, this->version);
	/*strcpy(internalKey, this->groupName);
	strcat(internalKey, "_");
	strcat(internalKey, this->hashcode);
	strcat(internalKey, "/");
	strcat(internalKey, this->super->name);
	strcat(internalKey, "_");
	strcat(internalKey, this->version);*/

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

void DeployUnit_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path, "%s/%s", parent, ((DeployUnit*)(this))->super->name);*/

	/*sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((DeployUnit*)(this))->super->name);*/
	NamedElement_VisitAttributes(((DeployUnit*)(this))->super, parent, visitor);
	
	sprintf(path,"%s\\groupName",parent);
	visitor->action(path, STRING, ((DeployUnit*)(this))->groupName);
	
	sprintf(path, "%s\\version", parent);
	visitor->action(path, STRING, ((DeployUnit*)(this))->version);
	
	sprintf(path,"%s\\url",parent);
	visitor->action(path, STRING, ((DeployUnit*)(this))->url);
	
	/*sprintf(path, "%s\\hashcode", parent);
	visitor->action(path, STRING, ((DeployUnit*)(this))->hashcode);*/
	
	sprintf(path, "%s\\type", parent);
	visitor->action(path, STRING, ((DeployUnit*)(this))->type);
}

void DeployUnit_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	if(((DeployUnit*)(this))->requiredLibs != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/requiredLibs[%s]", parent, ((DeployUnit*)(this))->super->name);*/
		
		/* requiredLibs */
		hashmap_map* m = ((DeployUnit*)(this))->requiredLibs;

		/* compare requiredLibs */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				DeployUnit* n = data;
				sprintf(path,"%s/requiredLibs[%s]", parent, /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
}

/*int _acceptDeployUnit(DeployUnit* this, DeployUnit* c, Visitor* visitor)
{
	visitor->action((void*)this->groupName, (void*)c->groupName, 0);
	visitor->action((void*)this->version, (void*)c->version, 0);
	visitor->action((void*)this->url, (void*)c->url, 0);
	visitor->action((void*)this->hashcode, (void*)c->hashcode, 0);
	visitor->action((void*)this->type, (void*)c->type, 0);
}*/