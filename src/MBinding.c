#include <string.h>
#include "MBinding.h"
#include "Channel.h"
#include "Port.h"
#include "ContainerRoot.h"
#include "Visitor.h"
#include "MBinding.h"
#include "tools.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

MBinding* new_MBinding(void)
{
	MBinding* pObj = NULL;
	/* Allocating memory */
	pObj = (MBinding*)malloc(sizeof(MBinding));

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

	pObj->internalGetKey = MBinding_internalGetKey;
	pObj->metaClassName = MBinding_metaClassName;
	pObj->Delete = delete_MBinding;
	pObj->VisitAttributes = MBinding_VisitAttributes;
	pObj->VisitPathAttributes = MBinding_VisitPathAttributes;
	pObj->VisitReferences = MBinding_VisitReferences;
	pObj->VisitPathReferences = MBinding_VisitPathReferences;
	pObj->FindByPath = MBinding_FindByPath;

	return pObj;
}

void delete_MBinding(void * const this)
{
	if(this != NULL)
	{
		/*
		free(((MBinding*)this)->generated_KMF_ID);
		free(((MBinding*)this)->port);
		free(((MBinding*)this)->channel);
		*/
		free(((MBinding*)this)->eContainer);
		free(this);
		/*this = NULL;*/
	}
}

char* MBinding_metaClassName(void * const this)
{
	char *name;

	name = malloc(sizeof(char) * (strlen("MBinding")) + 1);
	if(name != NULL)
		strcpy(name, "MBinding");
	else
		return NULL;

	return name;
}

char* MBinding_internalGetKey(void * const this)
{
	MBinding *pObj = (MBinding*)this;
	return pObj->generated_KMF_ID;
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

void MBinding_VisitAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
		cClass = malloc(sizeof(char) * (strlen("org.kevoree.") + strlen(((MBinding*)this)->metaClassName((MBinding*)this))) + 1);
		sprintf(cClass, "org.kevoree.%s", ((MBinding*)this)->metaClassName((MBinding*)this));
		sprintf(path,"eClass");
		visitor->action(path, STRING, cClass);
		visitor->action(NULL, COLON, NULL);
		free(cClass);

		sprintf(path, "generated_KMF_ID");
		visitor->action(path, STRING, ((MBinding*)(this))->generated_KMF_ID);
		visitor->action(NULL, COLON, NULL);
	}
	else
	{
		sprintf(path, "generated_KMF_ID");
		visitor->action(path, STRING, ((MBinding*)(this))->generated_KMF_ID);
		visitor->action(NULL, COLON, NULL);
	}

}

void MBinding_VisitPathAttributes(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	char path[256];
	char *cClass = NULL;
	memset(&path[0], 0, sizeof(path));

	if(recursive)
	{
		sprintf(path, "%s\\generated_KMF_ID", parent);
		visitor->action(path, STRING, ((MBinding*)(this))->generated_KMF_ID);
	} else {
		sprintf(path, "%s\\generated_KMF_ID", parent);
		visitor->action(path, REFERENCE, ((MBinding*)(this))->generated_KMF_ID);
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
			sprintf(path, "port[%s]", ((MBinding*)(this))->port->internalGetKey(((MBinding*)(this))->port));
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
			sprintf(path, "hub[%s]", ((MBinding*)(this))->channel->internalGetKey(((MBinding*)(this))->channel));
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

void MBinding_VisitPathReferences(void *const this, char *parent, Visitor *visitor, bool recursive)
{
	if(recursive)
	{
		char path[256];
		memset(&path[0], 0, sizeof(path));

		if(((MBinding*)(this))->port != NULL)
		{
			sprintf(path, "%s/%s\\port", parent, ((MBinding*)(this))->port->path);
			visitor->action(path, REFERENCE, parent);
		}

		if(((MBinding*)(this))->channel != NULL)
		{
			sprintf(path, "%s/%s\\hub", parent, ((MBinding*)(this))->channel->path);
			visitor->action(path, REFERENCE, parent);
		}
	}
}

void* MBinding_FindByPath(char* attribute, void * const this)
{
	MBinding *pObj = (MBinding*)this;
	/* Local attributes */
	if(!strcmp("generated_KMF_ID", attribute))
	{
		return pObj->generated_KMF_ID;
	}
	/* Local references */
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

		if(!strcmp("port", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->port;
			}
			else
			{
				return pObj->port->FindByPath(nextPath, pObj->port);
			}
		}
		else if(!strcmp("channel", obj))
		{
			free(obj);
			if(nextAttribute == NULL)
			{
				return pObj->channel;
			}
			else
			{
				return pObj->channel->FindByPath(nextPath, pObj->channel);
			}
		}
		else
		{
			free(obj);
			PRINTF("Wrong attribute or reference\n");
			return NULL;
		}
	}
}
