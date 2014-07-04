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
	
	pObj->MetaClassName = NetworkProperty_MetaClassName;
	pObj->InternalGetKey = NetworkProperty_InternalGetKey;
	pObj->VisitAttributes = NetworkProperty_VisitAttributes;
	pObj->VisitReferences = NetworkProperty_VisitAttributes;
	
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
	pNetPropObj->VisitAttributes = NetworkProperty_VisitAttributes;
	pNetPropObj->VisitReferences = NetworkProperty_VisitAttributes;
	
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

void NetworkProperty_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));

	sprintf(path, "%s/%s", parent, ((NetworkProperty*)(this))->super->name);

	/*sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((NetworkProperty*)(this))->super->name);*/
	NamedElement_VisitAttributes(((NetworkProperty*)(this))->super, parent, visitor);
}

/*int _acceptNetworkProperty(NetworkProperty* this, NetworkProperty* c, Visitor* visitor)
{
	visitor->action((void*)this->value, (void*)c->value, 0);
}*/