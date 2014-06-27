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
	pCompInstanceObj->VisitAttributes = ComponentInstance_VisitAttributes;
	
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
	pCompInstanceObj->super = pObj;
	pCompInstanceObj->VisitAttributes = ComponentInstance_VisitAttributes;
	
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

void ComponentInstance_VisitAttributes(ComponentInstance* const this, char *parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));
	sprintf(path, "%s/components[%s]", parent, this->super->super->name);

	sprintf(path, "%s\\name", path);

	visitor->action(path, STRING, this->super->super->name);
	
	sprintf(path, "%s\\started", path);
	visitor->action(path, BOOL, (int)(this->super->started));
}

/*void ComponentInstance_VisitReferences*/

/*int _acceptComponentInstance(ComponentInstance* this, ComponentInstance* c, Visitor* visitor)
{
	int i;
	visitor->action((void*)this->name, (void*)c->name, 0);
	visitor->action((void*)this->typedefinition, (void*)c->typedefinition, 0);
}*/
