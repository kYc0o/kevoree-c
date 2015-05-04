#include <string.h>
#include "PortTypeRef.h"
#include "NamedElement.h"
#include "TypeDefinition.h"
#include "Visitor.h"
#include "ComponentType.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

TypeDefinition* newPoly_ComponentType(void)
{
	ComponentType* pCompTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pCompTypeObj = (ComponentType*)malloc(sizeof(ComponentType));

	if (pCompTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pCompTypeObj; /* Pointing to derived object */
	pCompTypeObj->super = pObj;

	pCompTypeObj->eContainer = NULL;
	pCompTypeObj->path = NULL;
	pCompTypeObj->refs = NULL;
	pCompTypeObj->required = NULL;
	pCompTypeObj->provided = NULL;

	pCompTypeObj->FindRequiredByID = ComponentType_FindRequiredByID;
	pCompTypeObj->FindProvidedByID = ComponentType_FindProvidedByID;
	pCompTypeObj->AddRequired = ComponentType_AddRequired;
	pCompTypeObj->AddProvided = ComponentType_AddProvided;
	pCompTypeObj->RemoveRequired = ComponentType_RemoveRequired;
	pCompTypeObj->RemoveProvided = ComponentType_RemoveProvided;

	pCompTypeObj->metaClassName = ComponentType_metaClassName;
	pCompTypeObj->internalGetKey = ComponentType_internalGetKey;
	pCompTypeObj->VisitAttributes = ComponentType_VisitAttributes;
	pCompTypeObj->VisitPathAttributes = ComponentType_VisitPathAttributes;
	pCompTypeObj->VisitReferences = ComponentType_VisitReferences;
	pCompTypeObj->VisitPathReferences = ComponentType_VisitPathReferences;

	pObj->super->metaClassName = ComponentType_metaClassName;
	pObj->internalGetKey = ComponentType_internalGetKey;
	pObj->VisitAttributes = ComponentType_VisitAttributes;
	pObj->VisitReferences = ComponentType_VisitReferences;
	pObj->FindByPath = ComponentType_FindByPath;

	pObj->Delete = deletePoly_ComponentType;

	return pObj;
}

ComponentType* new_ComponentType(void)
{
	ComponentType* pCompTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();

	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pCompTypeObj = (ComponentType*)malloc(sizeof(ComponentType));

	if (pCompTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	/*pObj->pDerivedObj = pCompTypeObj;  Pointing to derived object */
	pObj->pDerivedObj = NULL;
	pCompTypeObj->super = pObj;

	pCompTypeObj->eContainer = NULL;
	pCompTypeObj->path = NULL;
	pCompTypeObj->refs = NULL;
	pCompTypeObj->required = NULL;
	pCompTypeObj->provided = NULL;

	pCompTypeObj->FindRequiredByID = ComponentType_FindRequiredByID;
	pCompTypeObj->FindProvidedByID = ComponentType_FindProvidedByID;
	pCompTypeObj->AddRequired = ComponentType_AddRequired;
	pCompTypeObj->AddProvided = ComponentType_AddProvided;
	pCompTypeObj->RemoveRequired = ComponentType_RemoveRequired;
	pCompTypeObj->RemoveProvided = ComponentType_RemoveProvided;

	pCompTypeObj->metaClassName = ComponentType_metaClassName;
	pCompTypeObj->internalGetKey = ComponentType_internalGetKey;
	pCompTypeObj->VisitAttributes = ComponentType_VisitAttributes;
	pCompTypeObj->VisitPathAttributes = ComponentType_VisitPathAttributes;
	pCompTypeObj->VisitReferences = ComponentType_VisitReferences;
	pCompTypeObj->VisitPathReferences = ComponentType_VisitPathReferences;
	pCompTypeObj->FindByPath = ComponentType_FindByPath;

	pCompTypeObj->Delete = delete_ComponentType;

	return pCompTypeObj;
}

char* ComponentType_internalGetKey(void* const this)
{
	if (this == NULL)
		return NULL;

	return TypeDefinition_internalGetKey((TypeDefinition*)this);
}

char* ComponentType_metaClassName(void* const this)
{
	/*ComponentType *pObj = (ComponentType*)this;
	char *name;

	name = malloc(sizeof(char) * (strlen("ComponentType")) + 1);
	if(name != NULL)
		strcpy(name, "ComponentType");
	else
		return NULL;

	return name;*/
	return "ComponentType";
}

PortTypeRef* ComponentType_FindRequiredByID(TypeDefinition* const this, char* id)
{
	PortTypeRef* value = NULL;

	if(hashmap_get(((ComponentType*)this->pDerivedObj)->required, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

PortTypeRef* ComponentType_FindProvidedByID(TypeDefinition* const this, char* id)
{
	PortTypeRef* value = NULL;

	if(hashmap_get(((ComponentType*)this->pDerivedObj)->provided, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void ComponentType_AddRequired(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef *container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The PortTypeRef cannot be added in ComponentType because the key is not defined");
	}
	else
	{
		if(this->required == NULL)
		{
			this->required = hashmap_new();
		}

		if(hashmap_get(this->required, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			if(hashmap_put(this->required, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->super->path)) + 1);
				strcpy(ptr->eContainer, this->super->path);
				ptr->path = malloc(sizeof(char) * (strlen(this->path) +	strlen("/required[]") +	strlen(internalKey)) + 1);
				sprintf(ptr->path, "%s/required[%s]", this->super->path, ptr->internalGetKey(ptr));
			}
		}
	}
}

void ComponentType_AddProvided(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef *container = NULL;

	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The PortTypeRef cannot be added in ComponentType because the key is not defined");
	}
	else
	{
		if(this->provided == NULL)
		{
			this->provided = hashmap_new();
		}
		if(hashmap_get(this->provided, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (PortTypeRef*)ptr;*/
			if(hashmap_put(this->provided, internalKey, ptr) == MAP_OK)
			{
				ptr->eContainer = malloc(sizeof(char) * (strlen(this->super->path)) + 1);
				strcpy(ptr->eContainer, this->super->path);
				ptr->path = malloc(sizeof(char) * (strlen(this->path) +	strlen("/provided[]") +	strlen(internalKey)) + 1);
				sprintf(ptr->path, "%s/provided[%s]", this->super->path, ptr->internalGetKey(ptr));
			}
		}
	}
}

void ComponentType_RemoveRequired(TypeDefinition* const this, PortTypeRef* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The PortTypeRef cannot be removed in ComponentType because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(((ComponentType*)this->pDerivedObj)->required, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void ComponentType_RemoveProvided(TypeDefinition* const this, PortTypeRef* ptr)
{
	char *internalKey = ptr->internalGetKey(ptr);

	if(internalKey == NULL)
	{
		PRINTF("The PortTypeRef cannot be removed in ComponentType because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(((ComponentType*)this->pDerivedObj)->provided, internalKey) == MAP_OK)
		{
			free(ptr->eContainer);
			ptr->eContainer = NULL;
			free(ptr->path);
			ptr->path = NULL;
		}
	}
}

void deletePoly_ComponentType(void* const this)
{
	TypeDefinition *pObj = (TypeDefinition*)this;
	ComponentType* pCompTypeObj;
	pCompTypeObj = pObj->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pCompTypeObj->required);
	hashmap_free(pCompTypeObj->provided);
	free(pCompTypeObj);
	/*destroy base Obj*/
	delete_TypeDefinition(pObj);
}

void delete_ComponentType(void* const this)
{
	ComponentType *pObj = (ComponentType*)this;
	/* destroy base object */
	delete_TypeDefinition(pObj->super);
	/* destroy data memebers */
	hashmap_free(pObj->required);
	hashmap_free(pObj->provided);
	free(this);
}

void ComponentType_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}

void ComponentType_VisitPathAttributes(void * const this, char* parent, Visitor* visitor, bool recursive)
{
	TypeDefinition_VisitPathAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}

void ComponentType_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	TypeDefinition* pObj = (TypeDefinition*)this;
	ComponentType* pDerivedObj = (ComponentType*)(pObj->pDerivedObj);

	if(pDerivedObj->required != NULL)
	{
		visitor->action("required", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(pDerivedObj->required);

		/* required */
		hashmap_map* m = pDerivedObj->required;

		/* compare required */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				PortTypeRef* n = data;
				/*sprintf(path, "%s/required[%s]", parent, n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, true);
				n->VisitReferences(n, path, visitor, true);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("required", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	if(pDerivedObj->provided != NULL)
	{
		visitor->action("provided", SQBRACKET, NULL);
		int i;
		int length = hashmap_length(pDerivedObj->provided);

		/* provided */
		hashmap_map* m = pDerivedObj->provided;

		/* compare provided */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				visitor->action(NULL, BRACKET, NULL);
				any_t data = (any_t) (m->data[i].data);
				PortTypeRef* n = data;
				/*sprintf(path, "%s/provided[%s]", parent, n->internalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, true);
				n->VisitReferences(n, path, visitor, true);
				if(length > 1)
				{
					visitor->action(NULL, CLOSEBRACKETCOLON, NULL);
					length--;
				}
				else
					visitor->action(NULL, CLOSEBRACKET, NULL);
			}
		}
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("provided", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	TypeDefinition_VisitReferences(pObj, parent, visitor, recursive);
}

void ComponentType_VisitPathReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	TypeDefinition* pObj = (TypeDefinition*)this;
	ComponentType* pDerivedObj = (ComponentType*)(pObj->pDerivedObj);

	TypeDefinition_VisitPathReferences(pObj, parent, visitor, recursive);

	if(pDerivedObj->required != NULL)
	{
		int i;

		/* required */
		hashmap_map* m = pDerivedObj->required;

		/* compare required */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				PortTypeRef* n = data;
				sprintf(path, "%s/required[%s]", parent, n->internalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, true);
				n->VisitPathReferences(n, path, visitor, true);
			}
		}
	}

	if(pDerivedObj->provided != NULL)
	{
		int i;

		/* provided */
		hashmap_map* m = pDerivedObj->provided;

		/* compare provided */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				PortTypeRef* n = data;
				sprintf(path, "%s/provided[%s]", parent, n->internalGetKey(n));
				n->VisitPathAttributes(n, path, visitor, true);
				n->VisitPathReferences(n, path, visitor, true);
			}
		}
	}
}

void* ComponentType_FindByPath(char* attribute, void* const this)
{
	/*
	 * TODO fix polymorphism
	 */
	TypeDefinition *pObj = (TypeDefinition*)this;
	/* There is no local attributes */
	/* TypeDefinition attributes */
	if(!strcmp("name",attribute) ||  !strcmp("version",attribute) || !strcmp("factoryBean",attribute) || !strcmp("bean",attribute) || !strcmp("abstract",attribute))
	{
		return TypeDefinition_FindByPath(attribute, pObj);
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

		if(!strcmp("required", obj))
		{
			free(obj);
			/*
			 * TODO fix polymorphism
			 */
			ComponentType* comptype = pObj->pDerivedObj;

			if(nextAttribute == NULL)
			{

				return comptype->FindRequiredByID(comptype->super, key);
			}
			else
			{
				PortTypeRef* ptypref = comptype->FindRequiredByID(comptype->super, key);
				if(ptypref != NULL)
					return ptypref->FindByPath(nextPath, ptypref);
				else
					return NULL;
			}
		}
		else if(!strcmp("provided", obj))
		{
			free(obj);
			ComponentType* comptype = pObj->pDerivedObj;

			if(nextAttribute == NULL)
			{

				return comptype->FindProvidedByID(comptype->super, key);
			}
			else
			{
				PortTypeRef* ptypref = comptype->FindProvidedByID(comptype->super, key);
				if(ptypref != NULL)
					return ptypref->FindByPath(nextPath, ptypref);
				else
					return NULL;
			}
		}
		/* TypeDefinition references */
		else
		{
			free(obj);
			return TypeDefinition_FindByPath(attribute, pObj);
		}
	}
}
