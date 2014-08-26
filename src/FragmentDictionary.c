#include "FragmentDictionary.h"

Dictionary* newPoly_FragmentDictionary()
{
	FragmentDictionary* pFragDicObj = NULL;
	Dictionary* pObj = new_Dictionary();

	/* Allocating memory */
	pFragDicObj = (FragmentDictionary*)malloc(sizeof(FragmentDictionary));

	if (pFragDicObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pFragDicObj; /* Pointing to derived object */
	((FragmentDictionary*)pObj->pDerivedObj)->super = pObj;
	pObj->VisitAttributes = FragmentDictionary_VisitAttributes;
	pObj->VisitReferences = FragmentDictionary_VisitReferences;
	
	pObj->MetaClassName = FragmentDictionary_MetaClassName;
	pObj->InternalGetKey = FragmentDictionary_InternalGetKey;
	
	pFragDicObj->name = NULL;
	
	pObj->FindByPath = FragmentDictionary_FindByPath;
	
	pObj->Delete = deletePoly_FragmentDictionary;

	return pObj;
}

FragmentDictionary* new_FragmentDictionary(void)
{
	FragmentDictionary* pFragDicObj = NULL;
	Dictionary* pObj = new_Dictionary();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pFragDicObj = (FragmentDictionary*)malloc(sizeof(FragmentDictionary));

	if (pFragDicObj == NULL)
	{
		return NULL;
	}

	pFragDicObj->super = pObj;
	pFragDicObj->VisitAttributes = FragmentDictionary_VisitAttributes;
	pFragDicObj->VisitReferences = FragmentDictionary_VisitReferences;
	
	pFragDicObj->name = NULL;
	
	pFragDicObj->MetaClassName = FragmentDictionary_MetaClassName;
	pObj->MetaClassName = FragmentDictionary_MetaClassName;
	pFragDicObj->InternalGetKey = FragmentDictionary_InternalGetKey;
	pFragDicObj->FindByPath = FragmentDictionary_FindByPath;
	
	pFragDicObj->Delete = delete_FragmentDictionary;

	return pFragDicObj;
}

void deletePoly_FragmentDictionary(void* const this)
{
	if(this != NULL)
	{
		FragmentDictionary* pFragDicObj;
		pFragDicObj = (FragmentDictionary*)((Dictionary*)this)->pDerivedObj;
		/*destroy derived obj*/
		free(pFragDicObj->name);
		free(pFragDicObj);
		/*destroy base Obj*/
		delete_Dictionary(((Dictionary*)this));
	}
}

void delete_FragmentDictionary(void* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_Dictionary(((FragmentDictionary*)this)->super);
		/* destroy data memebers */
		FragmentDictionary* pDicAttrObj = (FragmentDictionary*)this;
		free(pDicAttrObj->name);
		free(this);
	}
}

char* FragmentDictionary_InternalGetKey(FragmentDictionary* const this)
{
	return this->name;
}

char* FragmentDictionary_MetaClassName(FragmentDictionary* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("FragmentDictionary")) + 1);
	if(name != NULL)
		strcpy(name, "FragmentDictionary");
	else
		return NULL;
	
	return name;
}

void FragmentDictionary_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* Dictionary attributes */
	Dictionary_VisitAttributes(((FragmentDictionary*)this)->super, parent, visitor);
	
	/* Local attributes */
	sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((FragmentDictionary*)(this))->name);
}

void FragmentDictionary_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	Dictionary_VisitReferences(((FragmentDictionary*)(this))->super, parent, visitor);
}

void* FragmentDictionary_FindByPath(char* attribute, FragmentDictionary* const this)
{
	/* Dictionary attributes and references */
	if(!strcmp("generated_KMF_ID", attribute) || !strcmp("values", attribute))
	{
		return Dictionary_FindByPath(attribute, this->super);
	}
	/* Local attributes */
	else if(!strcmp("name", attribute))
	{
		return this->name;
	}
	/* There is no local references */
	else
	{
		printf("Wrong attribute or reference\n");
		return NULL;
	}
}
