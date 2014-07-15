#include "TypeLibrary.h"

NamedElement* newPoly_TypeLibrary(void)
{
	TypeLibrary* pTypeLibObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeLibObj = (TypeLibrary*)malloc(sizeof(TypeLibrary));

	if (pTypeLibObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pTypeLibObj; /* Pointing to derived object */
	
	/*pTypeLibObj->subTypes = hashmap_new();*/
	pTypeLibObj->subTypes = NULL;
	
	pTypeLibObj->FindSubTypesByID = TypeLibrary_FindSubTypesByID;
	pTypeLibObj->AddSubTypes = TypeLibrary_AddSubTypes;
	pTypeLibObj->RemoveSubTypes = TypeLibrary_RemoveSubTypes;
	
	pObj->MetaClassName = TypeLibrary_MetaClassname;
	pObj->InternalGetKey = TypeLibrary_InternalGetKey;
	pObj->Delete = deletePoly_TypeLibrary;
	pObj->VisitAttributes = TypeLibrary_VisitAttributes;
	pObj->VisitReferences = TypeLibrary_VisitReferences;

	return pObj;
}

TypeLibrary* new_TypeLibrary(void)
{
	TypeLibrary* pTypeLibObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;
	
	/* Allocating memory */
	pTypeLibObj = (TypeLibrary*)malloc(sizeof(TypeLibrary));

	if (pTypeLibObj == NULL)
	{
		return NULL;
	}

	/* pObj->pDerivedObj = pTypeLibObj; Pointing to derived object */
	pTypeLibObj->super = pObj;
	
	/*pTypeLibObj->subTypes = hashmap_new();*/
	pTypeLibObj->subTypes = NULL;
	
	pTypeLibObj->FindSubTypesByID = TypeLibrary_FindSubTypesByID;
	pTypeLibObj->AddSubTypes = TypeLibrary_AddSubTypes;
	pTypeLibObj->RemoveSubTypes = TypeLibrary_RemoveSubTypes;
	
	pTypeLibObj->MetaClassName = TypeLibrary_MetaClassname;
	pTypeLibObj->InternalGetKey = TypeLibrary_InternalGetKey;
	pTypeLibObj->Delete = delete_TypeLibrary;
	pTypeLibObj->VisitAttributes = TypeLibrary_VisitAttributes;
	pTypeLibObj->VisitReferences = TypeLibrary_VisitReferences;

	return pTypeLibObj;
}

char* TypeLibrary_MetaClassname(TypeLibrary* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("TypeLibrary") + 1));
	strcpy(name, "TypeLibrary");
	
	return name;
}

char* TypeLibrary_InternalGetKey(TypeLibrary* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->name)));

	if (internalKey == NULL)
		return NULL;

	strcpy(internalKey, this->super->name);

	return internalKey;
}

TypeDefinition* TypeLibrary_FindSubTypesByID(TypeLibrary* const this, char* id)
{
	TypeDefinition* value;

	if(hashmap_get(this->subTypes, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

/*void TypeLibrary::addsubTypes(TypeDefinition *ptr)*/
void TypeLibrary_AddSubTypes(TypeLibrary* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = (TypeDefinition*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be added in TypeLibrary because the key is not defined");*/
		printf("The TypeDefinition cannot be added in TypeLibrary because the key is not defined\n");
	}
	else
	{
		/*if(subTypes.find(container->internalGetKey()) == subTypes.end())*/
		if(this->subTypes == NULL)
		{
			this->subTypes = hashmap_new();
		}
		if(hashmap_get(this->subTypes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*subTypes[container->internalGetKey()]=ptr;*/
			container = (TypeDefinition*)ptr;
			hashmap_put(this->subTypes, container->InternalGetKey(container), ptr);
		}
	}
}

/*void TypeLibrary::removesubTypes(TypeDefinition *ptr)*/
void TypeLibrary_RemoveSubTypes(TypeLibrary* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = (TypeDefinition*)ptr;

	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be removed in TypeLibrary because the key is not defined");*/
		printf("The TypeDefinition cannot be removed in TypeLibrary because the key is not defined\n");
	}
	else
	{
		/*subTypes.erase( subTypes.find(container->internalGetKey()));*/
		hashmap_remove(this->subTypes, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void deletePoly_TypeLibrary(NamedElement* const this)
{
	TypeLibrary* pTypeLibObj;
	pTypeLibObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pTypeLibObj->subTypes);
	free(pTypeLibObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_TypeLibrary(TypeLibrary* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	hashmap_free(this->subTypes);
	free(this);
}

void TypeLibrary_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path,"%s/%s",parent, ((TypeLibrary*)(this))->super->name);*/

	/*sprintf(path,"%s\\name",parent);
	visitor->action(path, STRING, ((TypeLibrary*)(this))->super->name);*/
	NamedElement_VisitAttributes(((TypeLibrary*)(this))->super, parent, visitor);
}

void TypeLibrary_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[128];
	memset(&path[0], 0, sizeof(path));

	if(((TypeLibrary*)(this))->subTypes != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/subTypes[%s]", parent, ((TypeLibrary*)(this))->super->name);*/
		
		/* subTypes */
		hashmap_map* m = ((TypeLibrary*)(this))->subTypes;

		/* compare subTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypeDefinition* n = data;
				sprintf(path,"%s/subTypes[%s]", parent, n->super->name);
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
			}
		}
	}
}

void* TypeLibrary_FindByPath(char* attribute, TypeLibrary* const this)
{
	/* NamedElement attributes */
	if(!strcmp("name",attribute))
	{
		return this->super->FindByPath(attribute, this->super);
	}
	/* Local references */
	else
	{
		char* path = strdup(attribute);
		char* pch;

		if(indexOf(path,"/") != -1)
		{
			pch = strtok (path,"/");
		}
		else
		{
			pch = path;
		}
		
		printf("Token: %s\n", pch);

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);
		char* nextAttribute = strtok(NULL, "\\");
		printf("relationName: %s\n", relationName);
		printf("queryID: %s\n", queryID);
		printf("next attribute: %s\n", nextAttribute);
	  
		if(!strcmp("subTypes", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindSubTypesByID(this, queryID);
			}
			else
			{
				TypeDefinition* typdef = this->FindSubTypesByID(this, queryID);
				return typdef->FindByPath(nextAttribute, typdef);
			}
		}
		else
		{
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
