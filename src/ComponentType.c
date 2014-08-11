#include "ComponentType.h"

int result;

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
	
	/*pCompTypeObj->required = hashmap_new();
	pCompTypeObj->provided = hashmap_new();*/
	pCompTypeObj->required = NULL;
	pCompTypeObj->provided = NULL;
	
	pCompTypeObj->FindRequiredByID = ComponentType_FindRequiredByID;
	pCompTypeObj->FindProvidedByID = ComponentType_FindProvidedByID;
	pCompTypeObj->AddRequired = ComponentType_AddRequired;
	pCompTypeObj->AddProvided = ComponentType_AddProvided;
	pCompTypeObj->RemoveRequired = ComponentType_RemoveRequired;
	pCompTypeObj->RemoveProvided = ComponentType_RemoveProvided;

	pObj->MetaClassName = ComponentType_MetaClassName;
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
	pCompTypeObj = (ComponentType*)malloc(sizeof(ComponentType));

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
	char* internalKey;

	if (this == NULL)
		return NULL;

	/*internalKey = malloc(sizeof(char) * (strlen(this->super->super->name) + strlen("/") + strlen(this->super->version)) + 1);

	if (internalKey == NULL)
		return NULL;*/

	/*strcpy(internalKey, this->super->super->name);
	strcat(internalKey, "/");
	strcat(internalKey, this->super->version);
	sprintf(internalKey, "%s/%s", this->super->super->name, this->super->version);*/
	
	internalKey = TypeDefinition_InternalGetKey((TypeDefinition*)this);

	return internalKey;
	/*return ((TypeDefinition*)this)->InternalGetKey(((TypeDefinition*)this));*/
}

char* ComponentType_MetaClassName(ComponentType* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("ComponentType") + 1));
	strcpy(name, "ComponentType");
	
	return name;
}

PortTypeRef* ComponentType_FindRequiredByID(ComponentType* const this, char* id)
{
	PortTypeRef* value;

	if(hashmap_get(this->required, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

PortTypeRef* ComponentType_FindProvidedByID(ComponentType* const this, char* id)
{
	PortTypeRef* value;

	if(hashmap_get(this->provided, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

void ComponentType_AddRequired(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef* container = (PortTypeRef*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeRef cannot be added in ComponentType because the key is not defined");
	}
	else
	{
		if(this->required == NULL)
		{
			this->required = hashmap_new();
		}

		if(hashmap_get(this->required, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (PortTypeRef*)ptr;
			result = hashmap_put(this->required, container->InternalGetKey(container), ptr);
			/*printf("PortTypeRef %s added to ComponentType %s Result: %d\n", ptr->super->name, this->super->super->name, result);*/
		}
	}
}

void ComponentType_AddProvided(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef* container = (PortTypeRef*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeRef cannot be added in ComponentType because the key is not defined");
	}
	else
	{
		if(this->provided == NULL)
		{
			this->provided = hashmap_new();
		}
		if(hashmap_get(this->provided, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			container = (PortTypeRef*)ptr;
			result = hashmap_put(this->provided, container->InternalGetKey(container), ptr);
			/*printf("PortTypeRef %s added to ComponentType %s Result: %d\n", ptr->super->name, this->super->super->name, result);*/
		}
	}
}

void ComponentType_RemoveRequired(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef* container = (PortTypeRef*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeRef cannot be removed in ComponentType because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->required, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void ComponentType_RemoveProvided(ComponentType* const this, PortTypeRef* ptr)
{
	PortTypeRef* container = (PortTypeRef*)ptr;

	if(container->InternalGetKey(container) == NULL)
	{
		printf("The PortTypeRef cannot be removed in ComponentType because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->provided, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
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

void ComponentType_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	/*char path[128];
	memset(&path[0], 0, sizeof(path));*/
	
	/*sprintf(path, "%s/%s", parent, ((TypeDefinition*)(this))->super->name);*/
	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor);
}
void ComponentType_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));
	
	TypeDefinition* pObj = (TypeDefinition*)this;
	ComponentType* pDerivedObj = (ComponentType*)(pObj->pDerivedObj);
	
	TypeDefinition_VisitReferences(pObj, parent, visitor);
		
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
				sprintf(path, "%s/required[%s]", parent, /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
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
				sprintf(path, "%s/required[%s]", parent, /*n->super->name*/n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
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