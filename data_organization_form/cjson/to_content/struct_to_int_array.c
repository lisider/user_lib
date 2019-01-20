/*************************************************************************
  > File Name: to_struct_with_int_array.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: Sat 19 Jan 2019 07:45:59 PM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
int main(void){

	cJSON * root = NULL;
	int ids[4] = {1,2,3,4};

	root = cJSON_CreateIntArray(ids,sizeof(ids)/sizeof(int));
    char *out = cJSON_Print(root);printf("%s\n",out);free(out);
	int num = cJSON_GetArraySize(root);
	int i = 0;
	for(i = 0 ; i < num ;i ++ )
		printf("%d\n",cJSON_GetArrayItem(root,i)->valueint);


}

