#include "DeployUnit.h"

NamedElement* newPoly_DeployUnit()
{
	DeployUnit* pDepUnitObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pDepUnitObj = (DeployUnit*)malloc(sizeof(DeployUnit));

	if (pDepUnitObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pDepUnitObj; /* Pointing to derived object */
	
	pDepUnitObj->groupName = NULL;
	pDepUnitObj->version = NULL;
	pDepUnitObj->url = NULL;
	pDepUnitObj->hashcode = NULL;
	pDepUnitObj->type = NULL;
	pDepUnitObj->requiredLibs = NULL;
	
	pDepUnitObj->AddRequiredLibs = DeployUnit_AddRequiredLibs;
	pDepUnitObj->RemoveRequiredLibs = DeployUnit_RemoveRequiredLibs;
	pDepUnitObj->FindRequiredLibsByID = DeployUnit_FindRequiredLibsByID;
	
	pObj->MetaClassName = DeployUnit_MetaClassName;
	pObj->InternalGetKey = DeployUnit_InternalGetKey;
	pObj->VisitAttributes = DeployUnit_VisitAttributes;
	pObj->VisitReferences = DeployUnit_VisitReferences;
	pObj->FindByPath = DeployUnit_FindByPath;
	
	pObj->Delete = deletePoly_DeployUnit;

	return pObj;
}

DeployUnit* new_DeployUnit()
{
	DeployUnit* pDepUnitObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;
	
	/* Allocating memory */
	pDepUnitObj = (DeployUnit*)malloc(sizeof(DeployUnit));

	if (pDepUnitObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pDepUnitObj;  Pointing to derived object */
	pDepUnitObj->super = pObj; /* Pointing to the base object */
	
	pDepUnitObj->groupName = NULL;
	pDepUnitObj->version = NULL;
	pDepUnitObj->url = NULL;
	pDepUnitObj->hashcode = NULL;
	pDepUnitObj->type = NULL;
	pDepUnitObj->requiredLibs = NULL;
	
	pDepUnitObj->AddRequiredLibs = DeployUnit_AddRequiredLibs;
	pDepUnitObj->RemoveRequiredLibs = DeployUnit_RemoveRequiredLibs;
	pDepUnitObj->FindRequiredLibsByID = DeployUnit_FindRequiredLibsByID;
	
	pDepUnitObj->MetaClassName = DeployUnit_MetaClassName;
	pDepUnitObj->InternalGetKey = DeployUnit_InternalGetKey;
	pDepUnitObj->VisitAttributes = DeployUnit_VisitAttributes;
	pDepUnitObj->VisitReferences = DeployUnit_VisitReferences;
	pDepUnitObj->FindByPath = DeployUnit_FindByPath;
	
	pDepUnitObj->Delete = delete_DeployUnit;

	return pDepUnitObj;
}

char* DeployUnit_InternalGetKey(DeployUnit* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen("groupName=") + strlen(this->groupName) + strlen(",") +
										strlen("hashcode=") + strlen(this->hashcode) + strlen(",") +
										strlen("name=") + strlen(this->super->name) + strlen(",") +
										strlen("version=") + strlen(this->version)) + 1);

	if (internalKey == NULL)
		return NULL;

	sprintf(internalKey, "groupName=%s,hashcode=%s,name=%s,version=%s",
						this->groupName, this->hashcode, this->super->name, this->version);

	return internalKey;
}

char* DeployUnit_MetaClassName(DeployUnit* const this)
{
	char name[11];
	memset(&name[0], 0, sizeof(name));

	/*name = malloc(sizeof(char) * (strlen("DeployUnit") + 1));*/
	strcpy(name, "DeployUnit");
	
	return name;
}

void DeployUnit_AddRequiredLibs(DeployUnit* const this, DeployUnit* ptr)
{
	DeployUnit* container = NULL;
	
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The DeployUnit cannot be added in DeployUnit because the key is not defined\n");
	}
	else
	{
		if(this->requiredLibs == NULL)
		{
			this->requiredLibs = hashmap_new();
		}
		if(hashmap_get(this->requiredLibs, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (DeployUnit*)ptr;*/
			hashmap_put(this->requiredLibs, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void DeployUnit_RemoveRequiredLibs(DeployUnit* const this, DeployUnit *ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The DeployUnit cannot be removed in DeployUnit because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->requiredLibs, ptr->InternalGetKey(ptr));
	}
}

DeployUnit* DeployUnit_FindRequiredLibsByID(DeployUnit* const this, char* id)
{
	DeployUnit* value = NULL;

	if(hashmap_get(this->requiredLibs, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void deletePoly_DeployUnit(NamedElement* const this)
{
	DeployUnit* pDepUnitObj;
	pDepUnitObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pDepUnitObj->groupName);
	free(pDepUnitObj->version);
	free(pDepUnitObj->url);
	free(pDepUnitObj->hashcode);
	free(pDepUnitObj->type);
	hashmap_free(pDepUnitObj->requiredLibs);
	free(pDepUnitObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_DeployUnit(DeployUnit* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	free(this->groupName);
	free(this->version);
	free(this->url);
	free(this->hashcode);
	free(this->type);
	hashmap_free(this->requiredLibs);
	free(this);
}

void DeployUnit_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	NamedElement_VisitAttributes(((DeployUnit*)(this))->super, parent, visitor);
	
	if(recursive)
	{
		sprintf(path,"%s\\groupName",parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->groupName);

		sprintf(path, "%s\\version", parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->version);

		sprintf(path,"%s\\url",parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->url);

		sprintf(path, "%s\\hashcode", parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->hashcode);

		sprintf(path, "%s\\type", parent);
		visitor->action(path, STRING, ((DeployUnit*)(this))->type);
	}
}

void DeployUnit_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	if(((DeployUnit*)(this))->requiredLibs != NULL)
	{
		int i;
		/*sprintf(path,"%s/requiredLibs[%s]", parent, ((DeployUnit*)(this))->super->name);*/

		/* requiredLibs */
		hashmap_map* m = ((DeployUnit*)(this))->requiredLibs;

		/* compare requiredLibs */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				DeployUnit* n = data;
				sprintf(path,"%s/requiredLibs[%s]", parent, /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor, 0);
				/*n->VisitReferences(n, path, visitor);*/
			}
		}
	}
}

void* DeployUnit_FindByPath(char* attribute, DeployUnit* const this)
{	
	/* NamedElement attributes */
	if(!strcmp("name", attribute))
	{
		return this->super->FindByPath(attribute, this->super);
	}
	/* Local attributes */
	else if(!strcmp("groupName", attribute))
	{
		return this->groupName;
	}
	else if(!strcmp("version", attribute))
	{
		return this->version;
	}
	else if(!strcmp("url", attribute))
	{
		return this->url;
	}
	else if(!strcmp("hashcode", attribute))
	{
		return this->hashcode;
	}
	else if(!strcmp("type", attribute))
	{
		return this->type;
	}
	/* Local references */
	else
	{
		char* nextAttribute = NULL;
		char* path = strdup(attribute);
		char* pch;

		if(indexOf(path,"/") != -1)
		{
			pch = strtok (path,"/");
			/*nextAttribute = strtok(NULL, "\\");
			sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));*/
			if(strchr(attribute,'\\') != NULL)
			{
				/*printf("Attribute found at: %d\n", strchr(attribute,'\\')-attribute+1);*/
				nextAttribute = strtok(NULL, "\\");
				sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));
			}
			else
			{
				/*printf("Attribute not found, looking for path\n");*/
				nextAttribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			nextAttribute = strtok(pch, "\\");
			nextAttribute = strtok(NULL, "\\");
		}
		
		/*printf("Token: %s\n", pch);*/

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
		
		/*printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("next attribute: %s\n", nextAttribute);*/
	  
		if(!strcmp("requiredLibs", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindRequiredLibsByID(this, queryID);
			}
			else
			{
				DeployUnit* reqlibs = this->FindRequiredLibsByID(this, queryID);
				if(reqlibs != NULL)
					return reqlibs->FindByPath(nextAttribute, reqlibs);
				else
					return NULL;
			}
		}
		else
		{
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
