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
	
	pInstanceObj->AddTypeDefinition = Instance_AddTypeDefinition;
	pObj->MetaClassName = Instance_MetaClassName;
	pObj->InternalGetKey = Instance_InternalGetKey;
	pObj->Delete = deletePoly_Instance;

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
	
	pInstanceObj->AddTypeDefinition = Instance_AddTypeDefinition;
	pInstanceObj->MetaClassName = Instance_MetaClassName;
	pInstanceObj->InternalGetKey = Instance_InternalGetKey;
	pInstanceObj->Delete = delete_Instance;

	return pInstanceObj;
}

void Instance_AddTypeDefinition(Instance* this, TypeDefinition* ptr)
{
	this->TypeDefinition = ptr;
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

/*int _acceptInstance(Instance* this, Instance* c, Visitor* visitor)
{
	visitor->action((void*)this->metaData, (void*)c->metaData, 0);
	visitor->action((void*)this->started, (void*)c->started, 1);
	visitor->action((void*)this->typeDefinition, (void*)c->typeDefinition, 0);
}*/