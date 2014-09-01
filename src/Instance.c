#include "Instance.h"

NamedElement* newPoly_Instance()
{
	Instance* pInstanceObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pInstanceObj = (Instance*)malloc(sizeof(Instance));

	if (pInstanceObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pInstanceObj; /* Pointing to derived object */
	
	pInstanceObj->metaData = NULL;
	pInstanceObj->started = -1;
	pInstanceObj->typeDefinition = NULL;
	pInstanceObj->dictionary = NULL;
	pInstanceObj->fragmentDictionary = NULL;
	
	pInstanceObj->FindFragmentDictionaryByID = Instance_FindFragmentDictionaryByID;
	pInstanceObj->AddTypeDefinition = Instance_AddTypeDefinition;
	pInstanceObj->AddDictionary = Instance_AddDictionary;
	pInstanceObj->AddFragmentDictionary = Instance_AddFragmentDictionary;
	pInstanceObj->RemoveTypeDefinition = Instance_RemoveTypeDefinition;
	pInstanceObj->RemoveDictionary = Instance_RemoveDictionary;
	pInstanceObj->RemoveFragmentDictionary = Instance_RemoveFragmentDictionary;
	
	pObj->MetaClassName = Instance_MetaClassName;
	pObj->InternalGetKey = Instance_InternalGetKey;
	pObj->Delete = deletePoly_Instance;
	pObj->VisitAttributes = Instance_VisitAttributes;
	pObj->VisitReferences = Instance_VisitReferences;

	return pObj;
}

Instance* new_Instance()
{
	Instance* pInstanceObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pInstanceObj = (Instance*)malloc(sizeof(Instance));

	if (pInstanceObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pInstanceObj; Pointing to derived object */
	pInstanceObj->super = pObj;
	
	pInstanceObj->metaData = NULL;
	pInstanceObj->started = -1;
	pInstanceObj->typeDefinition = NULL;
	pInstanceObj->dictionary = NULL;
	pInstanceObj->fragmentDictionary = NULL;
	
	pInstanceObj->FindFragmentDictionaryByID = Instance_FindFragmentDictionaryByID;
	pInstanceObj->AddTypeDefinition = Instance_AddTypeDefinition;
	pInstanceObj->AddDictionary = Instance_AddDictionary;
	pInstanceObj->AddFragmentDictionary = Instance_AddFragmentDictionary;
	pInstanceObj->RemoveTypeDefinition = Instance_RemoveTypeDefinition;
	pInstanceObj->RemoveDictionary = Instance_RemoveDictionary;
	pInstanceObj->RemoveFragmentDictionary = Instance_RemoveFragmentDictionary;
	
	pInstanceObj->MetaClassName = Instance_MetaClassName;
	pObj->MetaClassName = pInstanceObj->MetaClassName;
	pInstanceObj->InternalGetKey = Instance_InternalGetKey;
	pInstanceObj->Delete = delete_Instance;
	pInstanceObj->VisitAttributes = Instance_VisitAttributes;
	pInstanceObj->VisitReferences = Instance_VisitReferences;

	return pInstanceObj;
}

FragmentDictionary* Instance_FindFragmentDictionaryByID(Instance* const this, char* id)
{
	FragmentDictionary* value = NULL;

	if(this->fragmentDictionary != NULL)
	{
		if(hashmap_get(this->fragmentDictionary, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void Instance_AddTypeDefinition(Instance* this, TypeDefinition* ptr)
{
	this->typeDefinition = ptr;
}

void Instance_AddDictionary(Instance* const this, Dictionary* ptr)
{
	this->dictionary = ptr;
}

void Instance_AddFragmentDictionary(Instance* const this, FragmentDictionary* ptr)
{
	FragmentDictionary* container = NULL;

	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The FragmentDictionary cannot be added in Instance because the key is not defined\n");
	}
	else
	{
		if(this->fragmentDictionary == NULL)
		{
			this->fragmentDictionary = hashmap_new();
		}
		if(hashmap_get(this->fragmentDictionary, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (FragmentDictionary*)ptr;*/
			hashmap_put(this->fragmentDictionary, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void Instance_RemoveTypeDefinition(Instance* const this, TypeDefinition* ptr)
{
	free(ptr);
	this->typeDefinition = NULL;
}

void Instance_RemoveDictionary(Instance* const this, Dictionary* ptr)
{
	free(ptr);
	this->dictionary = NULL;
}

void Instance_RemoveFragmentDictionary(Instance* const this, FragmentDictionary* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The FragmentDictionary cannot be removed in Instance because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->fragmentDictionary, ptr->InternalGetKey(ptr));
	}
}

char* Instance_InternalGetKey(Instance* const this)
{
	return this->super->InternalGetKey(this->super);
}

char* Instance_MetaClassName(Instance* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("Instance")) + 1);
	if(name != NULL)
		strcpy(name, "Instance");
	else
		return NULL;
	
	return name;
}

void deletePoly_Instance(NamedElement* const this)
{
	Instance* pInstanceObj;
	pInstanceObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pInstanceObj->metaData);
	free(pInstanceObj->typeDefinition);
	free(pInstanceObj->dictionary);
	hashmap_free(pInstanceObj->fragmentDictionary);
	free(pInstanceObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_Instance(Instance* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	free(this->metaData);
	free(this->typeDefinition);
	free(this->dictionary);
	hashmap_free(this->fragmentDictionary);
	free(this);
	
}

void Instance_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s\\cClass", parent);
	visitor->action(path, STRING, ((Instance*)this)->MetaClassName((Instance*)this));*/

	/* NamedElement attributes */
	NamedElement_VisitAttributes(((Instance*)(this))->super, parent, visitor, recursive);
	
	/* Local attributes */
	if(recursive)
	{
		/*sprintf(path,"%s\\metaData", parent);*/
		sprintf(path,"metaData");
		visitor->action(path, STRING, ((Instance*)(this))->metaData);
		visitor->action(NULL, COLON, NULL);

		/*sprintf(path,"%s\\started", parent);*/
		sprintf(path,"started", parent);
		visitor->action(path, BOOL, (void*)((Instance*)(this))->started);
		visitor->action(NULL, COLON, NULL);
	}
}

void Instance_VisitReferences(void* const this, char* parent, Visitor* visitor, int recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
		if(((Instance*)(this))->typeDefinition != NULL)
		{
			visitor->action("typeDefinition", SQBRACKET, NULL);
			/*sprintf(path, "%s/typeDefinition[%s]", parent, ((Instance*)(this))->typeDefinition->InternalGetKey(((Instance*)(this))->typeDefinition));*/
			((Instance*)(this))->typeDefinition->VisitAttributes(((Instance*)(this))->typeDefinition, path, visitor, recursive);
			((Instance*)(this))->typeDefinition->VisitReferences(((Instance*)(this))->typeDefinition, path, visitor);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}
		else
		{
			visitor->action("typeDefinition", SQBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}

		if(((Instance*)(this))->dictionary != NULL)
		{
			visitor->action("dictionary", SQBRACKET, NULL);
			visitor->action(NULL, BRACKET, NULL);
			/*sprintf(path, "%s/dictionary[%s]", parent, ((Instance*)(this))->dictionary->InternalGetKey(((Instance*)(this))->dictionary));*/
			((Instance*)(this))->dictionary->VisitAttributes(((Instance*)(this))->dictionary, path, visitor);
			((Instance*)(this))->dictionary->VisitReferences(((Instance*)(this))->dictionary, path, visitor);
			visitor->action(NULL, CLOSEBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}
		else
		{
			visitor->action("dictionary", SQBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}

		hashmap_map* m = NULL;
		int i;

		if((m = (hashmap_map*) ((Instance*)(this))->fragmentDictionary) != NULL)
		{
			int length = hashmap_length(((Instance*)(this))->fragmentDictionary);

			visitor->action("fragmentDictionary", SQBRACKET, NULL);
			/* compare fragmentDictionary*/
			for(i = 0; i< m->table_size; i++)
			{
				if(m->data[i].in_use != 0)
				{
					visitor->action(NULL, BRACKET, NULL);
					any_t data = (any_t) (m->data[i].data);
					FragmentDictionary* n = data;
					/*sprintf(path, "%s/fragmentDictionary[%s]", parent, n->InternalGetKey(n));*/
					n->VisitAttributes(n, path, visitor);
					n->VisitReferences(n, path, visitor);
					if(length > 1)
					{
						visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
						length--;
					}
					else
						visitor->action(NULL, CLOSEBRACKET, NULL);
				}
			}
			visitor->action(NULL, CLOSESQBRACKET, NULL);
		}
		else
		{
			visitor->action("fragmentDictionary", SQBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKET, NULL);
		}
	}
	else
	{
		if(((Instance*)(this))->typeDefinition != NULL)
		{
			visitor->action("typeDefinition", SQBRACKET, NULL);
			/*sprintf(path, "%s/typeDefinition[%s]", parent, ((Instance*)(this))->typeDefinition->InternalGetKey(((Instance*)(this))->typeDefinition));
			((Instance*)(this))->typeDefinition->VisitAttributes(((Instance*)(this))->typeDefinition, path, visitor, recursive);*/
			sprintf(path, "typeDefinition[%s]", ((Instance*)(this))->typeDefinition->InternalGetKey(((Instance*)(this))->typeDefinition));
			visitor->action(path, STRREF, NULL);
			visitor->action(NULL, RETURN, NULL);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}
		else
		{
			visitor->action("typeDefinition", SQBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}

		if(((Instance*)(this))->dictionary != NULL)
		{
			visitor->action("dictionary", SQBRACKET, NULL);
			visitor->action(NULL, BRACKET, NULL);
			/*sprintf(path, "%s/dictionary[%s]", parent, ((Instance*)(this))->dictionary->InternalGetKey(((Instance*)(this))->dictionary));*/
			((Instance*)(this))->dictionary->VisitAttributes(((Instance*)(this))->dictionary, path, visitor);
			((Instance*)(this))->dictionary->VisitReferences(((Instance*)(this))->dictionary, path, visitor);
			visitor->action(NULL, CLOSEBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}
		else
		{
			visitor->action("dictionary", SQBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}

		hashmap_map* m = NULL;
		int i;

		if((m = (hashmap_map*) ((Instance*)(this))->fragmentDictionary) != NULL)
		{
			int length = hashmap_length(((Instance*)(this))->fragmentDictionary);

			visitor->action("fragmentDictionary", SQBRACKET, NULL);
			/* compare fragmentDictionary*/
			for(i = 0; i< m->table_size; i++)
			{
				if(m->data[i].in_use != 0)
				{
					visitor->action(NULL, BRACKET, NULL);
					any_t data = (any_t) (m->data[i].data);
					FragmentDictionary* n = data;
					/*sprintf(path, "%s/fragmentDictionary[%s]", parent, n->InternalGetKey(n));*/
					n->VisitAttributes(n, path, visitor);
					n->VisitReferences(n, path, visitor);
					if(length > 1)
					{
						visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
						length--;
					}
					else
						visitor->action(NULL, CLOSEBRACKET, NULL);
				}
			}
			visitor->action(NULL, CLOSESQBRACKET, NULL);
		}
		else
		{
			visitor->action("fragmentDictionary", SQBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKET, NULL);
		}
	}
}

void* Instance_FindByPath(char* attribute, Instance* const this)
{
	/* NamedElement attributes */
	if(!strcmp("name", attribute))
	{
		return this->super->FindByPath(attribute, this->super);
	}
	/* Local attributes */
	else if(!strcmp("metaData",attribute))
	{
		return this->metaData;
	}
	else if(!strcmp("started",attribute))
	{
		return this->started;
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
			/*printf("pch: %s\n", pch);*/
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
		
		if(!strcmp("typeDefinition", relationName))
		{
			/*printf("relationName: %s\n", relationName);*/
			if(nextAttribute == NULL)
			{
				return this->typeDefinition;
			}
			else
			{
				return this->typeDefinition->FindByPath(nextAttribute, this->typeDefinition);
			}
		}
		else if(!strcmp("dictionary", relationName))
		{
			/*printf("relationName: %s\n", relationName);*/
			if(nextAttribute == NULL)
			{
				return this->dictionary;
			}
			else
			{
				return this->dictionary->FindByPath(nextAttribute, this->dictionary);
			}
		}
		else if(!strcmp("fragmentDictionary", relationName))
		{
			/*printf("relationName: %s\n", relationName);*/
			if(nextAttribute == NULL)
			{
				return this->fragmentDictionary;
			}
			else
			{
				FragmentDictionary* value = this->FindFragmentDictionaryByID(this, queryID);
				if(value != NULL)
					return value->FindByPath(nextAttribute, value);
				else
					return NULL;
			}
		}
		else
		{
			/*printf("relationName: %s\n", relationName);*/
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
