#include "Visitor.h"

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

