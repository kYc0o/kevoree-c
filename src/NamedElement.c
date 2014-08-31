#include "NamedElement.h"

NamedElement* new_NamedElement()
{
	NamedElement* pObj = NULL;
	/* Allocating memory */
	pObj = (NamedElement*)malloc(sizeof(NamedElement));

	if (pObj == NULL)
	{
		return NULL;
	}

	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;
	pObj->name = NULL;

	pObj->InternalGetKey = NamedElement_InternalGetKey;
	pObj->MetaClassName = NamedElement_MetaClassName;
	pObj->Delete = delete_NamedElement;
	pObj->VisitAttributes = NamedElement_VisitAttributes;
	pObj->VisitReferences = NamedElement_VisitAttributes;
	pObj->FindByPath = NamedElement_FindByPath;
	
	return pObj;
}

char* NamedElement_InternalGetKey(NamedElement* const this)
{
	return this->name;
}

char* NamedElement_MetaClassName(NamedElement* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("NamedElement")) + 1);
	if(name != NULL)
		strcpy(name, "NamedElement");
	else
		return NULL;
	
	return name;
}

void delete_NamedElement(NamedElement* const this)
{
	if(this != NULL)
	{
		free(this->name);
		free(this);
	}
}

void NamedElement_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
		char* cClass = NULL;
		/*sprintf(path,"%s\\cClass", parent);*/
		sprintf(path,"cClass");
		cClass = ((NamedElement*)this)->MetaClassName((NamedElement*)this);
		visitor->action(path, STRING, cClass);
		visitor->action(NULL, COLON, NULL);
		free(cClass);

		/*sprintf(path, "%s\\name", parent);*/
		sprintf(path, "name", parent);
		visitor->action(path, STRING, ((NamedElement*)(this))->name);
		visitor->action(NULL, COLON, NULL);
	}
	else
	{
		/*sprintf(path, "%s\\name", parent);*/
		visitor->action("", STRING, ((NamedElement*)(this))->name);
		visitor->action(NULL, COLON, NULL);
	}
}

void* NamedElement_FindByPath(char* attribute, NamedElement* const this)
{
	if(!strcmp("name",attribute))
	{
		return this->name;
	}
	else
	{
		printf("Wrong attribute\n");
		return NULL;
	}
}
