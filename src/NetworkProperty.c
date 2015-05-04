#include <stdlib.h>
#include <string.h>
#include "NamedElement.h"
#include "NetworkInfo.h"
#include "NodeLink.h"
#include "Visitor.h"
#include "NetworkProperty.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

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
	
	pNetPropObj->value = NULL;
	pNetPropObj->eContainer = NULL;
	
	pObj->metaClassName = NetworkProperty_metaClassName;
	pObj->internalGetKey = NetworkProperty_internalGetKey;
	pObj->VisitAttributes = NetworkProperty_VisitAttributes;
	pObj->VisitPathAttributes = NetworkProperty_VisitPathAttributes;
	pObj->FindByPath = NetworkProperty_FindByPath;
	
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

	pNetPropObj->super = pObj;
	
	pNetPropObj->value = NULL;
	pNetPropObj->eContainer = NULL;

	pNetPropObj->metaClassName = NetworkProperty_metaClassName;
	pObj->metaClassName = NetworkProperty_metaClassName;
	pNetPropObj->internalGetKey = NetworkProperty_internalGetKey;
	pNetPropObj->VisitAttributes = NetworkProperty_VisitAttributes;
	pNetPropObj->VisitPathAttributes = NetworkProperty_VisitPathAttributes;
	pNetPropObj->FindByPath = NetworkProperty_FindByPath;
	
	pNetPropObj->Delete = delete_NetworkProperty;

	return pNetPropObj;
}

char* NetworkProperty_internalGetKey(void * const this)
{
	NetworkProperty *pObj = (NetworkProperty*)this;
	return pObj->super->internalGetKey(pObj->super);
}

char* NetworkProperty_metaClassName(void * const this)
{
	/*char *name = NULL;

	name = malloc(sizeof(char) * (strlen("NetworkProperty")) + 1);
	if(name != NULL)
		strcpy(name, "NetworkProperty");
	else
		return NULL;
	
	return name;
	*/
	return "NetworkProperty";
}

void deletePoly_NetworkProperty(void * const this)
{
	if(this != NULL)
	{
		NamedElement *pObj = (NamedElement*)this;
		NetworkProperty* pNetPropObj;
		pNetPropObj = pObj->pDerivedObj;
		/*destroy derived obj*/
		free(pNetPropObj->value);
		free(pNetPropObj);
		/*destroy base Obj*/
		delete_NamedElement(pObj);
	}
}

void delete_NetworkProperty(void * const this)
{
	if(this != NULL)
	{
		NetworkProperty *pObj = (NetworkProperty*)this;
		/* destroy base object */
		delete_NamedElement(pObj->super);
		/* destroy data memebers */
		free(pObj->value);
		free(pObj);
		/*this = NULL;*/
	}
	
}

void NetworkProperty_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	NamedElement_VisitAttributes(((NetworkProperty*)(this))->super, parent, visitor, true);
	
	sprintf(path, "value");
	visitor->action(path, STRING, ((NetworkProperty*)this)->value);
	visitor->action(NULL, RETURN, NULL);
}

void NetworkProperty_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	NamedElement_VisitPathAttributes(((NetworkProperty*)(this))->super, parent, visitor, true);

	sprintf(path, "%s\\value", parent);
	visitor->action(path, STRING, ((NetworkProperty*)this)->value);
}

void* NetworkProperty_FindByPath(char *attribute, void *const this)
{
	NetworkProperty *pObj = (NetworkProperty*)this;
	/* NamedElement attributes */
	if(!strcmp("name", attribute))
	{
		return pObj->super->FindByPath(attribute, pObj->super);
	}
	/* Local attributes */
	else if(!strcmp("value", attribute))
	{
		return pObj->value;
	}
	else
	{
		PRINTF("Wrong path\n");
		return NULL;
	}
}

