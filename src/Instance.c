#include <stdlib.h>
#include "NamedElement.h"
#include "TypeDefinition.h"
#include "Dictionary.h"
#include "FragmentDictionary.h"
#include "Visitor.h"
#include "Instance.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

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

	pInstanceObj->path = NULL;
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

	pObj->metaClassName = Instance_metaClassName;
	pObj->internalGetKey = Instance_internalGetKey;
	pObj->Delete = deletePoly_Instance;
	pObj->VisitAttributes = Instance_VisitAttributes;
	pObj->VisitPathAttributes = Instance_VisitPathAttributes;
	pObj->VisitReferences = Instance_VisitReferences;
	pObj->VisitPathReferences = Instance_VisitPathReferences;
	pObj->FindByPath = Instance_FindByPath;

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

	pInstanceObj->path = NULL;
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

	pInstanceObj->metaClassName = Instance_metaClassName;
	pObj->metaClassName = pInstanceObj->metaClassName;
	pInstanceObj->internalGetKey = Instance_internalGetKey;
	pInstanceObj->Delete = delete_Instance;
	pInstanceObj->VisitAttributes = Instance_VisitAttributes;
	pInstanceObj->VisitPathAttributes = Instance_VisitPathAttributes;
	pInstanceObj->VisitReferences = Instance_VisitReferences;
	pInstanceObj->VisitPathReferences = Instance_VisitPathReferences;
	pInstanceObj->FindByPath = Instance_FindByPath;

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
	ptr->eContainer = malloc(sizeof(char) * (strlen(this->path)) + 1);
	strcpy(ptr->eContainer, this->path);
	ptr->path = malloc(sizeof(char) * (strlen(this->path) + strlen("/dictionary[]") + strlen(ptr->internalGetKey(ptr))) + 1);
	sprintf(ptr->path, "%s/dictionary[%s]", this->path, ptr->internalGetKey(ptr));
}

void Instance_AddFragmentDictionary(Instance* const this, FragmentDictionary* ptr)
{
	FragmentDictionary* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The FragmentDictionary cannot be added in Instance because the key is not defined\n");
	}
	else
	{
		if(this->fragmentDictionary == NULL)
		{
			this->fragmentDictionary = hashmap_new();
		}
		if(hashmap_get(this->fragmentDictionary, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (FragmentDictionary*)ptr;*/
			if(hashmap_put(this->fragmentDictionary, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->path)) + 1);
				strcpy(ptr->eContainer, this->path);
				ptr->super->eContainer = ptr->eContainer;
				ptr->path = malloc(sizeof(char) * (strlen(this->path) + strlen("/fragmentDictionary[]") + strlen(internalKey)) + 1);
				sprintf(ptr->path, "%s/fragmentDictionary[%s]", this->path, internalKey);
				ptr->super->path = ptr->path;
			}
		}
	}
}

void Instance_RemoveTypeDefinition(Instance* const this, TypeDefinition* ptr)
{
	this->typeDefinition = NULL;
}

void Instance_RemoveDictionary(Instance* const this, Dictionary* ptr)
{
	free(ptr->eContainer);
	ptr->eContainer = NULL;
	this->dictionary = NULL;
}

void Instance_RemoveFragmentDictionary(Instance* const this, FragmentDictionary* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The FragmentDictionary cannot be removed in Instance because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->fragmentDictionary, internalKey);
	}
}

char* Instance_internalGetKey(void* const this)
{
	Instance *pObj = (Instance*)this;
	return pObj->super->internalGetKey(pObj->super);
}

char* Instance_metaClassName(void* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("Instance")) + 1);
	if(name != NULL)
		strcpy(name, "Instance");
	else
		return NULL;

	return name;
}

void deletePoly_Instance(void * const this)
{
	NamedElement *pObj = (NamedElement*)this;
	Instance* pInstanceObj;
	pInstanceObj = pObj->pDerivedObj;
	/*destroy derived obj*/
	free(pInstanceObj->metaData);
	/*
	free(pInstanceObj->typeDefinition);
	free(pInstanceObj->dictionary);
	*/
	/*
	 * TODO verify NULLity
	 */
	hashmap_free(pInstanceObj->fragmentDictionary);
	free(pInstanceObj);
	/*destroy base Obj*/
	delete_NamedElement(pObj);
}

void delete_Instance(void * const this)
{
	Instance *pObj = (Instance*)this;
	/* destroy base object */
	delete_NamedElement(pObj->super);
	/* destroy data memebers */
	free(pObj->metaData);
	/*
	free(this->typeDefinition);
	free(this->dictionary);
	*/
	/*
	 * TODO verify NULLity
	 */
	hashmap_free(pObj->fragmentDictionary);
	free(pObj);

}

void Instance_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* NamedElement attributes */
	NamedElement_VisitAttributes(((Instance*)(this))->super, parent, visitor, recursive);

	/* Local attributes */
	if(recursive)
	{
		sprintf(path,"metaData");
		visitor->action(path, STRING, ((Instance*)(this))->metaData);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "started");
		visitor->action(path, BOOL, (void*)((Instance*)(this))->started);
		visitor->action(NULL, COLON, NULL);
	}
}

void Instance_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/* NamedElement attributes */
	NamedElement_VisitPathAttributes(((Instance*)(this))->super, parent, visitor, recursive);

	/* Local attributes */
	if(recursive)
	{
		sprintf(path,"%s\\metaData", parent);
		visitor->action(path, STRING, ((Instance*)(this))->metaData);

		sprintf(path,"%s\\started", parent);
		visitor->action(path, BOOL, (void*)((Instance*)(this))->started);
	}
}

void Instance_VisitReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
		if(((Instance*)(this))->typeDefinition != NULL)
		{
			visitor->action("typeDefinition", SQBRACKET, NULL);
			((Instance*)(this))->typeDefinition->VisitAttributes(((Instance*)(this))->typeDefinition, path, visitor, recursive);
			((Instance*)(this))->typeDefinition->VisitReferences(((Instance*)(this))->typeDefinition, path, visitor, recursive);
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
			((Instance*)(this))->dictionary->VisitAttributes(((Instance*)(this))->dictionary, path, visitor, recursive);
			((Instance*)(this))->dictionary->VisitReferences(((Instance*)(this))->dictionary, path, visitor, recursive);
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
					n->VisitAttributes(n, path, visitor, recursive);
					n->VisitReferences(n, path, visitor, recursive);
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
			sprintf(path, "typeDefinitions[%s]", ((Instance*)(this))->typeDefinition->internalGetKey(((Instance*)(this))->typeDefinition));
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
			((Instance*)(this))->dictionary->VisitAttributes(((Instance*)(this))->dictionary, path, visitor, recursive);
			((Instance*)(this))->dictionary->VisitReferences(((Instance*)(this))->dictionary, path, visitor, recursive);
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
					n->VisitAttributes(n, path, visitor, recursive);
					n->VisitReferences(n, path, visitor, recursive);
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

void Instance_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
		if(((Instance*)(this))->typeDefinition != NULL)
		{
			sprintf(path, "%s/typeDefinition[%s]", parent, ((Instance*)(this))->typeDefinition->internalGetKey(((Instance*)(this))->typeDefinition));
			if (visitor->secondAction != NULL) {
				if (visitor->secondAction(path, "typeDefinition")) {
					((Instance*)(this))->typeDefinition->VisitPathAttributes(((Instance*)(this))->typeDefinition, path, visitor, recursive);
					((Instance*)(this))->typeDefinition->VisitPathReferences(((Instance*)(this))->typeDefinition, path, visitor, recursive);
				}
			} else {
				((Instance*)(this))->typeDefinition->VisitPathAttributes(((Instance*)(this))->typeDefinition, path, visitor, recursive);
				((Instance*)(this))->typeDefinition->VisitPathReferences(((Instance*)(this))->typeDefinition, path, visitor, recursive);
			}
		}
		if(((Instance*)(this))->dictionary != NULL)
		{
			sprintf(path, "%s/dictionary[%s]", parent, ((Instance*)(this))->dictionary->internalGetKey(((Instance*)(this))->dictionary));
			if (visitor->secondAction != NULL) {
				if (visitor->secondAction(path, "dictionary")) {
					((Instance*)(this))->dictionary->VisitPathAttributes(((Instance*)(this))->dictionary, path, visitor, recursive);
					((Instance*)(this))->dictionary->VisitPathReferences(((Instance*)(this))->dictionary, path, visitor, recursive);
				} else {
					((Instance*)(this))->dictionary->VisitPathAttributes(((Instance*)(this))->dictionary, path, visitor, recursive);
					((Instance*)(this))->dictionary->VisitPathReferences(((Instance*)(this))->dictionary, path, visitor, recursive);
				}
			}
		}

		hashmap_map* m = NULL;
		int i;

		if((m = (hashmap_map*) ((Instance*)(this))->fragmentDictionary) != NULL)
		{
			PRINTF("Looking for fragmentDictionary\n");
			/* compare fragmentDictionary*/
			for(i = 0; i< m->table_size; i++)
			{
				if(m->data[i].in_use != 0)
				{
					any_t data = (any_t) (m->data[i].data);
					FragmentDictionary* n = data;
					sprintf(path, "%s/fragmentDictionary[%s]", parent, n->internalGetKey(n));
					if (visitor->secondAction != NULL) {
						if (visitor->secondAction(path, "fragmentDictionary")) {
							n->VisitPathAttributes(n, path, visitor, recursive);
							n->VisitPathReferences(n, path, visitor, recursive);
						}
					} else {
						n->VisitPathAttributes(n, path, visitor, recursive);
						n->VisitPathReferences(n, path, visitor, recursive);
					}
				}
			}
		}
	}
	else
	{
		if(((Instance*)(this))->typeDefinition != NULL)
		{
			sprintf(path, "%s/%s\\typeDefinition", parent, ((Instance*)(this))->typeDefinition->path);
			/*((Instance*)(this))->typeDefinition->VisitPathAttributes(((Instance*)(this))->typeDefinition, path, visitor, recursive);*/
			visitor->action(path, REFERENCE, parent);
		}
		if(((Instance*)(this))->dictionary != NULL)
		{
			sprintf(path, "%s/dictionary[%s]", parent, ((Instance*)(this))->dictionary->internalGetKey(((Instance*)(this))->dictionary));
			if (visitor->secondAction != NULL) {
				if (visitor->secondAction(path, "dictionary")) {
					((Instance*)(this))->dictionary->VisitPathAttributes(((Instance*)(this))->dictionary, path, visitor, true);
					((Instance*)(this))->dictionary->VisitPathReferences(((Instance*)(this))->dictionary, path, visitor, true);
				} else {
					((Instance*)(this))->dictionary->VisitPathAttributes(((Instance*)(this))->dictionary, path, visitor, true);
					((Instance*)(this))->dictionary->VisitPathReferences(((Instance*)(this))->dictionary, path, visitor, true);
				}
			}
		}

		hashmap_map* m = NULL;
		int i;

		if((m = (hashmap_map*) ((Instance*)(this))->fragmentDictionary) != NULL)
		{
			/* compare fragmentDictionary*/
			for(i = 0; i< m->table_size; i++)
			{
				if(m->data[i].in_use != 0)
				{
					any_t data = (any_t) (m->data[i].data);
					FragmentDictionary* n = data;
					sprintf(path, "%s/fragmentDictionary[%s]", parent, n->internalGetKey(n));
					if (visitor->secondAction != NULL) {
						if (visitor->secondAction(path, "fragmentDictionary")) {
							n->VisitPathAttributes(n, path, visitor, true);
							n->VisitPathReferences(n, path, visitor, true);
						}
					} else {
						n->VisitPathAttributes(n, path, visitor, true);
						n->VisitPathReferences(n, path, visitor, true);
					}
				}
			}
		}
	}
}

void* Instance_FindByPath(char* attribute, void* const this)
{
	Instance *pObj = (Instance*)this;
	/* NamedElement attributes */
	if(!strcmp("name", attribute))
	{
		return pObj->super->FindByPath(attribute, pObj->super);
	}
	/* Local attributes */
	else if(!strcmp("metaData",attribute))
	{
		return pObj->metaData;
	}
	else if(!strcmp("started",attribute))
	{
		return (void*)pObj->started;
	}
	/* Local references */
	else
	{
		char path[250];
		memset(&path[0], 0, sizeof(path));
		char token[100];
		memset(&token[0], 0, sizeof(token));
		char *obj = NULL;
		char key[50];
		memset(&key[0], 0, sizeof(key));
		char nextPath[150];
		memset(&nextPath[0], 0, sizeof(nextPath));
		char *nextAttribute = NULL;

		strcpy(path, attribute);

		if(strchr(path, '[') != NULL)
		{
			obj = strdup(strtok(path, "["));
			strcpy(path, attribute);
			PRINTF("Object: %s\n", obj);
			strcpy(token, strtok(path, "]"));
			strcpy(path, attribute);
			sprintf(token, "%s]", token);
			PRINTF("Token: %s\n", token);
			sscanf(token, "%*[^[][%[^]]", key);
			PRINTF("Key: %s\n", key);

			if((strchr(path, '\\')) != NULL)
			{
				nextAttribute = strtok(NULL, "\\");
				PRINTF("Attribute: %s\n", nextAttribute);

				if(strchr(nextAttribute, '['))
				{
					sprintf(nextPath, "%s\\%s", ++nextAttribute, strtok(NULL, "\\"));
					PRINTF("Next Path: %s\n", nextPath);
				}
				else
				{
					strcpy(nextPath, nextAttribute);
					PRINTF("Next Path: %s\n", nextPath);
				}
			}
			else
			{
				nextAttribute = strtok(path, "]");
				bool isFirst = true;
				char *fragPath = NULL;
				while ((fragPath = strtok(NULL, "]")) != NULL) {
					PRINTF("Attribute: %s]\n", fragPath);
					if (isFirst) {
						sprintf(nextPath, "%s]", ++fragPath);
						isFirst = false;
					} else {
						sprintf(nextPath, "%s/%s]", nextPath, ++fragPath);
					}
					PRINTF("Next Path: %s\n", nextPath);
				}
				if (strlen(nextPath) == 0) {
					PRINTF("Attribute: NULL\n");
					PRINTF("Next Path: NULL\n");
					nextAttribute = NULL;
				}
			}
		}
		else
		{
			if ((nextAttribute = strtok(path, "\\")) != NULL) {
				if ((nextAttribute = strtok(NULL, "\\")) != NULL) {
					PRINTF("Attribute: %s\n", nextAttribute);
				} else {
					nextAttribute = strtok(path, "\\");
					PRINTF("Attribute: %s\n", nextAttribute);
				}
			}
		}

		if(!strcmp("typeDefinitions", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->typeDefinition;
			}
			else
			{
				return pObj->typeDefinition->FindByPath(nextPath, pObj->typeDefinition);
			}
		}
		else if(!strcmp("dictionary", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->dictionary;
			}
			else
			{
				return pObj->dictionary->FindByPath(nextPath, pObj->dictionary);
			}
		}
		else if(!strcmp("fragmentDictionary", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->FindFragmentDictionaryByID(pObj, key);
			}
			else
			{
				FragmentDictionary* value = pObj->FindFragmentDictionaryByID(pObj, key);
				if(value != NULL)
					return value->FindByPath(nextPath, value);
				else
					return NULL;
			}
		}
		else
		{
			free(obj);
			PRINTF("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
