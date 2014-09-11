#include <string.h>
#include "MBinding.h"
#include "Channel.h"
#include "Port.h"
#include "ContainerRoot.h"
#include "Visitor.h"
#include "MBinding.h"

MBinding* new_MBinding(void)
{
	MBinding* pObj = NULL;
	/* Allocating memory */
	pObj = (MBinding*)my_malloc(sizeof(MBinding));

	if (pObj == NULL)
	{
		return NULL;
	}

	memset(&pObj->generated_KMF_ID[0], 0, sizeof(pObj->generated_KMF_ID));
	rand_str(pObj->generated_KMF_ID, 8);
	
	pObj->port = NULL;
	pObj->channel = NULL;
	pObj->eContainer = NULL;
	
	pObj->AddPort = MBinding_AddPort;
	pObj->AddHub = MBinding_AddHub;
	pObj->RemoveHub = MBinding_RemoveHub;
	pObj->RemovePort = MBinding_RemovePort;

	pObj->InternalGetKey = MBinding_InternalGetKey;
	pObj->MetaClassName = MBinding_MetaClassName;
	pObj->Delete = delete_MBinding;
	pObj->VisitAttributes = MBinding_VisitAttributes;
	pObj->VisitReferences = MBinding_VisitReferences;
	pObj->FindByPath = MBinding_FindByPath;
	
	return pObj;
}

void delete_MBinding(void* const this)
{
	if(this != NULL)
	{
		free(((MBinding*)this)->generated_KMF_ID);
		free(((MBinding*)this)->port);
		free(((MBinding*)this)->channel);
		free(((MBinding*)this)->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

char* MBinding_MetaClassName(MBinding* const this)
{
	char *name;

	name = my_malloc(sizeof(char) * (strlen("MBinding")) + 1);
	if(name != NULL)
		strcpy(name, "MBinding");
	else
		return NULL;
	
	return name;
}

char* MBinding_InternalGetKey(MBinding* const this)
{
	return this->generated_KMF_ID;
}

void MBinding_AddPort(MBinding* const this, Port* ptr)
{
	this->port = ptr;
}

void MBinding_AddHub(MBinding* const this, Channel* ptr)
{
	this->channel = ptr;
}

void MBinding_RemovePort(MBinding* const this, Port* ptr)
{
	free(ptr);
	this->port = NULL;
}

void MBinding_RemoveHub(MBinding* const this, Channel* ptr)
{
	free(ptr);
	this->channel = NULL;
}

void MBinding_VisitAttributes(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
		/*sprintf(path,"%s\\cClass", parent);*/
		cClass = my_malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((MBinding*)this)->MetaClassName((MBinding*)this))) + 1);
		sprintf(cClass, "org.kevoree.%s", ((MBinding*)this)->MetaClassName((MBinding*)this));
		sprintf(path,"eClass");
		/*cClass = ((MBinding*)this)->MetaClassName((MBinding*)this);*/
		visitor->action(path, STRING, cClass);
		visitor->action(NULL, COLON, NULL);
		/*free(cClass);*/
		str_free(cClass);

		/*sprintf(path, "%s\\generated_KMF_ID", parent);*/
		sprintf(path, "generated_KMF_ID");
		visitor->action(path, STRING, ((MBinding*)(this))->generated_KMF_ID);
		visitor->action(NULL, COLON, NULL);
	}
	else
	{
		/*sprintf(path, "%s\\generated_KMF_ID", parent);*/
		sprintf(path, "generated_KMF_ID");
		visitor->action(path, STRING, ((MBinding*)(this))->generated_KMF_ID);
		visitor->action(NULL, COLON, NULL);
	}

}

void MBinding_VisitReferences(void* const this, char* parent, Visitor* visitor, bool recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		if(((MBinding*)(this))->port != NULL)
		{
			visitor->action("port", SQBRACKET, NULL);
			/*sprintf(path, "%s/port[%s]", parent, ((MBinding*)(this))->port->InternalGetKey(((MBinding*)(this))->port));
			((MBinding*)(this))->port->VisitAttributes(((MBinding*)(this))->port, path, visitor, 0);*/
			sprintf(path, "port[%s]", ((MBinding*)(this))->port->InternalGetKey(((MBinding*)(this))->port));
			/*((MBinding*)(this))->port->VisitReferences(((MBinding*)(this))->port, path, visitor);*/
			visitor->action(path, STRREF, NULL);
			visitor->action(NULL, RETURN, NULL);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}
		else
		{
			visitor->action("port", SQBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKETCOLON, NULL);
		}

		if(((MBinding*)(this))->channel != NULL)
		{
			visitor->action("hub", SQBRACKET, NULL);
			/*sprintf(path, "%s/hub[%s]", parent, ((MBinding*)(this))->channel->InternalGetKey(((MBinding*)(this))->channel));
			((MBinding*)(this))->channel->VisitAttributes(((MBinding*)(this))->channel, path, visitor, 0);*/
			sprintf(path, "hub[%s]", ((MBinding*)(this))->channel->InternalGetKey(((MBinding*)(this))->channel));
			/*((MBinding*)(this))->channel->VisitReferences(((MBinding*)(this))->channel, path, visitor);*/
			visitor->action(path, STRREF, NULL);
			visitor->action(NULL, RETURN, NULL);
			visitor->action(NULL, CLOSESQBRACKET, NULL);
		}
		else
		{
			visitor->action("hub", SQBRACKET, NULL);
			visitor->action(NULL, CLOSESQBRACKET, NULL);
		}
	}
}

void* MBinding_FindByPath(char* attribute, MBinding* const this)
{
	/* Local attributes */
	if(!strcmp("generated_KMF_ID", attribute))
	{
		return this->generated_KMF_ID;
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
			
			if(strchr(attribute,'\\') != NULL)
			{
				nextAttribute = strtok(NULL, "\\");
				sprintf(nextAttribute, "%s\\%s", nextAttribute, strtok(NULL, "\\"));
			}
			else
			{
				nextAttribute = strtok(NULL, "\\");
			}
		}
		else
		{
			pch = path;
			nextAttribute = strtok(pch, "\\");
			nextAttribute = strtok(NULL, "\\");
		}

		int i = indexOf(pch,"[") + 2;
		int y = lastIndexOf(pch,"]") - i + 1;

		char* relationName = (char*)Substring(pch, 0, i - 2);
		char* queryID = (char*)Substring(pch, i, y);

		if(!strcmp("port", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->port;
			}
			else
			{
				return this->port->FindByPath(nextAttribute, this->port);
			}
		}
		else if(!strcmp("channel", relationName))
		{
			if(nextAttribute == NULL)
			{
				return this->channel;
			}
			else
			{
				return this->channel->FindByPath(nextAttribute, this->channel);
			}
		}
		else
		{
			printf("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
