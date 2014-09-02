#include "NamedElement.h"
#include "ContainerRoot.h"
#include "Visitor.h"
#include "TypedElement.h"

NamedElement* newPoly_TypedElement(void)
{
	TypedElement* pTypeElemObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeElemObj = (TypedElement*)my_malloc(sizeof(TypedElement));

	if (pTypeElemObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pTypeElemObj; /* Pointing to derived object */
	
	pTypeElemObj->genericTypes = NULL;
	pTypeElemObj->eContainer = NULL;
	
	pTypeElemObj->FindGenericTypesByID = TypedElement_FindGenericTypesByID;
	pTypeElemObj->AddGenericTypes = TypedElement_AddGenericTypes;
	pTypeElemObj->RemoveGenericTypes = TypedElement_RemoveGenericTypes;
	
	pObj->MetaClassName = TypedElement_MetaClassName;
	pObj->InternalGetKey = TypedElement_InternalGetKey;
	pObj->Delete = deletePoly_TypedElement;
	pObj->VisitAttributes = TypedElement_VisitAttributes;
	pObj->VisitReferences = TypedElement_VisitReferences;
	pObj->FindByPath = TypedElement_FindByPath;

	return pObj;
}

TypedElement* new_TypedElement(void)
{
	TypedElement* pTypeElemObj = NULL;
	NamedElement* pObj = new_NamedElement();

	if(pObj == NULL)
		return NULL;
	
	/* Allocating memory */
	pTypeElemObj = (TypedElement*)my_malloc(sizeof(TypedElement));

	if (pTypeElemObj == NULL)
	{
		return NULL;
	}

	pObj->pDerivedObj = pObj;  /*Pointing to derived object */
	pTypeElemObj->super = pObj;
	
	pTypeElemObj->genericTypes = NULL;
	pTypeElemObj->eContainer = NULL;
	
	pTypeElemObj->FindGenericTypesByID = TypedElement_FindGenericTypesByID;
	pTypeElemObj->AddGenericTypes = TypedElement_AddGenericTypes;
	pTypeElemObj->RemoveGenericTypes = TypedElement_RemoveGenericTypes;
	
	pTypeElemObj->MetaClassName = TypedElement_MetaClassName;
	pObj->MetaClassName = TypedElement_MetaClassName;
	pTypeElemObj->InternalGetKey = TypedElement_InternalGetKey;
	pTypeElemObj->Delete = delete_TypedElement;
	pTypeElemObj->VisitAttributes = TypedElement_VisitAttributes;
	pTypeElemObj->VisitReferences = TypedElement_VisitReferences;
	pTypeElemObj->FindByPath = TypedElement_FindByPath;

	return pTypeElemObj;
}

char* TypedElement_MetaClassName(TypedElement* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("TypedElement")) + 1);
	if(name != NULL)
		strcpy(name, "TypedElement");
	else
		return NULL;
	
	return name;
}

char* TypedElement_InternalGetKey(TypedElement* const this)
{
	return this->super->InternalGetKey(this->super);
}

TypedElement* TypedElement_FindGenericTypesByID(TypedElement* const this, char* id)
{
	TypedElement* value = NULL;

	if(this->genericTypes)
	{
		if(hashmap_get(this->genericTypes, id, (void**)(&value)) == MAP_OK)
			return value;
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

void TypedElement_AddGenericTypes(TypedElement* const this, TypedElement* ptr)
{
	TypedElement* container = NULL;
	
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The TypedElement cannot be added in TypedElement because the key is not defined");
	}
	else
	{
		if(this->genericTypes == NULL)
		{
			this->genericTypes = hashmap_new();
		}
		if(hashmap_get(this->genericTypes, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (TypedElement*)ptr;*/
			hashmap_put(this->genericTypes, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void TypedElement_RemoveGenericTypes(TypedElement* const this, TypedElement* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The TypedElement cannot be removed in TypedElement because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->genericTypes, ptr->InternalGetKey(ptr));
	}
}

void deletePoly_TypedElement(NamedElement* const this)
{
	if(this != NULL)
	{
		TypedElement* pTypeElemObj;
		pTypeElemObj = this->pDerivedObj;
		/*destroy derived obj*/
		hashmap_free(pTypeElemObj->genericTypes);
		free(pTypeElemObj->eContainer);
		free(pTypeElemObj);
		/*destroy base Obj*/
		delete_NamedElement(this);
	}
}

void delete_TypedElement(TypedElement* const this)
{
	if(this != NULL)
	{
		/* destroy base object */
		delete_NamedElement(this->super);
		/* destroy data memebers */
		hashmap_free(this->genericTypes);
		free(this->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

void TypedElement_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	/*char path[256];
	memset(&path[0], 0, sizeof(path));

	sprintf(path,"%s\\cClass", parent);
	visitor->action(path, STRING, ((TypedElement*)this)->MetaClassName((TypedElement*)this));*/

	NamedElement_VisitAttributes(((TypedElement*)(this))->super, parent, visitor, 1);
}

void TypedElement_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypedElement*)(this))->genericTypes != NULL)
	{
		visitor->action("genericTypes", SQBRACKET, NULL);
		int i;
		
		/* genericTypes */
		hashmap_map* m = ((TypedElement*)(this))->genericTypes;

		/* compare genericTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypedElement* n = data;
				/*sprintf(path,"%s/genericTypes[%s]", parent, n->super->name);*/
				sprintf(path,"genericTypes[%s]", n->InternalGetKey(n));
				/*n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);*/
				visitor->action(path, STRREF, NULL);
				visitor->action(NULL, RETURN, NULL);
			}
		}
	}
}

void* TypedElement_FindByPath(char* attribute, TypedElement* const this)
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
	  
		if(!strcmp("genericTypes", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindGenericTypesByID(this, queryID);
			}
			else
			{
				TypedElement* typelem = this->FindGenericTypesByID(this, queryID);
				if(typelem != NULL)
					return typelem->FindByPath(nextAttribute, typelem);
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
