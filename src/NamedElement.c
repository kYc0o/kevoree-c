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
	
	return pObj;
}

char* NamedElement_InternalGetKey(NamedElement* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->name)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->name);

	return internalKey;
}

char* NamedElement_MetaClassName(NamedElement* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("NamedElement") + 1));
	strcpy(name, "NamedElement");
	
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

void NamedElement_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));

	sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((NamedElement*)(this))->name);
}

/*int _acceptNamedElement(NamedElement* this, NamedElement* c, Visitor* visitor)
{
	visitor->action((void*)this->name, (void*)c->name, 0);
}*/