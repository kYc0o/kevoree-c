#include "GroupType.h"

TypeDefinition* newPoly_GroupType()
{
	GroupType* pGroupTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();

	/* Allocating memory */
	pGroupTypeObj = (GroupType*)malloc(sizeof(GroupType));

	if (pGroupTypeObj == NULL)
	{
		pObj->Delete(pObj);
		return NULL;
	}

	pObj->pDerivedObj = pGroupTypeObj; /* Pointing to derived object */

	pObj->MetaClassName = GroupType_MetaClassName;
	pObj->InternalGetKey = GroupType_InternalGetKey;
	pObj->VisitAttributes = GroupType_VisitAttributes;
	pObj->VisitReferences = TypeDefinition_VisitReferences;
	
	pObj->Delete = deletePoly_GroupType;

	return pObj;
}

GroupType* new_GroupType()
{
	GroupType* pGroupTypeObj = NULL;
	TypeDefinition* pObj = new_TypeDefinition();
	
	if(pObj == NULL)
		return NULL;

	/* Allocating memory */
	pGroupTypeObj = (GroupType*)malloc(sizeof(GroupType));

	if (pGroupTypeObj == NULL)
	{
		return NULL;
	}

	/*pObj->pDerivedObj = pGroupTypeObj;  Pointing to derived object */
	pGroupTypeObj->super = pObj;

	pGroupTypeObj->MetaClassName = GroupType_MetaClassName;
	pGroupTypeObj->InternalGetKey = GroupType_InternalGetKey;
	pGroupTypeObj->VisitAttributes = GroupType_VisitAttributes;
	pGroupTypeObj->VisitReferences = TypeDefinition_VisitReferences;
	
	pGroupTypeObj->Delete = delete_GroupType;

	return pGroupTypeObj;
}

char* GroupType_MetaClassName(GroupType* const this)
{
	char* internalKey;

	if (this == NULL)
		return NULL;

	internalKey = malloc(sizeof(char) * (strlen(this->super->super->name) + strlen("_") + strlen(this->super->version)) + 1);

	if (internalKey == NULL)
		return NULL;

	sprintf(internalKey, "%s_%s", this->super->super->name, this->super->version);
	/*strcpy(internalKey, this->super->super->name);
	strcat(internalKey, "/");
	strcat(internalKey, this->super->version);*/

	return internalKey;
}

char* GroupType_InternalGetKey(GroupType* const this)
{
	char* name;

	name = malloc(sizeof(char) * (strlen("GroupType") + 1));
	strcpy(name, "GroupType");
	
	return name;
}

void deletePoly_GroupType(TypeDefinition* const this)
{
	GroupType* pGroupTypeObj;
	pGroupTypeObj = this->pDerivedObj;
	/*destroy derived obj*/
	free(pGroupTypeObj);
	/*destroy base Obj*/
	delete_TypeDefinition(this);
}
void delete_GroupType(GroupType* const this)
{
	/* destroy base object */
	delete_TypeDefinition(this->super);
	/* destroy data memebers */
	free(this);
}

void GroupType_VisitAttributes(void* const this, char* parent, Visitor* visitor)
{
	char path[256];
	memset(&path[0], 0, sizeof(path));

	/*sprintf(path, "%s", parent, ((GroupType*)(this))->super->super->name);*/

	/*sprintf(path, "%s\\name", parent);
	visitor->action(path, STRING, ((GroupType*)(this))->super->super->name);*/
	TypeDefinition_VisitAttributes(((TypeDefinition*)(this)), parent, visitor);
}