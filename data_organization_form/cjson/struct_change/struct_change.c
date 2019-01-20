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
	printf("--------------------\n");

	cJSON_ReplaceItemInObject(root,"name",cJSON_CreateString("Jim"));
    out = cJSON_Print(root);printf("%s\n",out);free(out);


}
