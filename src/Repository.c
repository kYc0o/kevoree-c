#include "Repository.h"

Repository* new_Repository()
{
	Repository* pObj;
	/* Allocating memory */
	pObj = (Repository*)malloc(sizeof(Repository));

	if (pObj == NULL)
	{
		return NULL;
	}

	/* pointing to itself as we are creating base class object*/
	pObj->pDerivedObj = pObj;
	
	pObj->url = NULL;
	
	pObj->InternalGetKey = Repository_InternalGetKey;
	pObj->MetaClassName = Repository_MetaClassName;
	pObj->Delete = delete_Repository;
	pObj->VisitAttributes = Repository_VisitAttributes;
	pObj->FindByPath = Repository_FindByPath;
	/*pObj->VisitReferences = Repository_VisitAttributes;*/
	
	return pObj;
}

char* Repository_MetaClassName(Repository* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("Repository")) + 1);
	if(name != NULL)
		strcpy(name, "Repository");
	else
		return NULL;
	
	return name;
}

char* Repository_InternalGetKey(Repository* const this)
{
	return this->url;
}

void delete_Repository(Repository* const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		free(this->url);
		free(this);
	}
}

void Repository_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	cClass = ((Repository*)this)->MetaClassName((Repository*)this);
	visitor->action(path, STRING, cClass);
	free(cClass);

	sprintf(path,"%s\\url",parent);
	visitor->action(path, STRING, ((Repository*)(this))->url);
}

void* Repository_FindByPath(char* attribute, Repository* const this)
{
	if(!strcmp("url",attribute))
	{
		return this->url;
	}
	else
	{
		printf("Wrong path\n");
		return NULL;
	}
}
