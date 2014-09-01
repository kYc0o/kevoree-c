#include "Visitor.h"

char* buffer = NULL;

void actionprintf(char *path, Type type, void* value)
{
	switch(type)
	{
		case STRING:
			printf("\"%s\" : \"%s\"", path, (char*)value);
			break;

		case STRREF:
			printf("\"%s\"", path);
			break;

		case BOOL:
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
	}
}
