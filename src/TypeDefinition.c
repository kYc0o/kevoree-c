#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NamedElement.h"
#include "DeployUnit.h"
#include "DictionaryType.h"
#include "Visitor.h"
#include "TypeDefinition.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

NamedElement* newPoly_TypeDefinition()
{
	TypeDefinition* pTypeDefObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeDefObj = (TypeDefinition*)malloc(sizeof(TypeDefinition));

	if (pTypeDefObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pTypeDefObj; /* Pointing to derived object */

	pTypeDefObj->version = NULL;
	pTypeDefObj->factoryBean = NULL;
	pTypeDefObj->bean = NULL;
	pTypeDefObj->abstract = -1;

	pTypeDefObj->deployUnits = NULL;
	pTypeDefObj->dictionaryType = NULL;
	pTypeDefObj->superTypes = NULL;
	pTypeDefObj->eContainer = NULL;

	pTypeDefObj->AddDeployUnit = TypeDefinition_AddDeployUnit;
	pTypeDefObj->AddDictionaryType = TypeDefinition_AddDictionaryType;
	pTypeDefObj->AddSuperTypes = TypeDefinition_AddSuperTypes;
	pTypeDefObj->RemoveDeployUnit = TypeDefinition_RemoveDeployUnit;
	pTypeDefObj->RemoveDictionaryType = TypeDefinition_RemoveDictionaryType;
	pTypeDefObj->RemoveSuperTypes = TypeDefinition_RemoveSuperTypes;
	pTypeDefObj->FindByPath = TypeDefinition_FindByPath;

	pObj->MetaClassName = TypeDefinition_MetaClassName;
	pObj->InternalGetKey = TypeDefinition_InternalGetKey;
	pObj->Delete = deletePoly_TypeDefinition;
	pObj->VisitAttributes = TypeDefinition_VisitAttributes;
	pObj->VisitPathAttributes = TypeDefinition_VisitPathAttributes;
	pObj->VisitReferences = TypeDefinition_VisitReferences;
	pObj->VisitPathReferences = TypeDefinition_VisitPathReferences;

	return pObj;
}

TypeDefinition* new_TypeDefinition()
{
	TypeDefinition* pTypeDefObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pTypeDefObj = (TypeDefinition*)malloc(sizeof(TypeDefinition));

	if (pTypeDefObj == NULL)
	{
		return NULL;
	}

	pTypeDefObj->super = pObj; /* Pointing to base object */

	pTypeDefObj->version = NULL;
	pTypeDefObj->factoryBean = NULL;
	pTypeDefObj->bean = NULL;
	pTypeDefObj->abstract = -1;

	pTypeDefObj->deployUnits = NULL;
	pTypeDefObj->dictionaryType = NULL;
	pTypeDefObj->superTypes = NULL;
	pTypeDefObj->eContainer = NULL;

	pTypeDefObj->AddDeployUnit = TypeDefinition_AddDeployUnit;
	pTypeDefObj->AddDictionaryType = TypeDefinition_AddDictionaryType;
	pTypeDefObj->AddSuperTypes = TypeDefinition_AddSuperTypes;
	pTypeDefObj->RemoveDeployUnit = TypeDefinition_RemoveDeployUnit;
	pTypeDefObj->RemoveDictionaryType = TypeDefinition_RemoveDictionaryType;
	pTypeDefObj->RemoveSuperTypes = TypeDefinition_RemoveSuperTypes;
	pTypeDefObj->MetaClassName = TypeDefinition_MetaClassName;
	pObj->MetaClassName = pTypeDefObj->MetaClassName;
	pTypeDefObj->InternalGetKey = TypeDefinition_InternalGetKey;
	pTypeDefObj->Delete = delete_TypeDefinition;
	pTypeDefObj->VisitAttributes = TypeDefinition_VisitAttributes;
	pTypeDefObj->VisitPathAttributes = TypeDefinition_VisitPathAttributes;
	pTypeDefObj->VisitReferences = TypeDefinition_VisitReferences;
	pTypeDefObj->VisitPathReferences = TypeDefinition_VisitPathReferences;
	pTypeDefObj->FindByPath = TypeDefinition_FindByPath;

	return pTypeDefObj;
}

char* TypeDefinition_InternalGetKey(TypeDefinition* const this)
{
	char* internalKey = NULL;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->name) + strlen("/") + strlen(this->version)) + 1);

	if (internalKey == NULL)
		return NULL;

	sprintf(internalKey, "%s/%s", this->super->name, this->version);

	return internalKey;
}

char* TypeDefinition_MetaClassName(TypeDefinition* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("TypeDefinition")) + 1);
	if(name != NULL)
		strcpy(name, "TypeDefinition");
	else
		return NULL;

	return name;
}

void TypeDefinition_AddDeployUnit(TypeDefinition* const this, DeployUnit* ptr)
{
	if(ptr != NULL)
	{
		this->deployUnits = ptr;
	}
}

void TypeDefinition_AddDictionaryType(TypeDefinition* const this, DictionaryType *ptr)
{
	if(ptr != NULL)
	{
		this->dictionaryType = ptr;
		/*ptr->eContainer = this;*/
	}
}

void TypeDefinition_RemoveDeployUnit(TypeDefinition* const this, DeployUnit* ptr)
{
	free(ptr);
	this->deployUnits = NULL;
}

void TypeDefinition_RemoveDictionaryType(TypeDefinition* const this, DictionaryType *ptr)
{
	ptr->eContainer = NULL;
	free(ptr);
	this->dictionaryType = NULL;
}

void TypeDefinition_AddSuperTypes(TypeDefinition* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = NULL;

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypeDefinition cannot be added in TypeDefinition because the key is not defined\n");
	}
	else
	{
		if(this->superTypes == NULL)
		{
			this->superTypes = hashmap_new();
		}
		if(hashmap_get(this->superTypes, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (TypeDefinition*)ptr;*/
			hashmap_put(this->superTypes, internalKey, ptr);
		}
	}
}

void TypeDefinition_RemoveSuperTypes(TypeDefinition* const this, TypeDefinition* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypeDefinition cannot be removed in TypeDefinition because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->superTypes, internalKey);
		free(internalKey);
	}
}

void deletePoly_TypeDefinition(NamedElement* const this)
{
	if(this != NULL)
	{
		TypeDefinition* pTypeDefObj;
		pTypeDefObj = this->pDerivedObj;
		/*destroy derived obj*/
		free(pTypeDefObj->version);
		free(pTypeDefObj->deployUnits);
		hashmap_free(pTypeDefObj->superTypes);
		free(pTypeDefObj->superTypes);
		free(pTypeDefObj->eContainer);
		free(pTypeDefObj);
		/*destroy base Obj*/
		delete_NamedElement(this);
	}
}

void delete_TypeDefinition(TypeDefinition* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_NamedElement(this->super);
		/* destroy data memebers */
		free(this->version);
		free(this->deployUnits);
		hashmap_free(this->superTypes);
		free(this->superTypes);
		free(this->eContainer);
		free(this);
	}

}

void TypeDefinition_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		NamedElement_VisitAttributes(((TypeDefinition*)(this))->super, parent, visitor, recursive);

		sprintf(path, "version");
		visitor->action(path, STRING, ((TypeDefinition*)(this))->version);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "factoryBean");
		visitor->action(path, STRING, ((TypeDefinition*)(this))->factoryBean);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "bean");
		visitor->action(path, STRING, ((TypeDefinition*)(this))->bean);
		visitor->action(NULL, COLON, NULL);

		sprintf(path, "abstract");
		visitor->action(path, BOOL, (void*)((TypeDefinition*)(this))->abstract);
		visitor->action(NULL, COLON, NULL);
	}
	else
	{
		NamedElement_VisitAttributes(((TypeDefinition*)(this))->super, parent, visitor, recursive);
	}
}

void TypeDefinition_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		NamedElement_VisitPathAttributes(((TypeDefinition*)(this))->super, parent, visitor, recursive);

		sprintf(path, "%s\\version", parent);
		visitor->action(path, STRING, ((TypeDefinition*)(this))->version);

		sprintf(path,"%s\\factoryBean",parent);
		visitor->action(path, STRING, ((TypeDefinition*)(this))->factoryBean);

		sprintf(path,"%s\\bean",parent);
		visitor->action(path, STRING, ((TypeDefinition*)(this))->bean);

		sprintf(path, "%s\\abstract", parent);
		visitor->action(path, BOOL, (void*)((TypeDefinition*)(this))->abstract);
	}
	else
	{
		NamedElement_VisitPathAttributes(((TypeDefinition*)(this))->super, parent, visitor, recursive);
	}
}

void TypeDefinition_VisitReferences(void *const this, char *parent, Visitor *visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypeDefinition*)(this))->deployUnits != NULL)
	{
		visitor->action("deployUnit", SQBRACKET, NULL);
		sprintf(path, "deployUnits[%s]", ((TypeDefinition*)(this))->deployUnits->InternalGetKey(((TypeDefinition*)(this))->deployUnits));
		visitor->action(path, STRREF, NULL);
		visitor->action(NULL, RETURN, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("deployUnit", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if(((TypeDefinition*)(this))->dictionaryType != NULL)
	{
		visitor->action("dictionaryType", SQBRACKET, NULL);
		sprintf(path, "dictionaryType[%s]", ((TypeDefinition*)(this))->dictionaryType->InternalGetKey(((TypeDefinition*)(this))->dictionaryType));
		DictionaryType* n = ((TypeDefinition*)(this))->dictionaryType;
		visitor->action(NULL, BRACKET, NULL);
		n->VisitAttributes(n, path, visitor);
		n->VisitReferences(n, path, visitor);
		visitor->action(NULL, CLOSEBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("dictionaryType", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if(((TypeDefinition*)(this))->superTypes != NULL)
	{
		visitor->action("superTypes", SQBRACKET, NULL);
		int i;

		/* superTypes */
		hashmap_map* m = ((TypeDefinition*)(this))->superTypes;

		/* compare superTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypeDefinition* n = data;
				sprintf(path,"superTypes[%s]", n->InternalGetKey(n));
				visitor->action(path, STRREF, NULL);
				visitor->action(NULL, COLON, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
	else
	{
		visitor->action("superTypes", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKET, NULL);
	}
}

void TypeDefinition_VisitPathReferences(void *const this, char *parent, Visitor *visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypeDefinition*)(this))->deployUnits != NULL)
	{
		sprintf(path, "%s/deployUnits[%s]", parent, ((TypeDefinition*)(this))->deployUnits->InternalGetKey(((TypeDefinition*)(this))->deployUnits));
		DeployUnit* n = ((TypeDefinition*)(this))->deployUnits;
		n->VisitPathAttributes(n, path, visitor, false);
	}

	if(((TypeDefinition*)(this))->dictionaryType != NULL)
	{
		sprintf(path, "%s/dictionaryType[%s]", parent, ((TypeDefinition*)(this))->dictionaryType->InternalGetKey(((TypeDefinition*)(this))->dictionaryType));
		DictionaryType* n = ((TypeDefinition*)(this))->dictionaryType;
		n->VisitPathAttributes(n, path, visitor);
		n->VisitPathReferences(n, path, visitor);
	}

	if(((TypeDefinition*)(this))->superTypes != NULL)
	{
		int i;

		/* superTypes */
		hashmap_map* m = ((TypeDefinition*)(this))->superTypes;

		/* compare superTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypeDefinition* n = data;
				sprintf(path,"%s/superTypes[%s]", parent, n->InternalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, false);
			}
		}
	}
}

void* TypeDefinition_FindByPath(char* attribute, TypeDefinition* const this)
{
	/* NamedElement attributes */
	if(!strcmp("name",attribute))
	{
		return this->super->FindByPath(attribute, this->super);
	}
	/* Local attributes */
	else if(!strcmp("version",attribute))
	{
		return this->version;
	}
	else if(!strcmp("factoryBean",attribute))
	{
		return this->factoryBean;
	}
	else if(!strcmp("bean",attribute))
	{
		return this->bean;
	}
	else if(!strcmp("abstract",attribute))
	{
		return (void*)this->abstract;
	}
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
				nextAttribute = strtok(NULL, "\\");
				strcpy(nextPath, ++nextAttribute);
				PRINTF("Next Path: %s\n", nextPath);
				nextAttribute = NULL;
			}
		}
		else
		{
			nextAttribute = strtok(path, "\\");
			nextAttribute = strtok(NULL, "\\");
			PRINTF("Attribute: %s\n", nextAttribute);
		}

		if(!strcmp("deployUnits", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return this->deployUnits;
			}
			else
			{
				return this->deployUnits->FindByPath(nextPath, this->deployUnits);
			}
		}
		else if(!strcmp("dictionaryType", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return this->dictionaryType;
			}
			else
			{
				return this->dictionaryType->FindByPath(nextPath, this->dictionaryType);
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
