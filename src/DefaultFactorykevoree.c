#include <string.h>
#include "DefaultFactorykevoree.h"
#include "kevoree.h"
#include "JSONModelLoader.h"
#include "json.h"
#include "jsonparse.h"

#define DEBUG 0
#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

/*KMFFactory *new_KMFFactory()
{
	KMFFactory *pKMFFactoryObj = NULL;

	pKMFFactoryObj = (ContainerRoot*)malloc(sizeof(KMFFactory));

	if(pKMFFactoryObj == NULL)
	{
		return NULL;
	}

	pKMFFactoryObj->createContainerNode = createContainerNode;
	pKMFFactoryObj->createComponentInstance = createComponentInstance;
	pKMFFactoryObj->createGroup = createGroup;
	pKMFFactoryObj->createTypeDefinition = createTypeDefinition;


}*/

ContainerNode *createContainerNode(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);

	ContainerNode *obj = new_ContainerNode();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->metaData);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						if (!strcmp("false", strJson)) {
							obj->super->started = false;
						} else if (!strcmp("true", strJson)) {
							obj->super->started = true;
						} else {
							obj->super->started = false;
						}
						PRINTF("%s -> %d\n", strJson, obj->super->started);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.ComponentInstance"))
												{
													if (obj->path == NULL) {
														root->AddNodes(root, obj);
													}
													ComponentInstance *component = createComponentInstance(jsonState, jsonType, strJson, root, obj, loader);
													if(component != NULL)
														obj->AddComponents(obj, component);
													else
														PRINTF("Component cannot be added!\n");
												}
												break;
											}
											break;
										}
									}
									else
									{
										PRINTF("Invalid object!\n");
									}
									break;
								}
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
							JSONKevDeserializer(jsonState, jsonType, NULL);
							break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "host"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
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
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "groups"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
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
								char id[150];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for Group %s\n", id);

								group = root->FindGroupsByID(root, id);

								if(group != NULL)
								{
									PRINTF("Group %s found!\n", id);
									obj->AddGroups(obj, group);
								}
								else
								{
									PRINTF("Group %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("nodes[]") * strlen(obj->internalGetKey(obj)) + 1);
									sprintf(objId, "nodes[%s]", obj->internalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "networkInformation"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.NetworkInfo"))
												{
													if (obj->path == NULL) {
														root->AddNodes(root, obj);
													}
													NetworkInfo *netInfo = createNetworkInfo(jsonState, jsonType, strJson, obj);
													if(netInfo != NULL)
														obj->AddNetworkInformation(obj, netInfo);
													else
														PRINTF("NetworkInfo cannot be added!\n");
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
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
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
								char id[150];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									PRINTF("TypeDefinition %s found!\n", id);
									obj->super->AddTypeDefinition(obj->super, typdef);
								}
								else
								{
									PRINTF("TypeDefinition %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("nodes[]") * strlen(obj->internalGetKey(obj)) + 1);
									sprintf(objId, "nodes[%s]", obj->internalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.Dictionary"))
												{
													if (obj->super->path == NULL) {
														root->AddNodes(root, obj);
													}
													Dictionary *dic = createDictionary(jsonState, jsonType, strJson, obj->super);
													if (dic != NULL) {
														obj->super->AddDictionary(obj->super, dic);
													} else {
														PRINTF("ERROR: Dictionary cannot be added!\n");
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

								case JSON_TYPE_STRING:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_INT:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_NUMBER:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.FragmentDictionary"))
												{
													FragmentDictionary *fragdic = createFragmentDictionary(jsonState, jsonType, strJson, obj->super);
													if (fragdic != NULL) {
														Instance *inst = obj->super;
														inst->AddFragmentDictionary(inst, fragdic);
													} else {
														PRINTF("DictionaryValue cannot be created!\n");
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
		}
	}
	PRINTF("\t}\n");
	return obj;
}

NetworkInfo *createNetworkInfo(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerNode *node)
{
	PRINTF("%s\n", strJson);
	NetworkInfo *obj = new_NetworkInfo();

	if (obj == NULL) {
		return NULL;
	}

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.NetworkProperty"))
												{
													if (obj->path == NULL) {
														node->AddNetworkInformation(node, obj);
													}
													NetworkProperty *netprop = createNetworkProperty(jsonState, jsonType, strJson);
													if (netprop != NULL) {
														obj->AddValues(obj, netprop);
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

NetworkProperty *createNetworkProperty(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	PRINTF("%s\n", strJson);

	NetworkProperty *obj = new_NetworkProperty();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->value = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->value, strJson);
						PRINTF("%s -> %s\n", strJson, obj->value);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

ComponentInstance *createComponentInstance(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, ContainerNode *node, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);

	ComponentInstance *obj = new_ComponentInstance();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->metaData);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						if (!strcmp("false", strJson)) {
							obj->super->started = false;
						} else if (!strcmp("true", strJson)) {
							obj->super->started = true;
						} else {
							obj->super->started = false;
						}
						PRINTF("%s -> %d\n", strJson, obj->super->started);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
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
								char id[150];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									PRINTF("TypeDefinition %s found!\n", id);
									obj->super->AddTypeDefinition(obj->super, typdef);
								}
								else
								{
									PRINTF("TypeDefinition %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("nodes[]/components[]") * strlen(obj->internalGetKey(obj)) * strlen(node->internalGetKey(node)) + 1);
									sprintf(objId, "nodes[%s]/components[%s]", node->internalGetKey(node), obj->internalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.Dictionary"))
												{
													if (obj->super->path == NULL) {
														node->AddComponents(node, obj);
													}
													Dictionary *dic = createDictionary(jsonState, jsonType, strJson, obj->super);
													if (dic != NULL) {
														if ((obj->FindByPath(dic->path, obj)) == NULL) {
															obj->super->AddDictionary(obj->super, dic);
														}
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

								case JSON_TYPE_STRING:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_INT:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_NUMBER:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.FragmentDictionary"))
												{
													if (obj->super->path == NULL) {
														node->AddComponents(node, obj);
													}
													FragmentDictionary *fragdic = createFragmentDictionary(jsonState, jsonType, strJson, obj->super);
													if(fragdic != NULL) {
														Instance *inst = obj->super;
														inst->AddFragmentDictionary(inst, fragdic);
													} else {
														PRINTF("DictionaryValue cannot be created!\n");
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
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
								JSONKevDeserializer(jsonState, jsonType, NULL);
								break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

Dictionary *createDictionary(struct jsonparse_state *jsonState, char jsonType, char *strJson, Instance *inst)
{
	PRINTF("%s\n", strJson);

	Dictionary *obj = new_Dictionary();

	if (obj == NULL) {
		return NULL;
	}

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						strcpy(obj->generated_KMF_ID, strJson);
						PRINTF("%s -> %s\n", strJson, obj->generated_KMF_ID);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState)) != ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryValue"))
												{
													if (obj->path == NULL) {
														inst->AddDictionary(inst, obj);
													}
													DictionaryValue *dicval = createDictionaryValue(jsonState, jsonType, strJson);
													obj->AddValues(obj, dicval);
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

Group *createGroup(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);

	Group *obj = new_Group();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->metaData = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->metaData, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->metaData);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->started = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->super->started);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
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
								char id[150];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									PRINTF("TypeDefinition %s found!\n", id);
									obj->super->AddTypeDefinition(obj->super, typdef);
								}
								else
								{
									PRINTF("TypeDefinition %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("groups[]") * strlen(obj->internalGetKey(obj)) + 1);
									sprintf(objId, "groups[%s]", obj->internalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
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
								char id[150];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for SubNode %s\n", id);

								node = root->FindNodesByID(root, id);

								if(node != NULL)
								{
									PRINTF("SubNode %s found!\n", id);
									obj->AddSubNodes(obj, node);
								}
								else
								{
									PRINTF("Node %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("groups[]") * strlen(obj->internalGetKey(obj)) + 1);
									sprintf(objId, "groups[%s]", obj->internalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
									/*node = new_ContainerNode();
									if(node != NULL)
									{
										node->super->super->name = malloc(sizeof(char) * strlen(id) + 1);
										strcpy(node->super->super->name, id);

										PRINTF("Node created with id: %d", node->super->super->name)
										obj->AddSubNodes(obj, node);
									}
									else
									{
										PRINTF("Cannot create SubNode reference\n");
									}*/
								}
								/*PRINTF("SubNode cannot be found!\n");*/
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.Dictionary"))
												{
													if (obj->super->path == NULL) {
														root->AddGroups(root, obj);
													}
													Dictionary *dic = createDictionary(jsonState, jsonType, strJson, obj->super);
													if (dic != NULL) {
														if ((obj->FindByPath(dic->path, obj)) == NULL) {
															obj->super->AddDictionary(obj->super, dic);
														}
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

								case JSON_TYPE_STRING:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_INT:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;

								case JSON_TYPE_NUMBER:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("\t\t\t\t%s\n", strJson);
									break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.FragmentDictionary"))
												{
													if (obj->super->path == NULL) {
														root->AddGroups(root, obj);
													}
													FragmentDictionary *fragdic = createFragmentDictionary(jsonState, jsonType, strJson, obj->super);
													if(fragdic != NULL) {
														Instance *inst = obj->super;
														inst->AddFragmentDictionary(inst, fragdic);
													} else {
														PRINTF("DictionaryValue cannot be created!\n");
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

FragmentDictionary *createFragmentDictionary(struct jsonparse_state *jsonState, char jsonType, char *strJson, Instance *inst)
{
	PRINTF("%s\n", strJson);
	FragmentDictionary *obj = new_FragmentDictionary();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						strcpy(obj->super->generated_KMF_ID, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->generated_KMF_ID);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryValue"))
												{
													if (obj->path == NULL) {
														inst->AddFragmentDictionary(inst, obj);
													}
													DictionaryValue *dicval = createDictionaryValue(jsonState, jsonType, strJson);
													if(dicval != NULL)
													{
														Dictionary *dico = obj->super;
														dico->AddValues(dico, dicval);
													}
													else
													{
														PRINTF("DictionaryValue cannot be created!\n");
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
		}
	}
	PRINTF("\t}\n");
	return obj;
}

DictionaryValue *createDictionaryValue(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	PRINTF("%s\n", strJson);

	DictionaryValue *obj = new_DictionaryValue();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->value = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->value, strJson);
						PRINTF("%s -> %s\n", strJson, obj->value);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

TypeDefinition *createTypeDefinition(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);

	TypeDefinition *obj = NULL;

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
		PRINTF("TypeDefinition %s not supported!\n", strJson);
		return NULL;
	}

	if (obj == NULL) {
		return NULL;
	}

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->version = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->version, strJson);
						PRINTF("%s -> %s\n", strJson, obj->version);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->factoryBean = malloc(sizeof(char) * strlen(strJson) + 1); /*atoi(strJson);*/
						strcpy(obj->factoryBean, strJson);
						PRINTF("%s -> %s\n", strJson, obj->factoryBean);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->bean = malloc(sizeof(char) * strlen(strJson) + 1); /*atoi(strJson);*/
						strcpy(obj->bean, strJson);
						PRINTF("%s -> %s\n", strJson, obj->bean);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->abstract = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->abstract);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
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
								char id[150];
								memset(&id[0], 0, sizeof(id));
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for DeployUnit %s\n", id);

								du = root->FindDeployUnitsByID(root, id);

								if(du != NULL)
								{
									PRINTF("DeployUnit %s found!\n", id);
									obj->AddDeployUnit(obj, du);
								}
								else
								{
									PRINTF("DeployUnit %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("typeDefinitions[]") * strlen(obj->internalGetKey(obj)) + 1);
									sprintf(objId, "typeDefinitions[%s]", obj->internalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
								/*case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;*/

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
														JSONKevDeserializer(jsonState, jsonType, NULL);
														break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryType"))
												{
													if (obj->path == NULL) {
														root->AddTypeDefinitions(root, obj);
													}
													DictionaryType *dictype = createDictionaryType(jsonState, jsonType, strJson, obj);
													if(dictype != NULL)
														obj->AddDictionaryType(obj, dictype);
													else
														return NULL;
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
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

							case JSON_TYPE_STRING:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

DictionaryType *createDictionaryType(struct jsonparse_state *jsonState, char jsonType, char *strJson, TypeDefinition *typdef)
{
	PRINTF("%s\n", strJson);

	DictionaryType *obj = new_DictionaryType();

	if(obj == NULL)
		return NULL;

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		PRINTF("jsonType: %c\n", jsonType);
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "generated_KMF_ID"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						strcpy(obj->generated_KMF_ID, strJson);
						PRINTF("%s -> %s\n", strJson, obj->generated_KMF_ID);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
						while((jsonType = jsonparse_next(jsonState))!= ']')
						{
							switch(jsonType)
							{
							case JSON_TYPE_OBJECT:
								PRINTF("JSON_TYPE_OBJECT\n\t{\n");
								switch(jsonparse_next(jsonState))
								{
								case JSON_TYPE_PAIR_NAME:
									jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
									PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
									if(!strcmp(strJson, "eClass"))
									{
										switch(jsonparse_next(jsonState))
										{
										case JSON_TYPE_PAIR:
											jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
											PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
											switch(jsonparse_next(jsonState))
											{
											case JSON_TYPE_STRING:
												jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
												if(!strcmp(strJson, "org.kevoree.DictionaryAttribute"))
												{
													if (obj->path == NULL) {
														typdef->AddDictionaryType(typdef, obj);
													}
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
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

DictionaryAttribute *createDictionaryAttribute(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	PRINTF("%s\n", strJson);

	DictionaryAttribute *obj = new_DictionaryAttribute();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->optional = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->optional);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->state = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->state);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->datatype = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->datatype, strJson);
						PRINTF("%s -> %s\n", strJson, obj->datatype);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->fragmentDependant = atoi(strJson);
						PRINTF("%s -> %d\n", strJson, obj->fragmentDependant);
						break;
					}
					break;
				}
			}
			else if(!strcmp(strJson, "defaultValue"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->defaultValue = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->defaultValue, strJson);
						PRINTF("%s -> %s\n", strJson, obj->defaultValue);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

/*NodeNetwork* createNodeNetwork(struct jsonparse_state *jsonState, char jsonType, char *strJson)
{
	NodeNetwork *ptr = (NodeNetwork*)malloc(sizeof(NodeNetwork));

	if(ptr == NULL)
	{
		PRINTF("FATAL can't allocate NodeNetwork \n");
		return NULL;
	}
	else
	{
		ptr->accept = _acceptNodeNetwork;
	}

	return ptr;
}*/

TypeLibrary *createTypeLibrary(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root, JSONModelLoader *loader)
{
	PRINTF("%s\n", strJson);

	TypeLibrary *obj = new_TypeLibrary();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_ARRAY:
						/*jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);*/
						PRINTF("[\n");
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
								char id[150];
								sscanf(strJson, "%*[^[][%[^]]", id);
								PRINTF("Looking for TypeDefinition %s\n", id);

								typdef = root->FindTypeDefsByID(root, id);

								if(typdef != NULL)
								{
									PRINTF("TypeDefinition %s found!\n", id);
									obj->AddSubTypes(obj, typdef);
								}
								else
								{
									PRINTF("TypeDefinition %s not found!\n", id);
									char *objId = (char*)malloc(sizeof(char) * strlen("libraries[]") * strlen(obj->internalGetKey(obj)) + 1);
									sprintf(objId, "libraries[%s]", obj->internalGetKey(obj));
									PRINTF("Storing objId %s for later resolve of %s!\n", objId, strJson);
									ObjectReference *ref = new_ObjectReference(objId, strdup(strJson));
									loader->addObjectReference(loader, ref);
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
										PRINTF("Cannot create TypeDefinition reference\n");
									}*/
								}
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_INT:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;

							case JSON_TYPE_NUMBER:
								jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
								PRINTF("\t\t\t\t%s\n", strJson);
								break;
							}
						}
						PRINTF("\t\t\t]\n");
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}

DeployUnit * createDeployUnit(struct jsonparse_state *jsonState, char jsonType, char *strJson, ContainerRoot *root)
{
	PRINTF("%s\n", strJson);

	DeployUnit *obj = new_DeployUnit();

	while((jsonType = jsonparse_next(jsonState)) != '}')
	{
		switch(jsonType)
		{
		case JSON_TYPE_PAIR_NAME:
			jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
			PRINTF("JSON_TYPE_PAIR_NAME\n%s\n", strJson);
			if(!strcmp(strJson, "name"))
			{
				switch(jsonparse_next(jsonState))
				{
				case JSON_TYPE_PAIR:
					jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->super->name = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->super->name, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->groupName = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->groupName, strJson);
						PRINTF("%s -> %s\n", strJson, obj->super->name);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						/*obj->state = atoi(strJson);*/
						obj->version = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->version, strJson);
						PRINTF("%s -> %s\n", strJson, obj->version);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->url = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->url, strJson);
						PRINTF("%s -> %s\n", strJson, obj->url);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->hashcode = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->hashcode, strJson);
						PRINTF("%s -> %s\n", strJson, obj->hashcode);
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
					PRINTF("JSON_TYPE_PAIR\n\t\t\t%s : ", strJson);
					switch(jsonparse_next(jsonState))
					{
					case JSON_TYPE_STRING:
						jsonparse_copy_value(jsonState, strJson, MAX_STRJSON_SIZE);
						obj->type = malloc(sizeof(char) * strlen(strJson) + 1);
						strcpy(obj->type, strJson);
						PRINTF("%s -> %s\n", strJson, obj->type);
						break;
					}
					break;
				}
			}
			break;
		}
	}
	PRINTF("\t}\n");
	return obj;
}
