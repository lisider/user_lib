/*************************************************************************
  > File Name: struct_to_string.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: Sat 19 Jan 2019 09:02:04 PM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
int main(void){
	cJSON * root = NULL;
	cJSON * fmt = NULL;

	root =cJSON_CreateObject();	
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("Jack (\"Bee\") Nimble"));
	cJSON_AddNumberToObject(root,"sex",	1);
	cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());
	cJSON_AddStringToObject(fmt,"type",		"rect");
	cJSON_AddNumberToObject(fmt,"width",		1920);
	cJSON_AddNumberToObject(fmt,"height",		1080);
	cJSON_AddFalseToObject (fmt,"interlace");
	cJSON_AddNumberToObject(fmt,"frame rate",	24);
    char *out = cJSON_Print(root);printf("%s\n",out);free(out);

	printf("---------------------\n");
	printf("---------------------\n");
	printf("---------------------\n");


	int sex = cJSON_GetObjectItem(root,"sex")->valueint; 
	char name[256] = {0};strcpy(name,cJSON_GetObjectItem(root,"name")->valuestring);

	printf("sex:%d\n",sex);
	printf("name:%s\n",name);

	//2
	cJSON * format = cJSON_GetObjectItem(root,"format");
	int width = cJSON_GetObjectItem(format,"width")->valueint;

	printf("width:%d\n",width);
}

