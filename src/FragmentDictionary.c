#include "Dictionary.h"
#include "Instance.h"
#include "Visitor.h"
#include "FragmentDictionary.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

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
	pObj->VisitPathAttributes = FragmentDictionary_VisitPathAttributes;
	pObj->VisitReferences = FragmentDictionary_VisitReferences;
	pObj->VisitPathReferences = FragmentDictionary_VisitPathReferences;
	
	pObj->metaClassName = FragmentDictionary_metaClassName;
	pObj->internalGetKey = FragmentDictionary_internalGetKey;
	
	pFragDicObj->name = NULL;
	pFragDicObj->eContainer = NULL;
	
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
	pFragDicObj->VisitPathAttributes = FragmentDictionary_VisitPathAttributes;
	pFragDicObj->VisitReferences = FragmentDictionary_VisitReferences;
	pFragDicObj->VisitPathReferences = FragmentDictionary_VisitPathReferences;
	
	pFragDicObj->name = NULL;
	pFragDicObj->eContainer = NULL;
	
	pFragDicObj->metaClassName = FragmentDictionary_metaClassName;
	pObj->metaClassName = FragmentDictionary_metaClassName;
	pFragDicObj->internalGetKey = FragmentDictionary_internalGetKey;
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
		free(pFragDicObj->eContainer);
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
		free(pDicAttrObj->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

char* FragmentDictionary_internalGetKey(void* const this)
{
	FragmentDictionary *pObj = (FragmentDictionary*)this;
	return pObj->name;
}

char* FragmentDictionary_metaClassName(void* const this)
{
	/*char *name;

	name = malloc(sizeof(char) * (strlen("FragmentDictionary")) + 1);
	if(name != NULL)
		strcpy(name, "FragmentDictionary");
	else
		return NULL;
	
	return name;
	*/
	return "FragmentDictionary";
}

void FragmentDictionary_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* Dictionary attributes */
	Dictionary_VisitAttributes(((FragmentDictionary*)this)->super, parent, visitor, recursive);
	
	/* Local attributes */
	sprintf(path, "name");
	visitor->action(path, STRING, ((FragmentDictionary*)(this))->name);
	visitor->action(NULL, COLON, NULL);
}

void FragmentDictionary_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* Dictionary attributes */
	Dictionary_VisitPathAttributes(((FragmentDictionary*)this)->super, parent, visitor, recursive);

	/* Local attributes */
	sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((FragmentDictionary*)(this))->name);
}

void FragmentDictionary_VisitReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	Dictionary_VisitReferences(((FragmentDictionary*)(this))->super, parent, visitor, recursive);
}

void FragmentDictionary_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	Dictionary_VisitPathReferences(((FragmentDictionary*)(this))->super, parent, visitor, recursive);
}

void* FragmentDictionary_FindByPath(char* attribute, void* const this)
{
	FragmentDictionary *pObj = (FragmentDictionary*)this;

	/* Local attributes */
	if(!strcmp("name", attribute))
	{
		return pObj->name;
	}
	/* Dictionary attributes and references */
	else /*(!strcmp("generated_KMF_ID", attribute) || !strcmp("values", attribute))*/
	{
		return Dictionary_FindByPath(attribute, pObj->super);
	}
}
