/*************************************************************************
  > File Name: to_struct_with_string.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com
  > Created Time: Sat 19 Jan 2019 07:20:56 PM PST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
int main(void){

	char text[]="{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";
	cJSON * root=cJSON_Parse(text);
    char *out = cJSON_Print(root);printf("%s\n",out);free(out);

}
