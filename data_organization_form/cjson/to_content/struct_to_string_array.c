/*************************************************************************
  > File Name: struct_to_strng_array.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: Sat 19 Jan 2019 09:16:37 PM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
int main(void){

	cJSON * root = NULL;
	char * string[]  = {"hello","pillo"};

	root=cJSON_CreateStringArray((const const char **)string,sizeof(string)/sizeof(char *));
    char *out = cJSON_Print(root);printf("%s\n",out);free(out);

	printf("------------\n");
	printf("------------\n");
	printf("------------\n");
	int num = cJSON_GetArraySize(root);
	int i = 0;
	for(i = 0 ; i < num ;i ++ )
		printf("%s\n",cJSON_GetArrayItem(root,i)->valuestring);

}


#if 0
	cJSON_GetArraySize(root);
	cJSON_GetArrayItem(root,i)->valuestring);
#endif
