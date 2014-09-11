#include <stdlib.h>
#include <string.h>
#include "NamedElement.h"
#include "NetworkInfo.h"
#include "NodeLink.h"
#include "Visitor.h"
#include "NetworkProperty.h"

NamedElement* newPoly_NetworkProperty()
{
	NetworkProperty* pNetPropObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pNetPropObj = (NetworkProperty*)my_malloc(sizeof(NetworkProperty));

	if (pNetPropObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pNetPropObj; /* Pointing to derived object */
	
	pNetPropObj->value = NULL;
	pNetPropObj->eContainerNL = NULL;
	pNetPropObj->eContainerNI = NULL;
	
	pObj->MetaClassName = NetworkProperty_MetaClassName;
	pObj->InternalGetKey = NetworkProperty_InternalGetKey;
	pObj->VisitAttributes = NetworkProperty_VisitAttributes;
	/*pObj->VisitReferences = NetworkProperty_VisitAttributes;*/
	
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
	pNetPropObj = (NetworkProperty*)my_malloc(sizeof(NetworkProperty));

	if (pNetPropObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pNetPropObj;  Pointing to derived object */
	pNetPropObj->super = pObj;
	
	pNetPropObj->value = NULL;
	pNetPropObj->eContainerNL = NULL;
	pNetPropObj->eContainerNI = NULL;

	pNetPropObj->MetaClassName = NetworkProperty_MetaClassName;
	pObj->MetaClassName = NetworkProperty_MetaClassName;
	pNetPropObj->InternalGetKey = NetworkProperty_InternalGetKey;
	pNetPropObj->VisitAttributes = NetworkProperty_VisitAttributes;
	
	pNetPropObj->Delete = delete_NetworkProperty;

	return pNetPropObj;
}

char* NetworkProperty_InternalGetKey(NetworkProperty* const this)
{
	return this->super->InternalGetKey(this->super);
}

char* NetworkProperty_MetaClassName(NetworkProperty* const this)
{
	char *name = NULL;

	name = my_malloc(sizeof(char) * (strlen("NetworkProperty")) + 1);
	if(name != NULL)
		strcpy(name, "NetworkProperty");
	else
		return NULL;
	
	return name;
}

void deletePoly_NetworkProperty(NamedElement* const this)
{
	if(this != NULL)
	{
		NetworkProperty* pNetPropObj;
		pNetPropObj = this->pDerivedObj;
		/*destroy derived obj*/
		free(pNetPropObj->value);
		free(pNetPropObj->eContainerNL);
		free(pNetPropObj->eContainerNI);
		free(pNetPropObj);
		/*destroy base Obj*/
		delete_NamedElement(this);
	}
}

void delete_NetworkProperty(NetworkProperty* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_NamedElement(this->super);
		/* destroy data memebers */
		free(this->value);
		free(this->eContainerNL);
		free(this->eContainerNI);
		free(this);
		/*this = NULL;*/
	}
	
}

void NetworkProperty_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	visitor->action(path, STRING, ((NetworkProperty*)this)->MetaClassName((NetworkProperty*)this));*/

	NamedElement_VisitAttributes(((NetworkProperty*)(this))->super, parent, visitor, true);
	
	/*sprintf(path, "%s\\value", parent);*/
	sprintf(path, "value", parent);
	visitor->action(path, STRING, ((NetworkProperty*)this)->value);
	visitor->action(NULL, RETURN, NULL);
}

void* NetworkProperty_FindByPath(char* attribute, NetworkProperty* const this)
{
	/* NamedElement attributes */
	if(!strcmp("name", attribute))
	{
		return this->super->FindByPath(attribute, this->super);
	}
	/* Local attributes */
	else if(!strcmp("value", attribute))
	{
		return this->value;
	}
	else
	{
		printf("Wrong path\n");
		return NULL;
	}
}

