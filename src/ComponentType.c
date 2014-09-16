#include <string.h>
#include "PortTypeRef.h"
#include "NamedElement.h"
#include "TypeDefinition.h"
#include "Visitor.h"
#include "ComponentType.h"

TypeDefinition* newPoly_ComponentType(void)
{
	ComponentType* pCompTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pCompTypeObj = (ComponentType*)my_malloc(sizeof(ComponentType));

	if (pCompTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pCompTypeObj; /* Pointing to derived object */
	pCompTypeObj->super = pObj;
	
	pCompTypeObj->required = NULL;
	pCompTypeObj->provided = NULL;
	
	pCompTypeObj->FindRequiredByID = ComponentType_FindRequiredByID;
	pCompTypeObj->FindProvidedByID = ComponentType_FindProvidedByID;
	pCompTypeObj->AddRequired = ComponentType_AddRequired;
	pCompTypeObj->AddProvided = ComponentType_AddProvided;
	pCompTypeObj->RemoveRequired = ComponentType_RemoveRequired;
	pCompTypeObj->RemoveProvided = ComponentType_RemoveProvided;

	pCompTypeObj->MetaClassName = ComponentType_MetaClassName;
	pCompTypeObj->InternalGetKey = ComponentType_InternalGetKey;
	pCompTypeObj->VisitAttributes = ComponentType_VisitAttributes;
	pCompTypeObj->VisitReferences = ComponentType_VisitReferences;

	pObj->super->MetaClassName = ComponentType_MetaClassName;
	pObj->InternalGetKey = ComponentType_InternalGetKey;
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
	pCompTypeObj = (ComponentType*)my_malloc(sizeof(ComponentType));

	if (pCompTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	/*pObj->pDerivedObj = pCompTypeObj;  Pointing to derived object */
	pObj->pDerivedObj = NULL;
	pCompTypeObj->super = pObj;
	
	pCompTypeObj->required = NULL;
	pCompTypeObj->provided = NULL;
	
	pCompTypeObj->FindRequiredByID = ComponentType_FindRequiredByID;
	pCompTypeObj->FindProvidedByID = ComponentType_FindProvidedByID;
	pCompTypeObj->AddRequired = ComponentType_AddRequired;
	pCompTypeObj->AddProvided = ComponentType_AddProvided;
	pCompTypeObj->RemoveRequired = ComponentType_RemoveRequired;
	pCompTypeObj->RemoveProvided = ComponentType_RemoveProvided;

	pCompTypeObj->MetaClassName = ComponentType_MetaClassName;
	pCompTypeObj->InternalGetKey = ComponentType_InternalGetKey;
	pCompTypeObj->VisitAttributes = ComponentType_VisitAttributes;
	pCompTypeObj->VisitReferences = ComponentType_VisitReferences;
	
	pCompTypeObj->Delete = delete_ComponentType;

	return pCompTypeObj;
}

char* ComponentType_InternalGetKey(void* const this)
{
	if (this == NULL)
		return NULL;
	
	return TypeDefinition_InternalGetKey((TypeDefinition*)this);
}

char* ComponentType_MetaClassName(ComponentType* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("ComponentType")) + 1);
	if(name != NULL)
		strcpy(name, "ComponentType");
	else
		return NULL;
	
	return name;
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

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The PortTypeRef cannot be added in ComponentType because the key is not defined");
	}
	else
	{
		if(this->required == NULL)
		{
			this->required = hashmap_new();
		}

		if(hashmap_get(this->required, internalKey, (void**)(&container)) == MAP_MISSING)
		{
			/*container = (PortTypeRef*)ptr;*/
			if(hashmap_put(this->required, internalKey, ptr) == MAP_OK)
			{
				TypeDefinition *typdef = this->super;
				char *strContainer = typdef->InternalGetKey(typdef);
				ptr->eContainer = my_malloc(sizeof(char) * (strlen("typeDefinitions[]") + strlen(strContainer)) + 1);
				sprintf(ptr->eContainer, "typeDefinitions[%s]", strContainer);
				str_free(strContainer);
			}
		}
	}
}

void ComponentType_AddProvided(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef *container = NULL;

	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The PortTypeRef cannot be added in ComponentType because the key is not defined");
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
				TypeDefinition *typdef = this->super;
				char *strContainer = typdef->InternalGetKey(typdef);
				ptr->eContainer = my_malloc(sizeof(char) * (strlen("typeDefinitions[]") + strlen(strContainer)) + 1);
				sprintf(ptr->eContainer, "typeDefinitions[%s]", strContainer);
				str_free(strContainer);
			}
		}
	}
}

void ComponentType_RemoveRequired(TypeDefinition* const this, PortTypeRef* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The PortTypeRef cannot be removed in ComponentType because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(((ComponentType*)this->pDerivedObj)->required, internalKey) == MAP_OK)
		{
			str_free(ptr->eContainer);
			ptr->eContainer = NULL;
			str_free(internalKey);
		}
	}
}

void ComponentType_RemoveProvided(TypeDefinition* const this, PortTypeRef* ptr)
{
	char *internalKey = ptr->InternalGetKey(ptr);

	if(internalKey == NULL)
	{
		printf("The PortTypeRef cannot be removed in ComponentType because the key is not defined\n");
	}
	else
	{
		if(hashmap_remove(((ComponentType*)this->pDerivedObj)->provided, internalKey) == MAP_OK)
		{
			ptr->eContainer = NULL;
			free(internalKey);
		}
	}
}

void deletePoly_ComponentType(TypeDefinition* const this)
{
	ComponentType* pCompTypeObj;
	pCompTypeObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pCompTypeObj->required);
	hashmap_free(pCompTypeObj->provided);
	free(pCompTypeObj);
	/*destroy base Obj*/
	delete_TypeDefinition(this);
}
void delete_ComponentType(ComponentType* const this)
{
	/* destroy base object */
	delete_TypeDefinition(this->super);
	/* destroy data memebers */
	hashmap_free(this->required);
	hashmap_free(this->provided);
	free(this);
}

void ComponentType_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	/*char path[256];
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	visitor->action(path, STRING, ((TypeDefinition*)this)->MetaClassName((TypeDefinition*)this));*/

	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor, recursive);
}

void ComponentType_VisitReferences(void* const this, char* parent, Visitor* visitor)
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
				/*sprintf(path, "%s/required[%s]", parent, n->InternalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, 1);
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
				/*sprintf(path, "%s/provided[%s]", parent, n->InternalGetKey(n));*/
				n->VisitAttributes(n, path, visitor, 1);
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
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}
	else
	{
		visitor->action("provided", SQBRACKET, NULL);
		visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
	}

	TypeDefinition_VisitReferences(pObj, parent, visitor);
}

void* ComponentType_FindByPath(char* attribute, TypeDefinition* const this)
{
	/* There is no local attributes */
	/* TypeDefinition attributes */
	if(!strcmp("name",attribute) ||  !strcmp("version",attribute) || !strcmp("factoryBean",attribute) || !strcmp("bean",attribute) || !strcmp("abstract",attribute))
	{
		return TypeDefinition_FindByPath(attribute, this);
	}
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
		
		if(!strcmp("required", relationName))
		{
			ComponentType* comptype = this->pDerivedObj;
			
			if(nextAttribute == NULL)
			{
				
				return comptype->FindRequiredByID(comptype, queryID);
			}
			else
			{
				PortTypeRef* ptypref = comptype->FindRequiredByID(comptype, queryID);
				if(ptypref != NULL)
					return ptypref->FindByPath(nextAttribute, ptypref);
				else
					return NULL;
			}
		}
		else if(!strcmp("provided", relationName))
		{
			ComponentType* comptype = this->pDerivedObj;
			
			if(nextAttribute == NULL)
			{
				
				return comptype->FindProvidedByID(comptype, queryID);
			}
			else
			{
				PortTypeRef* ptypref = comptype->FindProvidedByID(comptype, queryID);
				if(ptypref != NULL)
					return ptypref->FindByPath(nextAttribute, ptypref);
				else
					return NULL;
			}
		}
		/* TypeDefinition references */
		else
		{
			return TypeDefinition_FindByPath(attribute, this);
		}
	}
}
