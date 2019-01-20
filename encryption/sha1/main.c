/*************************************************************************
    > File Name: main.c
    > Author: Sues
    > Mail: sumory.kaka@foxmail.com 
    > Created Time: Tue 10 Apr 2018 01:58:37 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include "common.h"


int main (int argc, char **argv)
{
	char sha1[41] = {0};
	int ret = 0;

	if(argc != 2)
	{
		printf("./main file\n");
		return -1;
	}

	system("echo hello > file");


	ret = get_file_sha1(*(argv+1), sha1);
	if(ret < 0){
		printf("get file sha1 error\n");
	}else
		printf("%s\n",sha1);


	printf("----------------\n");


	bzero(sha1,sizeof(sha1));
	ret = get_str_sha1("hello",strlen("hello"),sha1);
	if(ret < 0){
		printf("get file sha1 error\n");
	}else
		printf("%s\n",sha1);

	return 0;
}


