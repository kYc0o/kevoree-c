#include "NetworkInfo.h"

NamedElement* newPoly_NetworkInfo()
{
	NetworkInfo* pNetInfoObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pNetInfoObj = (NetworkInfo*)malloc(sizeof(NetworkInfo));

	if (pNetInfoObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pNetInfoObj; /* Pointing to derived object */
	
	/*pNetInfoObj->values = hashmap_new();*/
	pNetInfoObj->values = NULL;
	
	pNetInfoObj->AddValues = NetworkInfo_AddValues;
	pNetInfoObj->RemoveValues = NetworkInfo_RemoveValues;
	pNetInfoObj->FindValuesByID = NetworkInfo_FindValuesByID;
	
	pObj->MetaClassName = NetworkInfo_MetaClassName;
	pObj->InternalGetKey = NetworkInfo_InternalGetKey;
	
	pObj->Delete = deletePoly_NetworkInfo;

	return pObj;
}

NetworkInfo* new_NetworkInfo()
{
	NetworkInfo* pNetInfoObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pNetInfoObj = (NetworkInfo*)malloc(sizeof(NetworkInfo));

	if (pNetInfoObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pNetInfoObj;  Pointing to derived object */
	pNetInfoObj->super = pObj;
	
	/*pNetInfoObj->values = hashmap_new();*/
	pNetInfoObj->values = NULL;
	
	pNetInfoObj->AddValues = NetworkInfo_AddValues;
	pNetInfoObj->RemoveValues = NetworkInfo_RemoveValues;
	pNetInfoObj->FindValuesByID = NetworkInfo_FindValuesByID;
	
	pNetInfoObj->MetaClassName = NetworkInfo_MetaClassName;
	pNetInfoObj->InternalGetKey = NetworkInfo_InternalGetKey;
	
	pNetInfoObj->Delete = delete_NetworkInfo;

	return pNetInfoObj;
}

char* NetworkInfo_InternalGetKey(NetworkInfo* const this)
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

char* NetworkInfo_MetaClassName(NetworkInfo* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("NetworkInfo") + 1));
	strcpy(name, "NetworkInfo");
	
	return name;
}

void NetworkInfo_AddValues(NetworkInfo* const this, NetworkProperty* ptr)
{
	NetworkProperty* container = (NetworkProperty*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be added in NetworkInfo because the key is not defined");*/
		printf("The NetworkProperty cannot be added in NetworkInfo because the key is not defined\n");
	}else
	{
		/*if(values.find(container->internalGetKey()) == values.end())*/
		if(this->values == NULL)
		{
			this->values = hashmap_new();
		}
		if(hashmap_get(this->values, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*values[container->internalGetKey()]=ptr;*/
			container = (NetworkProperty*)ptr;
			hashmap_put(this->values, container->InternalGetKey(container), ptr);
			/*any ptr_any = container;
			RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"values",ptr_any);
			container->setEContainer(this,cmd,"values");*/
		}
	}
}

void NetworkInfo_RemoveValues(NetworkInfo* const this, NetworkProperty* ptr)
{
	NetworkProperty* container = (NetworkProperty*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be removed in NetworkInfo because the key is not defined");*/
		printf("The NetworkProperty cannot be removed in NetworkInfo because the key is not defined\n");
	}
	else
	{
		/*values.erase( values.find(container->internalGetKey()));*/
		hashmap_remove(this->values, container->InternalGetKey(container));
		/*delete container;
		container->setEContainer(NULL,NULL,"");*/
	}
}

NetworkInfo* NetworkInfo_FindValuesByID(NetworkInfo* const this, char* id)
{
	NetworkInfo* value;

	if(hashmap_get(this->values, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void deletePoly_NetworkInfo(NamedElement* const this)
{
	NetworkInfo* pNetInfoObj;
	pNetInfoObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pNetInfoObj->values);
	free(pNetInfoObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_NetworkInfo(NetworkInfo* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	hashmap_free(this->values);
	free(this);
	
}

/*int _acceptNetworkInfo(NetworkInfo* this, NetworkInfo* c, Visitor* visitor)
{
	int i;

	for(i = 0; i < this->count_values; i++)
	{
		visitor->action((void*)this->values, (void*)c->values, 0);
	}
}*/