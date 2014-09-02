#include "Repository.h"
#include "Visitor.h"

Repository* new_Repository()
{
	Repository* pObj;
	/* Allocating memory */
	pObj = (Repository*)my_malloc(sizeof(Repository));

	if (pObj == NULL)
	{
		return NULL;
	}
	
	pObj->url = NULL;
	pObj->eContainer = NULL;
	
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

	name = my_malloc(sizeof(char) * (strlen("Repository")) + 1);
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
		free(this->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

void Repository_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);*/
	cClass = my_malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((Repository*)this)->MetaClassName((Repository*)this))) + 1);
	sprintf(cClass, "org.kevoree.%s", ((Repository*)this)->MetaClassName((Repository*)this));
	sprintf(path,"eClass");
	/*cClass = ((Repository*)this)->MetaClassName((Repository*)this);*/
	visitor->action(path, STRING, cClass);
	visitor->action(NULL, COLON, NULL);
	str_free(cClass);

	/*sprintf(path,"%s\\url",parent);*/
	sprintf(path, "url");
	visitor->action(path, STRING, ((Repository*)(this))->url);
	visitor->action(NULL, RETURN, NULL);
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
