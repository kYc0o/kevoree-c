#include "Visitor.h"
#include "Dictionary.h"
#include "DictionaryValue.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

DictionaryValue* new_DictionaryValue(void)
{
	DictionaryValue* pObj = NULL;
	/* Allocating memory */
	pObj = (DictionaryValue*)malloc(sizeof(DictionaryValue));

	if (pObj == NULL)
	{
		return NULL;
	}
	
	pObj->name = NULL;
	pObj->value = NULL;
	pObj->eContainer = NULL;

	pObj->internalGetKey = DictionaryValue_internalGetKey;
	pObj->metaClassName = DictionaryValue_metaClassName;
	pObj->Delete = delete_DictionaryValue;
	pObj->VisitAttributes = DictionaryValue_VisitAttributes;
	pObj->VisitPathAttributes = DictionaryValue_VisitPathAttributes;
	pObj->FindByPath = DictionaryValue_FindByPath;
	
	return pObj;
}

void delete_DictionaryValue(void* const this)
{
	if(this != NULL)
	{
		DictionaryValue *pObj = (DictionaryValue*)this;
		free(pObj->name);
		free(pObj->value);
		free(pObj->eContainer);
		free(pObj);
		/*this = NULL;*/
	}
}

char *DictionaryValue_internalGetKey(void* const this)
{
	DictionaryValue *pObj = (DictionaryValue*)this;
	return pObj->name;
}

char* DictionaryValue_metaClassName(void* const this)
{
	/*
	 * TODO avoid to send an allocated pointer
	 */
	char *name;

	name = malloc(sizeof(char) * (strlen("DictionaryValue")) + 1);
	if(name != NULL)
		strcpy(name, "DictionaryValue");
	else
		return NULL;
	
	return name;
}

void DictionaryValue_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	cClass = malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((DictionaryValue*)this)->metaClassName((DictionaryValue*)this))) + 1);
	sprintf(cClass, "org.kevoree.%s", ((DictionaryValue*)this)->metaClassName((DictionaryValue*)this));
	sprintf(path,"eClass");
	visitor->action(path, STRING, cClass);
	visitor->action(NULL, COLON, NULL);
	free(cClass);

	sprintf(path, "name");
	visitor->action(path, STRING, ((DictionaryValue*)(this))->name);
	visitor->action(NULL, COLON, NULL);
	
	sprintf(path, "value");
	visitor->action(path, STRING, ((DictionaryValue*)(this))->value);
	visitor->action(NULL, RETURN, NULL);
}

void DictionaryValue_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	cClass = ((DictionaryValue*)this)->metaClassName((DictionaryValue*)this);
	visitor->action(path, STRING, cClass);
	free(cClass);*/

	sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((DictionaryValue*)(this))->name);

	sprintf(path, "%s\\value", parent);
	visitor->action(path, STRING, ((DictionaryValue*)(this))->value);
}

void* DictionaryValue_FindByPath(char* attribute, void* const this)
{
	DictionaryValue *pObj = (DictionaryValue*)this;
	/* Local attributes */
	if(!strcmp("name", attribute))
	{
		return pObj->name;
	}
	else if(!strcmp("value", attribute))
	{
		return pObj->value;
	}
	/* There is no local references */
	else
	{
		PRINTF("Wrong attribute or reference\n");
		return NULL;
	}
}
