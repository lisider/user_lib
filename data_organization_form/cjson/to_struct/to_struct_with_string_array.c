/*************************************************************************
  > File Name: to_struct_with_array.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: Sat 19 Jan 2019 07:31:17 PM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
int main(void){

	cJSON * root = NULL;
	char * string[]  = {"hello","pillo"};

	root=cJSON_CreateStringArray((const const char **)string,sizeof(string)/sizeof(char *));
    char *out = cJSON_Print(root);printf("%s\n",out);free(out);

}

