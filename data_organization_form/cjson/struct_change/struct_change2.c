/*************************************************************************
  > File Name: struct_delete.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: Sat 19 Jan 2019 08:50:02 PM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
int main(void){

	cJSON * root = NULL;
	cJSON * fmt = NULL;

	root =cJSON_CreateObject();	
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
	cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());
	cJSON_AddStringToObject(fmt,"type",		"rect");
	cJSON_AddNumberToObject(fmt,"width",		1920);
	cJSON_AddNumberToObject(fmt,"height",		1080);
	cJSON_AddFalseToObject (fmt,"interlace");
	cJSON_AddNumberToObject(fmt,"frame rate",	24);
    char *out = cJSON_Print(root);printf("%s\n",out);free(out);
	printf("--------------------\n");
	printf("--cjson 不关注顺序--\n");
	printf("--------------------\n");

	cJSON_DeleteItemFromObject(root, "name");
	cJSON_AddStringToObject(root, "name", "brown");
    out = cJSON_Print(root);printf("%s\n",out);free(out);


}
#if 0
//只能先删除,再添加
cJSON_AddStringToObject(pJsObj, "key", "test");
//也可以
cJSON_ReplaceItemInObject(fmt,"frame rate",cJSON_CreateNumber(25));
cJSON_ReplaceItemInObject(fmt,"frame rate",cJSON_CreateString("hello"));
#endif
