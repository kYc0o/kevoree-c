#include "NamedElement.h"
#include "DeployUnit.h"
#include "DictionaryType.h"
#include "TypeDefinition.h"

NamedElement* newPoly_TypeDefinition()
{
	TypeDefinition* pTypeDefObj = NULL;
	NamedElement* pObj = new_NamedElement();

	/* Allocating memory */
	pTypeDefObj = (TypeDefinition*)my_malloc(sizeof(TypeDefinition));

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
	pObj->VisitReferences = TypeDefinition_VisitReferences;

	return pObj;
}

TypeDefinition* new_TypeDefinition()
{
	TypeDefinition* pTypeDefObj = NULL;
	NamedElement* pObj = new_NamedElement();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pTypeDefObj = (TypeDefinition*)my_malloc(sizeof(TypeDefinition));

	if (pTypeDefObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pTypeDefObj; Pointing to derived object */
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
	pTypeDefObj->VisitReferences = TypeDefinition_VisitReferences;
	pTypeDefObj->FindByPath = TypeDefinition_FindByPath;

	return pTypeDefObj;
}

char* TypeDefinition_InternalGetKey(TypeDefinition* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = my_malloc(sizeof(char) * (strlen("name=") + strlen(this->super->name) + strlen(",") +
										strlen("version=") + strlen(this->version)) + 1);

	if (internalKey == NULL)
		return NULL;
	
	sprintf(internalKey, "%s/%s", this->super->name, this->version);

	return internalKey;
}

char* TypeDefinition_MetaClassName(TypeDefinition* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("TypeDefinition")) + 1);
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
	}
}

void TypeDefinition_RemoveDeployUnit(TypeDefinition* const this, DeployUnit* ptr)
{
	free(ptr);
	this->deployUnits = NULL;
}

void TypeDefinition_RemoveDictionaryType(TypeDefinition* const this, DictionaryType *ptr)
{
	free(ptr);
	this->dictionaryType = NULL;
}

void TypeDefinition_AddSuperTypes(TypeDefinition* const this, TypeDefinition* ptr)
{
	TypeDefinition* container = NULL;
	
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The TypeDefinition cannot be added in TypeDefinition because the key is not defined\n");
	}
	else
	{
		if(this->superTypes == NULL)
		{
			this->superTypes = hashmap_new();
		}
		if(hashmap_get(this->superTypes, ptr->InternalGetKey(ptr), (void**)(&container)) == MAP_MISSING)
		{
			/*container = (TypeDefinition*)ptr;*/
			hashmap_put(this->superTypes, ptr->InternalGetKey(ptr), ptr);
		}
	}
}

void TypeDefinition_RemoveSuperTypes(TypeDefinition* const this, TypeDefinition* ptr)
{
	if(ptr->InternalGetKey(ptr) == NULL)
	{
		printf("The TypeDefinition cannot be removed in TypeDefinition because the key is not defined\n");
	}
	else
	{
		hashmap_remove(this->superTypes, ptr->InternalGetKey(ptr));
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

void TypeDefinition_VisitAttributes(void* const this, char* parent, Visitor* visitor, int recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		/*sprintf(path,"%s\\cClass", parent);
		visitor->action(path, STRING, ((TypeDefinition*)this)->MetaClassName((TypeDefinition*)this));*/

		NamedElement_VisitAttributes(((TypeDefinition*)(this))->super, parent, visitor, recursive);

		/*sprintf(path, "%s\\version", parent);*/
		sprintf(path, "version");
		visitor->action(path, STRING, ((TypeDefinition*)(this))->version);
		visitor->action(NULL, COLON, NULL);

		/*printf(path,"%s\\factoryBean",parent);*/
		sprintf(path, "factoryBean");
		visitor->action(path, STRING, ((TypeDefinition*)(this))->factoryBean);
		visitor->action(NULL, COLON, NULL);

		/*sprintf(path,"%s\\bean",parent);*/
		sprintf(path, "bean");
		visitor->action(path, STRING, ((TypeDefinition*)(this))->bean);
		visitor->action(NULL, COLON, NULL);

		/*sprintf(path, "%s\\abstract", parent);*/
		sprintf(path, "abstract");
		visitor->action(path, BOOL, (void*)((TypeDefinition*)(this))->abstract);
		visitor->action(NULL, COLON, NULL);
	}
	else
	{
		NamedElement_VisitAttributes(((TypeDefinition*)(this))->super, parent, visitor, recursive);
	}
}

void TypeDefinition_VisitReferences(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	if(((TypeDefinition*)(this))->deployUnits != NULL)
	{
		visitor->action("deployUnit", SQBRACKET, NULL);
		/*sprintf(path, "%s/deployUnit[%s]", parent, ((TypeDefinition*)(this))->deployUnits->InternalGetKey(((TypeDefinition*)(this))->deployUnits));*/
		sprintf(path, "deployUnits[%s]", ((TypeDefinition*)(this))->deployUnits->InternalGetKey(((TypeDefinition*)(this))->deployUnits));
		/*DeployUnit* n = ((TypeDefinition*)(this))->deployUnits;
		n->VisitAttributes(n, path, visitor, 0);*/
		visitor->action(path, STRREF, NULL);
		visitor->action(NULL, RETURN, NULL);
		/*n->VisitReferences(n, path, visitor);*/
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
				/*sprintf(path,"%s/superTypes[%s]", parent, n->InternalGetKey(n));*/
				sprintf(path,"superTypes[%s]", n->InternalGetKey(n));
				/*n->VisitAttributes(n, path, visitor, 0);*/
				/*n->VisitReferences(n, path, visitor);*/
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
		return this->abstract;
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

		if(!strcmp("deployUnits", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->deployUnits;
			}
			else
			{
				return this->deployUnits->FindByPath(nextAttribute, this->deployUnits);
			}
		}
		else if(!strcmp("dictionaryType", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->dictionaryType;
			}
			else
			{
				return this->dictionaryType->FindByPath(nextAttribute, this->dictionaryType);
			}
		}
		else
		{
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
