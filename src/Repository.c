#include "Repository.h"
#include "Visitor.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

Repository* new_Repository()
{
	Repository* pObj;
	/* Allocating memory */
	pObj = (Repository*)malloc(sizeof(Repository));

	if (pObj == NULL)
	{
		return NULL;
	}
	
	pObj->url = NULL;
	pObj->eContainer = NULL;
	
	pObj->internalGetKey = Repository_internalGetKey;
	pObj->metaClassName = Repository_metaClassName;
	pObj->Delete = delete_Repository;
	pObj->VisitAttributes = Repository_VisitAttributes;
	pObj->VisitPathAttributes = Repository_VisitPathAttributes;
	pObj->FindByPath = Repository_FindByPath;
	
	return pObj;
}

char* Repository_metaClassName(void * const this)
{
	/*char *name;

	name = malloc(sizeof(char) * (strlen("Repository")) + 1);
	if(name != NULL)
		strcpy(name, "Repository");
	else
		return NULL;
	
	return name;
	*/
	return "Repository";
}

char* Repository_internalGetKey(void * const this)
{
	Repository *pObj = (Repository*)this;
	return pObj->url;
}

void delete_Repository(void * const this)
{
	/* destroy data memebers */
	if(this != NULL)
	{
		Repository *pObj = (Repository*)this;
		free(pObj->url);
		free(pObj->eContainer);
		free(pObj);
		/*this = NULL;*/
	}
}

void Repository_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	cClass = malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((Repository*)this)->metaClassName((Repository*)this))) + 1);
	sprintf(cClass, "org.kevoree.%s", ((Repository*)this)->metaClassName((Repository*)this));
	sprintf(path,"eClass");
	visitor->action(path, STRING, cClass);
	visitor->action(NULL, COLON, NULL);
	free(cClass);

	sprintf(path, "url");
	visitor->action(path, STRING, ((Repository*)(this))->url);
	visitor->action(NULL, RETURN, NULL);
}

void Repository_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	cClass = ((Repository*)this)->metaClassName((Repository*)this);
	visitor->action(path, STRING, cClass);
	free(cClass);*/

	sprintf(path,"%s\\url",parent);
	visitor->action(path, STRING, ((Repository*)(this))->url);
}

void* Repository_FindByPath(char* attribute, void * const this)
{
	Repository *pObj = (Repository*)this;
	if(!strcmp("url", attribute))
	{
		return pObj->url;
	}
	else
	{
		PRINTF("Wrong path\n");
		return NULL;
	}
}
