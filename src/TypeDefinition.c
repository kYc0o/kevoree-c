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
	pTypeDefObj->internalKey = NULL;

	pTypeDefObj->AddDeployUnit = TypeDefinition_AddDeployUnit;
	pTypeDefObj->AddDictionaryType = TypeDefinition_AddDictionaryType;
	pTypeDefObj->AddSuperTypes = TypeDefinition_AddSuperTypes;
	pTypeDefObj->RemoveDeployUnit = TypeDefinition_RemoveDeployUnit;
	pTypeDefObj->RemoveDictionaryType = TypeDefinition_RemoveDictionaryType;
	pTypeDefObj->RemoveSuperTypes = TypeDefinition_RemoveSuperTypes;
	pTypeDefObj->FindByPath = TypeDefinition_FindByPath;

	pObj->metaClassName = TypeDefinition_metaClassName;
	pObj->internalGetKey = TypeDefinition_internalGetKey;
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
	pTypeDefObj->eContainer = NULL;
	pTypeDefObj->path = NULL;

	pTypeDefObj->version = NULL;
	pTypeDefObj->factoryBean = NULL;
	pTypeDefObj->bean = NULL;
	pTypeDefObj->abstract = -1;

	pTypeDefObj->deployUnits = NULL;
	pTypeDefObj->dictionaryType = NULL;
	pTypeDefObj->superTypes = NULL;
	pTypeDefObj->eContainer = NULL;
	pTypeDefObj->internalKey = NULL;

	pTypeDefObj->AddDeployUnit = TypeDefinition_AddDeployUnit;
	pTypeDefObj->AddDictionaryType = TypeDefinition_AddDictionaryType;
	pTypeDefObj->AddSuperTypes = TypeDefinition_AddSuperTypes;
	pTypeDefObj->RemoveDeployUnit = TypeDefinition_RemoveDeployUnit;
	pTypeDefObj->RemoveDictionaryType = TypeDefinition_RemoveDictionaryType;
	pTypeDefObj->RemoveSuperTypes = TypeDefinition_RemoveSuperTypes;
	pTypeDefObj->metaClassName = TypeDefinition_metaClassName;
	pObj->metaClassName = pTypeDefObj->metaClassName;
	pTypeDefObj->internalGetKey = TypeDefinition_internalGetKey;
	pTypeDefObj->Delete = delete_TypeDefinition;
	pTypeDefObj->VisitAttributes = TypeDefinition_VisitAttributes;
	pTypeDefObj->VisitPathAttributes = TypeDefinition_VisitPathAttributes;
	pTypeDefObj->VisitReferences = TypeDefinition_VisitReferences;
	pTypeDefObj->VisitPathReferences = TypeDefinition_VisitPathReferences;
	pTypeDefObj->FindByPath = TypeDefinition_FindByPath;

	return pTypeDefObj;
}

char* TypeDefinition_internalGetKey(void * const this)
{
	TypeDefinition *pObj = (TypeDefinition*)this;
	char* internalKey = NULL;

	if (this == NULL)
		return NULL;

	if (pObj->internalKey == NULL) {
		internalKey = malloc(sizeof(char) * (strlen(pObj->super->name) + strlen("/") + strlen(pObj->version)) + 1);

		if (internalKey == NULL)
			return NULL;

		sprintf(internalKey, "%s/%s", pObj->super->name, pObj->version);

		pObj->internalKey = internalKey;
		return internalKey;
	} else {
		return pObj->internalKey;
	}
}

char* TypeDefinition_metaClassName(void * const this)
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
		/*if (ptr->refs == NULL) {
			if((ptr->refs = hashmap_new()) == MAP_OK) {
				PRINTF("INFO: deployUnit refs created!\n");
			} else {
				PRINTF("ERROR: deployUnit refs cannot be created!\n");
			}
		}
		if (ptr->refs != NULL) {
			char *value = malloc(sizeof(char) * (strlen("typeDefinitions[]") + strlen(this->internalGetKey(this))) + 1);
			sprintf(value, "typeDefinitions[%s]", this->internalGetKey(this));
			if ((hashmap_put(ptr->refs, this->path, (void**)&value)) == MAP_OK) {
				PRINTF("INFO: deployUnit reference added!\n");
			} else {
				PRINTF("ERROR: deployUnit reference cannot be added\n");
			}
		}*/
	}
}

void TypeDefinition_AddDictionaryType(TypeDefinition* const this, DictionaryType *ptr)
{
	if(ptr != NULL)
	{
		this->dictionaryType = ptr;
		ptr->eContainer = malloc(sizeof(char) * (strlen(this->path)) + 1);
		strcpy(ptr->eContainer, this->path);
		ptr->path = malloc(sizeof(char) * (strlen(this->path) + strlen("/dictionaryType[]") + strlen(ptr->internalGetKey(ptr))) + 1);
		sprintf(ptr->path, "%s/dictionaryType[%s]", this->path, ptr->internalGetKey(ptr));
	}
}

void TypeDefinition_RemoveDeployUnit(TypeDefinition* const this, DeployUnit* ptr)
{
	this->deployUnits = NULL;
	/*if ((hashmap_remove(ptr->refs, this->path)) == MAP_OK) {
		PRINTF("INFO: deployUnit reference removed!\n");
	} else {
		PRINTF("INFO: cannot remove deployUnit reference\n");
	}*/
}

void TypeDefinition_RemoveDictionaryType(TypeDefinition* const this, DictionaryType *ptr)
{
	this->dictionaryType = NULL;
	free(ptr->eContainer);
	ptr->eContainer = NULL;
	free(ptr->path);
	ptr->path = NULL;
}

void TypeDefinition_AddSuperTypes(TypeDefinition* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

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
			if ((hashmap_put(this->superTypes, internalKey, ptr)) == MAP_OK) {
				/*if (ptr->refs == NULL) {
					if((ptr->refs = hashmap_new()) == MAP_OK) {
						PRINTF("INFO: superType refs created!\n");
					} else {
						PRINTF("ERROR: superType refs cannot be created!\n");
					}
				}
				if (ptr->refs != NULL) {
					char *value = malloc(sizeof(char) * (strlen("typeDefinitions[]") + strlen(this->internalGetKey(this))) + 1);
					sprintf(value, "typeDefinitions[%s]", this->internalGetKey(this));
					if ((hashmap_put(ptr->refs, this->path, (void**)&value)) == MAP_OK) {
						PRINTF("INFO: superType reference added!\n");
					} else {
						PRINTF("ERROR: superType reference cannot be added\n");
					}
				}*/
				PRINTF("DEBUG: superType successfully added!\n");
			} else {
				PRINTF("ERROR: superType can't be added!\n");
			}
		}
	}
}

void TypeDefinition_RemoveSuperTypes(TypeDefinition* const this, TypeDefinition* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The TypeDefinition cannot be removed in TypeDefinition because the key is not defined\n");
	}
	else
	{
		if ((hashmap_remove(this->superTypes, internalKey)) == MAP_OK) {
			/*if ((hashmap_remove(ptr->refs, this->path)) == MAP_OK) {
				PRINTF("INFO: superType reference removed!\n");
			} else {
				PRINTF("INFO: cannot remove superType reference\n");
			}*/
			PRINTF("DEBUG: superType successfully removed!\n");
		} else {
			PRINTF("ERROR: superType can't be removed!\n");
		}
	}
}

void deletePoly_TypeDefinition(void * const this)
{
	if(this != NULL)
	{
		NamedElement *pObj = (NamedElement*)this;
		TypeDefinition* pTypeDefObj;
		pTypeDefObj = pObj->pDerivedObj;
		/*destroy derived obj*/
		free(pTypeDefObj->version);
		hashmap_free(pTypeDefObj->superTypes);
		free(pTypeDefObj->eContainer);
		free(pTypeDefObj);
		/*destroy base Obj*/
		delete_NamedElement(pObj);
	}
}

void delete_TypeDefinition(void * const this)
{
	if(this != NULL)
	{
		TypeDefinition *pObj = (TypeDefinition*)this;
		/* destroy base object */
		delete_NamedElement(pObj->super);
		/* destroy data memebers */
		free(pObj->version);
		hashmap_free(pObj->superTypes);
		free(pObj->eContainer);
		free(pObj);
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
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
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
		/*
		NamedElement_VisitPathAttributes(((TypeDefinition*)(this))->super, parent, visitor, recursive);
		*/
		sprintf(path, "%s\\typeDefinition", parent);
		visitor->action(path, BOOL, (void*)((TypeDefinition*)(this))->abstract);
	}
}

void TypeDefinition_VisitReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypeDefinition*)(this))->deployUnits != NULL)
	{
		visitor->action("deployUnit", SQBRACKET, NULL);
		sprintf(path, "deployUnits[%s]", ((TypeDefinition*)(this))->deployUnits->internalGetKey(((TypeDefinition*)(this))->deployUnits));
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
		sprintf(path, "dictionaryType[%s]", ((TypeDefinition*)(this))->dictionaryType->internalGetKey(((TypeDefinition*)(this))->dictionaryType));
		DictionaryType* n = ((TypeDefinition*)(this))->dictionaryType;
		visitor->action(NULL, BRACKET, NULL);
		n->VisitAttributes(n, path, visitor, recursive);
		n->VisitReferences(n, path, visitor, recursive);
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
				sprintf(path,"superTypes[%s]", n->internalGetKey(n));
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

void TypeDefinition_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypeDefinition*)(this))->deployUnits != NULL)
	{
		sprintf(path, "%s/%s\\deployUnit", parent, ((TypeDefinition*)(this))->deployUnits->path);
		/*DeployUnit* n = ((TypeDefinition*)(this))->deployUnits;
		n->VisitPathAttributes(n, path, visitor, false);*/
		visitor->action(path, REFERENCE, parent);
	}

	if(((TypeDefinition*)(this))->dictionaryType != NULL)
	{
		DictionaryType* n = ((TypeDefinition*)(this))->dictionaryType;
		sprintf(path, "%s/dictionaryType[%s]", parent, ((TypeDefinition*)(this))->dictionaryType->internalGetKey(((TypeDefinition*)(this))->dictionaryType));
		if (visitor->secondAction != NULL) {
			if (visitor->secondAction(path, "dictionaryType")) {
				n->VisitPathAttributes(n, path, visitor, recursive);
				n->VisitPathReferences(n, path, visitor, recursive);
			}
		} else {
			n->VisitPathAttributes(n, path, visitor, recursive);
			n->VisitPathReferences(n, path, visitor, recursive);
		}
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
				sprintf(path,"%s/superTypes[%s]", parent, n->internalGetKey(n));
				if (visitor->secondAction != NULL) {
					if (visitor->secondAction(path, "dictionaryType")) {
						n->VisitPathAttributes(n, path, visitor, false);
					}
				} else {
					n->VisitPathAttributes(n, path, visitor, false);
				}
			}
		}
	}
}

void* TypeDefinition_FindByPath(char* attribute, void * const this)
{
	/*
	 * TODO fix polymorphism
	 */
	TypeDefinition *pObj = (TypeDefinition*)this;
	/* NamedElement attributes */
	if(!strcmp("name",attribute))
	{
		return pObj->super->FindByPath(attribute, pObj->super);
	}
	/* Local attributes */
	else if(!strcmp("version",attribute))
	{
		return pObj->version;
	}
	else if(!strcmp("factoryBean",attribute))
	{
		return pObj->factoryBean;
	}
	else if(!strcmp("bean",attribute))
	{
		return pObj->bean;
	}
	else if(!strcmp("abstract",attribute))
	{
		return (void*)pObj->abstract;
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

		if(!strcmp("deployUnits", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->deployUnits;
			}
			else
			{
				return pObj->deployUnits->FindByPath(nextPath, pObj->deployUnits);
			}
		}
		else if(!strcmp("dictionaryType", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->dictionaryType;
			}
			else
			{
				DictionaryType *dictype = pObj->dictionaryType;
				return dictype->FindByPath(nextPath, dictype);
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
