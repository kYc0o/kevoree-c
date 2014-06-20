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
	
	pObj->InternalGetKey = Repository_InternalGetKey;
	pObj->MetaClassName = Repository_MetaClassName;
	pObj->Delete = delete_Repository;
	
	return pObj;
}

char* Repository_MetaClassName(Repository* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("Repository") + 1));
	strcpy(name, "Repository");
	
	return name;
}

char* Repository_InternalGetKey(Repository* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->url)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->url);

	return internalKey;
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