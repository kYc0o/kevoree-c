#include "Visitor.h"
#include "ContainerRoot.h"
#include "ModelTrace.h"
#include "list.h"

char buffer[250];

Visitor *new_Visitor(ContainerRoot *new_model, ContainerRoot *current_model)
{
	Visitor *pVisitObj = malloc(sizeof(Visitor));

	if(pVisitObj == NULL)
	{
		return NULL;
	}

	pVisitObj->new_model = new_model;
	pVisitObj->current_model = current_model;
	pVisitObj->visit_list_list = NULL;
	pVisitObj->visit_list = (list_t)&(pVisitObj->visit_list_list);
	list_init(pVisitObj->visit_list);

	pVisitObj->store = Visitor_store;
	pVisitObj->printPaths = Visitor_printPaths;
	pVisitObj->print = Visitor_print;
	pVisitObj->diff = Visitor_diff;
	pVisitObj->delete = delete_Visitor;

	return pVisitObj;
}

void delete_Visitor(void *const this)
{
	if(this != NULL)
	{
		Visitor *v = this;
		int length = list_length(v->visit_list);
		int i;

		for (i = 0; i < length; ++i) {
			list_chop(v->visit_list);
		}

		free(this);
	}
}


void Visitor_store(char *path, Type type, void *value)
{
	/*switch(type)
	{
	case STRING:
		sprintf(buffer, "\"%s\" : \"%s\"", path, (char*)value);
		write_to_file(buffer);
		break;

	case STRREF:
		sprintf(buffer, "\"%s\"", path);
		write_to_file(buffer);
		break;

	case BOOL:
		sprintf(buffer, "\"%s\" : \"%d\"", path, (bool)value);
		write_to_file(buffer);
		break;

	case INTEGER:
		sprintf(buffer, "\"%s\" : \"%d\"", path, (int)value);
		write_to_file(buffer);
		break;

	case BRACKET:
		sprintf(buffer, "{\n");
		write_to_file(buffer);
		break;

	case SQBRACKET:
		sprintf(buffer, "\"%s\" : [\n", path);
		write_to_file(buffer);
		break;

	case CLOSEBRACKET:
		sprintf(buffer, "}\n");
		write_to_file(buffer);
		break;

	case CLOSESQBRACKET:
		sprintf(buffer, "]\n");
		write_to_file(buffer);
		break;

	case CLOSEBRACKETCOLON:
		sprintf(buffer, "},\n");
		write_to_file(buffer);
		break;

	case CLOSESQBRACKETCOLON:
		sprintf(buffer, "],\n");
		write_to_file(buffer);
		break;

	case COLON:
		sprintf(buffer, ",\n");
		write_to_file(buffer);
		break;

	case RETURN:
		sprintf(buffer, "\n");
		write_to_file(buffer);
		break;
	}*/
}

void Visitor_printPaths(char *path, Type type, void *value)
{
	/*switch(type)
	{
	case STRING:
		printf("path = %s  value = %s\n",path,(char*)value);
		break;

	case BOOL:
	case INTEGER:
		printf("path = %s  value = %d\n", path, (int)value);
		break;

	case STRREF:
	case BRACKET:
	case SQBRACKET:
	case CLOSEBRACKET:
	case CLOSESQBRACKET:
	case CLOSEBRACKETCOLON:
	case CLOSESQBRACKETCOLON:
	case COLON:
	case RETURN:
		printf("Type non valid!\n");
		break;
	}*/
}

void Visitor_print(char *path, Type type, void *value)
{
	/*switch(type)
	{
	case STRING:
		printf("\"%s\" : \"%s\"", path, (char*)value);
		break;

	case STRREF:
		printf("\"%s\"", path);
		break;

	case BOOL:
	case INTEGER:
		printf("\"%s\" : \"%d\"", path, (int)value);
		break;

	case BRACKET:
		printf("{\n");
		break;

	case SQBRACKET:
		printf("\"%s\" : [\n", path);
		break;

	case CLOSEBRACKET:
		printf("}\n");
		break;

	case CLOSESQBRACKET:
		printf("]\n");
		break;

	case CLOSEBRACKETCOLON:
		printf("},\n");
		break;

	case CLOSESQBRACKETCOLON:
		printf("],\n");
		break;

	case COLON:
		printf(",\n");
		break;

	case RETURN:
		printf("\n");
		break;
	}*/
}

/*
ModelTrace *Visitor_diff(Visitor *const this, char *path, Type type, void *value);

char* buffer = NULL;


void actionprintf(char *path, Type type, void* value)
{
	switch(type)
	{
	case STRING:
		printf("\"%s\" : \"%s\"", path, (char*)value);
		break;

	case INTEGER:
		printf("\"%s\" : \"%d\"", path, (int)value);
		break;

	case STRREF:
		printf("\"%s\"", path);
		break;

	case BOOL:
		if((int)value)
			printf("\"%s\" : \"%s\"", path, "true");
		else
			printf("\"%s\" : \"%s\"", path, "false");
		break;

	case BRACKET:
		printf("{\n");
		break;

	case SQBRACKET:
		printf("\"%s\" : [\n", path);
		break;

	case CLOSEBRACKET:
		printf("}\n");
		break;

	case CLOSESQBRACKET:
		printf("]\n");
		break;

	case CLOSEBRACKETCOLON:
		printf("},\n");
		break;

	case CLOSESQBRACKETCOLON:
		printf("],\n");
		break;

	case COLON:
		printf(",\n");
		break;

	case RETURN:
		printf("\n");
	}
}
*/
void Visitor_diff(Visitor *const this, char *path, Type type, void *value)
{

}
