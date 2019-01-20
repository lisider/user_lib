/*************************************************************************
  > File Name: to_struct_with_array.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: Sat 19 Jan 2019 07:31:17 PM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

typedef struct {
	int lat;
	char address[32];
} fields_t;

fields_t fields[] = {
	{
		5,
		"cn",
	},
};

int main(void){

	cJSON * root = NULL;
	cJSON * fld = NULL;
	int i = 0;
	root=cJSON_CreateArray();
	for (i=0;i<1;i++)
	{
		cJSON_AddItemToArray(root,fld=cJSON_CreateObject());
		cJSON_AddNumberToObject(fld, "Latitude", fields[i].lat);
		cJSON_AddStringToObject(fld, "Address", fields[i].address);
	}

    char *out = cJSON_Print(root);printf("%s\n",out);free(out);

}

