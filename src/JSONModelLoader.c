#include "JSONModelLoader.h"
#include "DefaultFactorykevoree.h"
#include "kevoree.h"
#include "json.h"
#include "jsonparse.h"

char strJson[MAX_STRJSON_SIZE];
char jsonType;

void JSONKevDeserializer(struct jsonparse_state *jsonState, char _jsonType, ContainerRoot *newModel)
{
	ContainerRoot *new_model = NULL;

	switch(_jsonType)
	{
	case JSON_TYPE_OBJECT:
		/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
		printf("JSON_TYPE_OBJECT\n\t{\n");
		while((jsonType = jsonparse_next(jsonState))!= '}')
		{
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
								new_model = new_ContainerRoot();
								if(new_model == NULL)
								{
									printf("New model cannot be created!\n");
								}
								else
								{
									printf("New model %s created!\n", new_model->generated_KMF_ID);
								}
							}
							break;
						}
						break;
					}
				}
				else if(!strcmp(strJson, "generated_KMF_ID"))
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
							strcpy(new_model->generated_KMF_ID, strJson);
							printf("%s -> %s\n", strJson, new_model->generated_KMF_ID);
							break;
						}
						break;
					}
				}
				else if(!strcmp(strJson, "nodes"))
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
													if(!strcmp(strJson, "org.kevoree.ContainerNode"))
													{
														ContainerNode *node = createContainerNode(jsonState, jsonparse_next(jsonState), strJson, new_model);
														if(new_model != NULL && node != NULL)
														{
															new_model->AddNodes(new_model, node);
															printf("Successfully added Node to new_model\n");
														}
														else
														{
															printf("Node cannot be added to model!\n");
														}
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
							printf("]\n");
						}
						break;
					}
				}
				else if(!strcmp(strJson, "typeDefinitions"))
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
													if(!strcmp(strJson, "org.kevoree.NodeType") ||
															!strcmp(strJson, "org.kevoree.GroupType") ||
															!strcmp(strJson, "org.kevoree.ComponentType"))
													{
														TypeDefinition *typdef = createTypeDefinition(jsonState, jsonparse_next(jsonState), strJson, new_model);
														if(new_model != NULL && typdef != NULL)
														{
															printf("Adding TypeDefinition to new_model...\n");
															new_model->AddTypeDefinitions(new_model, typdef);
															printf("TypeDefinition added successfully!\n");
														}
														else
														{
															printf("TypeDefinition cannot be added to model!\n");
														}
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
							printf("]");
						}
						break;
					}
				}
				else if(!strcmp(strJson, "libraries"))
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
													if(!strcmp(strJson, "org.kevoree.TypeLibrary"))
													{
														TypeLibrary *typlib = createTypeLibrary(jsonState, jsonparse_next(jsonState), strJson, new_model);
														if(new_model != NULL && typlib != NULL)
															new_model->AddLibraries(new_model, typlib);
														else
															printf("TypeLibrary cannot be added to model!\n");
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
							printf("]");
						}
						break;
					}
				}
				else if(!strcmp(strJson, "deployUnits"))
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
													if(!strcmp(strJson, "org.kevoree.DeployUnit"))
													{
														DeployUnit *depunit = createDeployUnit(jsonState, jsonparse_next(jsonState), strJson, new_model);
														if(new_model != NULL && depunit != NULL)
															new_model->AddDeployUnits(new_model, depunit);
														else
															printf("DeployUnit cannot be added to model!\n");
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
							printf("]");
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
													if(!strcmp(strJson, "org.kevoree.Group"))
													{
														Group *group = createGroup(jsonState, jsonparse_next(jsonState), strJson, new_model);
														if(new_model != NULL && group != NULL)
															new_model->AddGroups(new_model, group);
														else
															printf("Group cannot be added to model!\n");
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
							printf("]");
						}
						break;
					}
				}
				else
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
							break;

						case JSON_TYPE_ARRAY:
							/*jsonparse_copy_value(jsonState, strJson, sizeof strJson);*/
							printf("[\n");
							while((jsonType = jsonparse_next(jsonState))!= ']')
							{
								switch(jsonType)
								{
								/*case JSON_TYPE_OBJECT:
																	JSONKevDeserializer(jsonState, jsonType, NULL);
																	break;*/

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

						case JSON_TYPE_INT:
							jsonparse_copy_value(jsonState, strJson, sizeof strJson);
							printf("JSON_TYPE_INT\n\t%s\n", strJson);
							break;

						case JSON_TYPE_NUMBER:
							jsonparse_copy_value(jsonState, strJson, sizeof strJson);
							printf("JSON_TYPE_NUMBER\n\t%s\n", strJson);
							break;

						case JSON_TYPE_ERROR:
							printf("JSON_TYPE_ERROR\n\t(empty)\n");
							break;
						}
						break;
					}
				}
				break;
			}
		}
		printf("}\n");
		break;
	}
}
