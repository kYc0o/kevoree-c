#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Visitor.h"
#include "NamedElement.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

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

	pObj->internalGetKey = NamedElement_internalGetKey;
	pObj->metaClassName = NamedElement_metaClassName;
	pObj->Delete = delete_NamedElement;
	pObj->VisitAttributes = NamedElement_VisitAttributes;
	pObj->VisitPathAttributes = NamedElement_VisitPathAttributes;
	pObj->VisitReferences = NamedElement_VisitAttributes;
	pObj->VisitPathReferences = NamedElement_VisitPathAttributes;
	pObj->FindByPath = NamedElement_FindByPath;
	
	return pObj;
}

char* NamedElement_internalGetKey(void * const this)
{
	NamedElement *pObj = (NamedElement*)this;
	return pObj->name;
}

char* NamedElement_metaClassName(void * const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("NamedElement")) + 1);
	if(name != NULL)
		strcpy(name, "NamedElement");
	else
		return NULL;
	
	return name;
}

void delete_NamedElement(void * const this)
{
	if(this != NULL)
	{
		NamedElement *pObj = (NamedElement*)this;
		free(pObj->name);
		free(pObj);
	}
}

void NamedElement_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
		char* cClass = NULL;
		cClass = malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((NamedElement*)this)->metaClassName((NamedElement*)this))) + 1);
		sprintf(cClass, "org.kevoree.%s", ((NamedElement*)this)->metaClassName((NamedElement*)this));
		sprintf(path,"eClass");
		visitor->action(path, STRING, cClass);
		visitor->action(NULL, COLON, NULL);
		free(cClass);

		sprintf(path, "name");
		visitor->action(path, STRING, ((NamedElement*)(this))->name);
		visitor->action(NULL, COLON, NULL);
	}
	else
	{
		visitor->action("", STRING, ((NamedElement*)(this))->name);
		visitor->action(NULL, COLON, NULL);
	}
}

void NamedElement_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
		/*char* cClass = NULL;
		sprintf(path,"%s\\cClass", parent);
		cClass = ((NamedElement*)this)->metaClassName((NamedElement*)this);
		visitor->action(path, STRING, cClass);
		free(cClass);*/

		sprintf(path, "%s\\name", parent);
		visitor->action(path, STRING, ((NamedElement*)(this))->name);
	}
	else
	{
		sprintf(path, "%s\\name", parent);
		visitor->action(path, REFERENCE, ((NamedElement*)(this))->name);
	}
}

void* NamedElement_FindByPath(char* attribute, void * const this)
{
	NamedElement *pObj = (NamedElement*)this;
	if(!strcmp("name", attribute))
	{
		return pObj->name;
	}
	else
	{
		PRINTF("Wrong attribute\n");
		return NULL;
	}
}
