#include "NetworkProperty.h"

NamedElement* newPoly_NetworkProperty()
{
	NetworkProperty* pNetPropObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pNetPropObj = (NetworkProperty*)malloc(sizeof(NetworkProperty));

	if (pNetPropObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pNetPropObj; /* Pointing to derived object */
	
	pNetPropObj->MetaClassName = NetworkProperty_MetaClassName;
	pNetPropObj->InternalGetKey = NetworkProperty_InternalGetKey;
	
	pObj->Delete = deletePoly_NetworkProperty;

	return pObj;
}

NetworkProperty* new_NetworkProperty()
{
	NetworkProperty* pNetPropObj = NULL;
	NamedElement* pObj = new_NamedElement();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pNetPropObj = (NetworkProperty*)malloc(sizeof(NetworkProperty));

	if (pNetPropObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pNetPropObj;  Pointing to derived object */
	pNetPropObj->super = pObj;
	
	pNetPropObj->MetaClassName = NetworkProperty_MetaClassName;
	pNetPropObj->InternalGetKey = NetworkProperty_InternalGetKey;
	
	pNetPropObj->Delete = delete_NetworkProperty;

	return pNetPropObj;
}

char* NetworkProperty_InternalGetKey(NetworkProperty* const this)
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

char* NetworkProperty_MetaClassName(NetworkProperty* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("NetworkProperty") + 1));
	strcpy(name, "NetworkProperty");
	
	return name;
}

void deletePoly_NetworkProperty(NamedElement* const this)
{
	NetworkProperty* pNetPropObj;
	pNetPropObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pNetPropObj->value);
	free(pNetPropObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_NetworkProperty(NetworkProperty* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	free(this->value);
	free(this);
	
}

/*int _acceptNetworkProperty(NetworkProperty* this, NetworkProperty* c, Visitor* visitor)
{
	visitor->action((void*)this->value, (void*)c->value, 0);
}*/