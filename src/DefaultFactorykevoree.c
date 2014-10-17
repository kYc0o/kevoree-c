#include "DefaultFactorykevoree.h"
#include "kevoree.h"
#include "JSONModelLoader.h"
#include "json.h"
#include "jsonparse.h"

#define DEBUG 1
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

ContainerRoot *createContainerRoot(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	ContainerRoot *obj = new_ContainerRoot();

	while((jsonType = jsonparse_next(jsonState)) != JSON_TYPE_OBJECT)
	{
		printf("root: jsonType->%c\n", jsonType);
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						strcpy(obj->generated_KMF_ID, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	return obj;
}

ContainerNode *createContainerNode(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root)
{
	printf("%s\n", strJson);

	ContainerNode *obj = new_ContainerNode();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						printf("%s -> %s\n", strJson, obj->super->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "metaData"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						printf("%s -> %s\n", strJson, obj->super->metaData);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "started"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->started = atoi(strJson);
						printf("%s -> %d\n", strJson, obj->super->started);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "components"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.ComponentInstance"))
												{
													ComponentInstance *component = createComponentInstance(jsonState, jsonType, strJson, root);
													if(component != NULL)
														obj->AddComponents(obj, component);
													else
														printf("Component cannot be added!\n");
												}
												break;
											}
											break;
										}
									}
									else
									{
										printf("Invalid object!\n");
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
				}
			}
			else if(!strcmp(strJson, "hosts"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
							JSONKevDeserializer(jsonState, jsonType, NULL);
							break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
				}
				break;
			}
			else if(!strcmp(strJson, "host"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
							 * TODO add host references
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
				}
				break;
			}
			else if(!strcmp(strJson, "groups"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
							 * TODO add hosts references
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								Group *group = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								printf("Looking for Group %s\n", id);

								group = root->FindGroupsByID(root, id);

								if(group != NULL)
								{
									printf("Group %s found!\n", id);
									obj->AddGroups(obj, group);
								}
								else
								{
									printf("Group %s not found!\n", id);/*, creating a new one...\n", id);*/
									/*group = new_Group();
									if(group != NULL)
									{
										group->super->super->name = malloc(sizeof(char) * strlen(id) + 1);
										strcpy(group->super->super->name, id);
										printf("Group created with id: %s\n", group->super->super->name);
										obj->AddGroups(obj, group);
										root->AddGroups(root, group);
									}
									else
									{
										printf("Cannot create Group reference\n");
									}*/
								}
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
				}
				break;
			}
			else if(!strcmp(strJson, "networkInformation"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.NetworkInfo"))
												{
													NetworkInfo *netInfo = createNetworkInfo(jsonState, jsonType, strJson);
													if(netInfo != NULL)
														obj->AddNetworkInformation(obj, netInfo);
													else
														printf("NetworkInfo cannot be added!\n");
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "typeDefinition"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								TypeDefinition *typdef = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								printf("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									printf("TypeDefinition %s found!\n", id);
									obj->super->AddTypeDefinition(obj->super, typdef);
								}
								else
								{
									printf("TypeDefinition %s not found!\n", id);
									/*typdef = new_TypeDefinition();
									if(typdef != NULL)
									{
										char *nextToken;
										nextToken = strtok(id, "/");

										typdef->super->name = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(typdef->super->name, nextToken);

										nextToken = strtok(NULL, "/");

										typdef->version = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(typdef->version, nextToken);

										printf("TypeDefinition created with id: %s/%s\n", typdef->super->name, typdef->version);
										obj->super->AddTypeDefinition(obj->super, typdef);
										root->AddTypeDefinitions(root, typdef);
									}
									else
									{
										printf("Cannot create TypeDefinition reference\n");
									}*/
								}
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "dictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
											JSONKevDeserializer(jsonState, jsonType, NULL);
											break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "fragmentDictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.FragmentDictionary"))
												{
													FragmentDictionary *fragdic = createFragmentDictionary(jsonState, jsonType, strJson);
													if(fragdic != NULL)
													{
														Instance *inst = obj->super;
														inst->AddFragmentDictionary(inst, fragdic);
													}
													else
													{
														printf("DictionaryValue cannot be created!\n");
													}
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
		}
	}
	printf("\t}\n");
	return obj;
}

NetworkInfo *createNetworkInfo(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	printf("%s\n", strJson);
	NetworkInfo *obj = new_NetworkInfo();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						printf("%s -> %s\n", strJson, obj->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "values"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.NetworkProperty"))
												{
													NetworkProperty *netprop = createNetworkProperty(jsonState, jsonType, strJson);
													obj->AddValues(obj, netprop);
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	return obj;
}

NetworkProperty *createNetworkProperty(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	printf("%s\n", strJson);

	NetworkProperty *obj = new_NetworkProperty();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						printf("%s -> %s\n", strJson, obj->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "value"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->value = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->value, strJson);
						printf("%s -> %s\n", strJson, obj->value);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	return obj;
}

ComponentInstance * createComponentInstance(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root)
{
	printf("%s\n", strJson);

	ComponentInstance *obj = new_ComponentInstance();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						printf("%s -> %s\n", strJson, obj->super->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "metaData"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						printf("%s -> %s\n", strJson, obj->super->metaData);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "started"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->started = atoi(strJson);
						printf("%s -> %d\n", strJson, obj->super->started);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "typeDefinition"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
											JSONKevDeserializer(jsonState, jsonType, NULL);
											break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								TypeDefinition *typdef = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								printf("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									printf("TypeDefinition %s found!\n", id);
									obj->super->AddTypeDefinition(obj->super, typdef);
								}
								else
								{
									printf("TypeDefinition %s not found!\n", id);
									/*typdef = new_TypeDefinition();
									if(typdef != NULL)
									{
										char *nextToken;
										nextToken = strtok(id, "/");

										typdef->super->name = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(typdef->super->name, nextToken);

										nextToken = strtok(NULL, "/");

										typdef->version = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(typdef->version, nextToken);

										printf("TypeDefinition created with id: %s/%s\n", typdef->super->name, typdef->version);
										obj->super->AddTypeDefinition(obj->super, typdef);
										root->AddTypeDefinitions(root, typdef);
									}
									else
									{
										printf("Cannot create TypeDefinition reference\n");
									}*/
								}
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "dictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
														JSONKevDeserializer(jsonState, jsonType, NULL);
														break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "fragmentDictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.FragmentDictionary"))
												{
													FragmentDictionary *fragdic = createFragmentDictionary(jsonState, jsonType, strJson);
													if(fragdic != NULL)
													{
														Instance *inst = obj->super;
														inst->AddFragmentDictionary(inst, fragdic);
													}
													else
													{
														printf("DictionaryValue cannot be created!\n");
													}
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "provided"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "required"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	return obj;
}

Group * createGroup(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root)
{
	printf("%s\n", strJson);

	Group *obj = new_Group();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						printf("%s -> %s\n", strJson, obj->super->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "metaData"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						printf("%s -> %s\n", strJson, obj->super->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "started"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->started = atoi(strJson);
						printf("%s -> %d\n", strJson, obj->super->started);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "subNodes"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																					JSONKevDeserializer(jsonState, jsonType, NULL);
																					break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								ContainerNode *node = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								printf("Looking for SubNode %s\n", id);

								node = root->FindNodesByID(root, id);

								if(node != NULL)
								{
									printf("SubNode %d found!\n", id);
									obj->AddSubNodes(obj, node);
								}
								else
								{
									printf("Node %s not found!\n", id);
									/*node = new_ContainerNode();
									if(node != NULL)
									{
										node->super->super->name = malloc(sizeof(char) * strlen(id) + 1);
										strcpy(node->super->super->name, id);

										printf("Node created with id: %d", node->super->super->name)
										obj->AddSubNodes(obj, node);
									}
									else
									{
										printf("Cannot create SubNode reference\n");
									}*/
								}
								/*printf("SubNode cannot be found!\n");*/
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "dictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
															JSONKevDeserializer(jsonState, jsonType, NULL);
															break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "fragmentDictionary"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.FragmentDictionary"))
												{
													FragmentDictionary *fragdic = createFragmentDictionary(jsonState, jsonType, strJson);
													if(fragdic != NULL)
													{
														Instance *inst = obj->super;
														inst->AddFragmentDictionary(inst, fragdic);
													}
													else
													{
														printf("DictionaryValue cannot be created!\n");
													}
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	return obj;
}

FragmentDictionary *createFragmentDictionary(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	printf("%s\n", strJson);
	FragmentDictionary *obj = new_FragmentDictionary();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						strcpy(obj->super->generated_KMF_ID, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->name, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "values"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryValue"))
												{
													DictionaryValue *dicval = createDictionaryValue(jsonState, jsonType, strJson);
													if(dicval != NULL)
													{
														Dictionary *dico = obj->super;
														dico->AddValues(dico, dicval);
													}
													else
													{
														printf("DictionaryValue cannot be created!\n");
													}
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
		}
	}
	printf("\t}\n");
	return obj;
}

DictionaryValue *createDictionaryValue(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	printf("%s\n", strJson);

	DictionaryValue *obj = new_DictionaryValue();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->name, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "value"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->value = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->value, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	return obj;
}

TypeDefinition* createTypeDefinition(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root)
{
	printf("%s\n", strJson);

	TypeDefinition *obj = NULL;
	printf("%X\n", obj);

	if(!strcmp(strJson, "org.kevoree.NodeType"))
	{
		obj = newPoly_NodeType();
	}
	else if(!strcmp(strJson, "org.kevoree.GroupType"))
	{
		obj = newPoly_GroupType();
	}
	else if(!strcmp(strJson, "org.kevoree.ComponentType"))
	{
		obj = newPoly_ComponentType();
	}
	else
	{
		printf("TypeDefinition %s not supported!\n", strJson);
		return NULL;
	}


	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						printf("%s -> %s\n", strJson, obj->super->name);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "version"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->version = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->version, strJson);
						printf("%s -> %s\n", strJson, obj->version);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "factoryBean"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->factoryBean = malloc(sizeof(char) * strlen(strJson) + 1); /*atoi(strJson);*/
						strcpy(obj->factoryBean, strJson);
						printf("%s -> %s\n", strJson, obj->factoryBean);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "bean"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->bean = malloc(sizeof(char) * strlen(strJson) + 1); /*atoi(strJson);*/
						strcpy(obj->bean, strJson);
						printf("%s -> %s\n", strJson, obj->bean);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "abstract"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->abstract = atoi(strJson);
						printf("%s -> %d\n", strJson, obj->abstract);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "deployUnit"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
											JSONKevDeserializer(jsonState, jsonType, NULL);
											break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								DeployUnit *du = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								printf("Looking for DeployUnit %s\n", id);

								du = root->FindDeployUnitsByID(root, id);

								if(du != NULL)
								{
									printf("DeployUnit %s found!\n", id);
									obj->AddDeployUnit(obj, du);
								}
								else
								{
									printf("DeployUnit %s not found!\n", id);
									/*du = new_DeployUnit();
									if(du != NULL)
									{
										char *nextToken;
										nextToken = strtok(id, "/");

										du->groupName = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(du->groupName, nextToken);

										nextToken = strtok(NULL, "/");

										du->hashcode = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(du->hashcode, nextToken);

										nextToken = strtok(NULL, "/");

										du->super->name = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(du->super->name, nextToken);

										nextToken = strtok(NULL, "/");

										du->version = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(du->version, nextToken);

										obj->AddDeployUnit(obj, du);
									}
									else
									{
										printf("Cannot create TypeDefinition reference\n");
									}*/
								}
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "superTypes"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
														JSONKevDeserializer(jsonState, jsonType, NULL);
														break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "dictionaryType"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryType"))
												{
													DictionaryType *dictype = createDictionaryType(jsonState, jsonType, strJson);
													obj->AddDictionaryType(obj, dictype);
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "required"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "provided"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	printf("%X\n", obj);
	return obj;
}

DictionaryType *createDictionaryType(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	printf("%s\n", strJson);

	DictionaryType *obj = new_DictionaryType();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						strcpy(obj->generated_KMF_ID, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "attributes"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								printf("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryAttribute"))
												{
													DictionaryAttribute *dicattr = createDictionaryAttribute(jsonState, jsonType, strJson);
													obj->AddAttributes(obj, dicattr);
												}
												break;
											}
											break;
										}
									}
									break;
								}
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	return obj;
}

DictionaryAttribute *createDictionaryAttribute(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	printf("%s\n", strJson);

	DictionaryAttribute *obj = new_DictionaryAttribute();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "optional"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->optional = atoi(strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "state"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->state = atoi(strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "datatype"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->datatype = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->datatype, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "fragmentDependant"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->fragmentDependant = atoi(strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "datatype"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->defaultValue = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->defaultValue, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	return obj;
}

/*NodeNetwork* createNodeNetwork(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	NodeNetwork *ptr = (NodeNetwork*)malloc(sizeof(NodeNetwork));

	if(ptr == NULL)
	{
		printf("FATAL can't allocate NodeNetwork \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptNodeNetwork;
	}

	return ptr;
}*/

TypeLibrary *createTypeLibrary(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root)
{
	printf("%s\n", strJson);

	TypeLibrary *obj = new_TypeLibrary();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "subTypes"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						printf("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																					JSONKevDeserializer(jsonState, jsonType, NULL);
																					break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								TypeDefinition *typdef = NULL;
								char id[30];
								sscanf(strJson, "%*[^[][%[^]]", id);
								printf("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									printf("TypeDefinition %s found!\n", id);
									obj->AddSubTypes(obj, typdef);
								}
								else
								{
									printf("TypeDefinition %s not found!\n", id);
									/*typdef = new_TypeDefinition();
									if(typdef != NULL)
									{
										char *nextToken;
										nextToken = strtok(id, "/");

										typdef->super->name = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(typdef->super->name, nextToken);

										nextToken = strtok(NULL, "/");

										typdef->version = malloc(sizeof(char) * strlen(nextToken) + 1);
										strcpy(typdef->version, nextToken);

										obj->AddSubTypes(obj, typdef);
									}
									else
									{
										printf("Cannot create TypeDefinition reference\n");
									}*/
								}
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								printf("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						printf("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	return obj;
}

DeployUnit * createDeployUnit(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root)
{
	printf("%s\n", strJson);

	DeployUnit *obj = new_DeployUnit();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			printf("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "groupName"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->groupName = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->groupName, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "version"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						/*obj->state = atoi(strJson);*/
						obj->version = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->version, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "url"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->url = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->url, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "hashcode"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->hashcode = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->hashcode, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "type"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					printf("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->type = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->type, strJson);
						printf("%s\n", strJson);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	printf("\t}\n");
	return obj;
}
