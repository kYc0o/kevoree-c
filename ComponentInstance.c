#include "ComponentInstance.h"

Instance* newPoly_ComponentInstance()
{
	ComponentInstance* pCompInstanceObj = NULL;
	Instance* pObj = new_Instance();

	/* Allocating memory */
	pCompInstanceObj = (ComponentInstance*)malloc(sizeof(ComponentInstance));

	if (pCompInstanceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pCompInstanceObj; /* Pointing to derived object */
	
	pObj->MetaClassName = ComponentInstance_MetaClassName;
	pObj->InternalGetKey = ComponentInstance_InternalGetKey;
	
	pObj->Delete = deletePoly_ComponentInstance;

	return pObj;
}

ComponentInstance* new_ComponentInstance()
{
	ComponentInstance* pCompInstanceObj = NULL;
	Instance* pObj = new_Instance();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pCompInstanceObj = (ComponentInstance*)malloc(sizeof(ComponentInstance));

	if (pCompInstanceObj == NULL)
	{
		return NULL;
	}

	/*((Instance*)(pObj->pDerivedObj))->pDerivedObj = pCompInstanceObj; Pointing to derived object */
	
	pCompInstanceObj->MetaClassName = ComponentInstance_MetaClassName;
	pCompInstanceObj->InternalGetKey = ComponentInstance_InternalGetKey;
	
	pCompInstanceObj->Delete = delete_ComponentInstance;

	return pCompInstanceObj;
}

char* ComponentInstance_InternalGetKey(ComponentInstance* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->super->name)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->super->name);

	return internalKey;
}

char* ComponentInstance_MetaClassName(ComponentInstance* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("ComponentInstance") + 1));
	strcpy(name, "ComponentInstance");
	
	return name;
}

void deletePoly_ComponentInstance(Instance* const this)
{
	ComponentInstance* pCompInstanceObj;
	pCompInstanceObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pCompInstanceObj);
	/*destroy base Obj*/
	delete_Instance(this);
}

void delete_ComponentInstance(ComponentInstance* const this)
{
	/* destroy base object */
	delete_Instance(this->super);
	/* destroy data memebers */
	free(this);
	
}

/*int _acceptComponentInstance(ComponentInstance* this, ComponentInstance* c, Visitor* visitor)
{
	int i;
	visitor->action((void*)this->name, (void*)c->name, 0);
	visitor->action((void*)this->typedefinition, (void*)c->typedefinition, 0);
}*/
