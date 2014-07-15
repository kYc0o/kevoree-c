#include "TypedElement.h"

NamedElement* newPoly_TypedElement(void)
{
	TypedElement* pTypeElemObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeElemObj = (TypedElement*)malloc(sizeof(TypedElement));

	if (pTypeElemObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pTypeElemObj; /* Pointing to derived object */
	
	/*pTypeElemObj->genericTypes = hashmap_new();*/
	pTypeElemObj->genericTypes = NULL;
	
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
	pTypeElemObj = (TypedElement*)malloc(sizeof(TypedElement));

	if (pTypeElemObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pTypeElemObj;  Pointing to derived object */
	pTypeElemObj->super = pObj;
	
	/*pTypeElemObj->genericTypes = hashmap_new();*/
	pTypeElemObj->genericTypes = NULL;
	
	pTypeElemObj->FindGenericTypesByID = TypedElement_FindGenericTypesByID;
	pTypeElemObj->AddGenericTypes = TypedElement_AddGenericTypes;
	pTypeElemObj->RemoveGenericTypes = TypedElement_RemoveGenericTypes;
	
	pTypeElemObj->MetaClassName = TypedElement_MetaClassName;
	pTypeElemObj->InternalGetKey = TypedElement_InternalGetKey;
	pTypeElemObj->Delete = delete_TypedElement;
	pTypeElemObj->VisitAttributes = TypedElement_VisitAttributes;
	pTypeElemObj->VisitReferences = TypedElement_VisitReferences;
	pTypeElemObj->FindByPath = TypedElement_FindByPath;

	return pTypeElemObj;
}

char* TypedElement_MetaClassName(TypedElement* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("TypedElement") + 1));
	strcpy(name, "TypedElement");
	
	return name;
}

char* TypedElement_InternalGetKey(TypedElement* const this)
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

TypedElement* TypedElement_FindGenericTypesByID(TypedElement* const this, char* id)
{
	TypedElement* value;

	if(hashmap_get(this->genericTypes, id, (void**)(&value)) == MAP_OK)
		return value;
	else
		return NULL;
}

/*void TypedElement::addgenericTypes(TypedElement *ptr)*/
void TypedElement_AddGenericTypes(TypedElement* const this, TypedElement* ptr)
{
	TypedElement* container = (TypedElement*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be added in TypedElement because the key is not defined");*/
		printf("The TypedElement cannot be added in TypedElement because the key is not defined");
	}
	else
	{
		/*if(genericTypes.find(container->internalGetKey()) == genericTypes.end())*/
		if(this->genericTypes == NULL)
		{
			this->genericTypes = hashmap_new();
		}
		if(hashmap_get(this->genericTypes, container->InternalGetKey(container), (void**)(&container)) == MAP_MISSING);
		{
			/*genericTypes[container->internalGetKey()]=ptr;*/
			container = (TypedElement*)ptr;
			hashmap_put(this->genericTypes, container->InternalGetKey(container), ptr);
		}
	}
}

/*void TypedElement::removegenericTypes(TypedElement *ptr)*/
void TypedElement_RemoveGenericTypes(TypedElement* const this, TypedElement* ptr)
{
	TypedElement* container = (TypedElement*)ptr;
	
	/*if(container->internalGetKey().empty())*/
	if(container->InternalGetKey(container) == NULL)
	{
		/*LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be removed in TypedElement because the key is not defined");*/
		printf("The TypedElement cannot be removed in TypedElement because the key is not defined\n");
	}
	else
	{
		/*genericTypes.erase( genericTypes.find(container->internalGetKey()));*/
		hashmap_remove(this->genericTypes, container->InternalGetKey(container));
		/*container->setEContainer(NULL,NULL,"");*/
	}
}

void deletePoly_TypedElement(NamedElement* const this)
{
	TypedElement* pTypeElemObj;
	pTypeElemObj = this->pDerivedObj;
	/*destroy derived obj*/
	hashmap_free(pTypeElemObj->genericTypes);
	free(pTypeElemObj);
	/*destroy base Obj*/
	delete_NamedElement(this);
}

void delete_TypedElement(TypedElement* const this)
{
	/* destroy base object */
	delete_NamedElement(this->super);
	/* destroy data memebers */
	hashmap_free(this->genericTypes);
	free(this);
}

void TypedElement_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	/*char path[128];
	memset(&path[0], 0, sizeof(path));*/

	/*sprintf(path,"%s/%s",parent, ((TypedElement*)(this))->super->name);*/

	/*sprintf(path,"%s\\name",parent);
	visitor->action(path, STRING, ((TypedElement*)(this))->super->name);*/
	NamedElement_VisitAttributes(((TypedElement*)(this))->super, parent, visitor);
}

void TypedElement_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypedElement*)(this))->genericTypes != NULL)
	{
		int i;
		
		/*sprintf(path,"%s/genericTypes[%s]", parent, ((TypedElement*)(this))->super->name);*/
		
		/* genericTypes */
		hashmap_map* m = ((TypedElement*)(this))->genericTypes;

		/* compare genericTypes */
		for(i = 0; i< m->table_size; i++)
		{
			if(m->data[i].in_use != 0)
			{
				any_t data = (any_t) (m->data[i].data);
				TypedElement* n = data;
				sprintf(path,"%s/genericTypes[%s]", parent, n->super->name);
				n->VisitAttributes(n, path, visitor);
				n->VisitReferences(n, path, visitor);
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
	  
		if(!strcmp("genericTypes", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->FindGenericTypesByID(this, queryID);
			}
			else
			{
				TypedElement* typelem = this->FindGenericTypesByID(this, queryID);
				return typelem->FindByPath(nextAttribute, typelem);
			}
		}
		else
		{
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}