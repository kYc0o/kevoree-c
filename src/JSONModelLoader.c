#include "JSONModelLoader.h"
#include "DefaultFactorykevoree.h"
#include "kevoree.h"
#include "json.h"
#include "jsonparse.h"

char strJson[100];
char jsonType;

void JSONKevDeserializer(struct jsonparse_state *jsonState, char _jsonType, void *object)
{
	/*while(jsonparse_has_next(jsonState))
	{*/
	/*jsonparse_next(&jsonState);*/


	switch(_jsonType)
	{
	/*case JSON_TYPE_ARRAY:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_ARRAY\n\t%s\n", strJson);
			break;*/

	case JSON_TYPE_OBJECT:
		/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
		printf("JSON_TYPE_OBJECT\n\t{\n");
		while((jsonType = jsonparse_next(jsonState))!= '}')
		{
			/*printf("JSON_TYPE_OBJECT\n\t{\n");*/
			switch(jsonType)
			{
			case JSON_TYPE_PAIR_NAME:
				jsonparse_copy_value(jsonState, strJson, sizeof strJson);
				printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
				if(!strcmp(strJson, "eClass"))
				{
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_PAIR:
						jsonparse_copy_value(jsonState, strJson, sizeof strJson);
						printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
						switch(jsonparse_next(jsonState))
						{
						case JSON_TYPE_STRING:
							jsonparse_copy_value(jsonState, strJson, sizeof strJson);
							printf("%s\n", strJson);
							if(!strcmp(strJson, "org.kevoree.ContainerRoot"))
							{
								ContainerRoot *model = (ContainerRoot*)object;
								model = createContainerRoot(jsonState, jsonparse_next(jsonState));
							}
							else if(!strcmp(strJson, "org.kevoree.ContainerNode"))
							{
								ContainerNode *node = createContainerNode(jsonState, jsonparse_next(jsonState));
								if(object != NULL)
									(ContainerRoot*)object->
							}
							break;

						case JSON_TYPE_ARRAY:
							/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
							printf("[\n");
							while((jsonType = jsonparse_next(jsonState))!= ']')
							{
								switch(jsonType)
								{
								case JSON_TYPE_OBJECT:
									JSONKevDeserializer(jsonState, jsonType, NULL);
									break;

								case JSON_TYPE_STRING:
									jsonparse_copy_value(jsonState, strJson, sizeof strJson);
									printf("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_INT:
									jsonparse_copy_value(jsonState, strJson, sizeof strJson);
									printf("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_NUMBER:
									jsonparse_copy_value(jsonState, strJson, sizeof strJson);
									printf("\t\t\t\t%s\n", strJson);
									break;
								}
							}
							printf("\t\t\t]\n");
							break;


						default:
							printf("ERROR!! JSON_TYPE_STRING expected!\n\n");
							break;
						}
					}
					break;
				}
			}
		}
		break;

		/*case JSON_TYPE_PAIR:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_PAIR\n\t%s\n", strJson);
			break;

		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_PAIR_NAME\n\t%s\n", strJson);
			break;

		case JSON_TYPE_STRING:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_STRING\n\t%s\n", strJson);
			break;

		case JSON_TYPE_INT:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_INT\n\t%s\n", strJson);
			break;

		case JSON_TYPE_NUMBER:
			jsonparse_copy_value(jsonState, strJson, sizeof strJson);
			printf("JSON_TYPE_NUMBER\n\t%s\n", strJson);
			break;*/

	case JSON_TYPE_ERROR:
		printf("JSON_TYPE_ERROR\n\t(empty)\n");
		break;

		/*case ']':
			printf("JSON_END_OF_ARRAY\n");
			break;*/

	case '}':
		/*printf("JSON_END_OF_OBJECT\n");*/
		printf("}\n");
		break;
	}
	printf("\t}\n");
	/*}*/
}
