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
	
	pTypeLibObj->subTypes = NULL;
	
	pTypeLibObj->FindSubTypesByID = TypeLibrary_FindSubTypesByID;
	pTypeLibObj->AddSubTypes = TypeLibrary_AddSubTypes;
	pTypeLibObj->RemoveSubTypes = TypeLibrary_RemoveSubTypes;
	
	pTypeLibObj->MetaClassName = TypeLibrary_MetaClassname;
	pObj->MetaClassName = TypeLibrary_MetaClassname;
	pTypeLibObj->InternalGetKey = TypeLibrary_InternalGetKey;
	pTypeLibObj->Delete = delete_TypeLibrary;
	pTypeLibObj->VisitAttributes = TypeLibrary_VisitAttributes;
	pTypeLibObj->VisitReferences = TypeLibrary_VisitReferences;

	return pTypeLibObj;
}

char* TypeLibrary_MetaClassname(TypeLibrary* const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("TypeLibrary")) + 1);
	if(name != NULL)
		strcpy(name, "TypeLibrary");
	else
		return NULL;
	
	return name;
}

char* TypeLibrary_InternalGetKey(TypeLibrary* const this)
{
	return this->super->InternalGetKey(this->super);
}

TypeDefinition* TypeLibrary_FindSubTypesByID(TypeLibrary* const this, char* id)
{
	TypeDefinition* value = NULL;

	if(this->subTypes != NULL)
	{
		if(hashmap_get(this->subTypes, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void TypeLibrary_AddSubTypes(TypeLibrary* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = NULL;
	
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The TypeDefinition cannot be added in TypeLibrary because the key is not defined\n");
	}
	else
	{
		if(this->subTypes == NULL)
		{
			this->subTypes = hashmap_new();
		}
		if(hashmap_get(this->subTypes, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (TypeDefinition*)ptr;*/
			hashmap_put(this->subTypes, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void TypeLibrary_RemoveSubTypes(TypeLibrary* const this, TypeDefinition* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The TypeDefinition cannot be removed in TypeLibrary because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->subTypes, ptr->InternalGetKey(ptr));
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
	/*char path[256];
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	visitor->action(path, STRING, ((TypedElement*)this)->MetaClassName((TypedElement*)this));*/

	NamedElement_VisitAttributes(((TypeLibrary*)(this))->super, parent, visitor, 1);
}

void TypeLibrary_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypeLibrary*)(this))->subTypes != NULL)
	{
		int i;
		
		/* subTypes */
		hashmap_map* m = ((TypeLibrary*)(this))->subTypes;

		/* compare subTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypeDefinition* n = data;
				sprintf(path,"%s/subTypes[%s]", parent, n->InternalGetKey(n));
				n->VisitAttributes(n, path, visitor, 0);
				/*n->VisitReferences(n, path, visitor);*/
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
	  
		if(!strcmp("subTypes", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindSubTypesByID(this, queryID);
			}
			else
			{
				TypeDefinition* typdef = this->FindSubTypesByID(this, queryID);
				if(typdef != NULL)
					return typdef->FindByPath(nextAttribute, typdef);
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
