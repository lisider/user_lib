/*************************************************************************
  > File Name: format.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: Thu 03 May 2018 07:38:26 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//格式化一个包 将信息 body部分 格式化一个 16* n 的 包 ,不满 16*n 的部分 ,用 0 填充
char * format(char * str_origin){

    int count = 0;
    char * tmp_p= NULL;
    int length = 0;
    char *p = NULL;
    int my_length;
    int str_len;

    if(str_origin == NULL)
        return NULL;

    length = str_origin[2] * 256 +str_origin[3];
    str_len = length -2;
    //printf("origin str length + 2 = %d\n",length);

    if (count = (16 - (length - 2)%16)%16){
        p = (char *)malloc(length + count + 4);
        memset(p,0,length + count + 4);
        memcpy(p, str_origin, 4 + str_len);

        //定位到 \r 处
        tmp_p = p + 4 + str_len;

        //填充0
        memset(tmp_p,0,count);

        //定位新的 \r 处

        *(tmp_p + count)= '\r';
        *(tmp_p + count + 1)= '\n';
        //*(p+length +4 -2+count) = '\r';
        //*(p+length +4 -2 + count) = '\n';

        p[2] = (length + count)/256;
        p[3] = (length + count)%256;


        my_length = p[2]*256 + p[3];

        if (p[my_length+4-1] != '\n' || p[my_length+4-2] != '\r'){
            printf("error\n");
            return NULL;
        }

    }else{
        p = (char *)malloc(length + 4);
        memcpy(p,str_origin,length + 4);
    }
    return p;
}
