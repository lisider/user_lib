/*************************************************************************
  > File Name: main.c
  > Author: Sues
  > Mail: sumory.kaka@foxmail.com 
  > Created Time: Thu 03 May 2018 07:27:32 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "aes.h"
#include "my_printf.h"
#include "print_color.h"

#define CRYPTO_16

#define STR_VERIFY "{\"T\":0,\"verify\":\"xiaoxunlanya\"}"

char key[17] =          {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c , 0x00};

void printASCCI(char *str, int len) {
    int c;
    for(int i = 0; i < len; i++) {
        c = (int)*str++;
        c = c & 0x000000ff;
        PRINT_BARE("0x%x ", c);
    }
    PRINT_ENTER("");
}

char * format(char * str_origin);

int main(void){

    char str_origin[256] = {0}; //用来装原始信息
    int msg_len = 0; //字符串和 \r\n 的长度
    char *p = NULL; //用来装格式化后的信息
    int i;

    if(strlen(STR_VERIFY) > 65533)
        return -1;

    /*
     *填充
     * */

    //填充头
    str_origin[0] = 0xFB;
    str_origin[1] = 0xFB;

    //填充信息
    strcpy(&str_origin[4],STR_VERIFY);

    //填充长度
    str_origin[2] = (strlen(STR_VERIFY) +2)/256;
    str_origin[3] = (strlen(STR_VERIFY) +2)%256;

    //填充尾
    str_origin[strlen(STR_VERIFY)+4] = '\r';
    str_origin[strlen(STR_VERIFY)+5] = '\n';

    /*
     * 校验
     * */

    msg_len = str_origin[2]*256 + str_origin[3];
    if (str_origin[msg_len+4-1] != '\n' || str_origin[msg_len+4-2] != '\r'){
        PRINT("error-1\n");
        return -1;
    }
    PRINT("unformat str:%s,msg_len:%d+2\n",STR_VERIFY,(int)strlen(STR_VERIFY));


    /*
     * 格式化
     * */

    //格式化字符串
    p = format(str_origin); //注意:不是 strlen(str_origin+4)
    msg_len = p[2]*256 + p[3];
    if (p[msg_len+4-1] != '\n' || p[msg_len+4-2] != '\r'){
        PRINT("error\n");
        return -1;
    }
    PRINT("format str :%s,msg_len:%d+2\n",&p[4],msg_len-2);


    /*
     * 加密1
     * */

#ifndef CRYPTO_16
    aes(p+4, msg_len-2, key);//AES加密
    PRINT(GREEN "after encryption\n" NONE);
    printASCCI(p+4,msg_len-2);
#else
    for (i = 0 ;i< (msg_len-2)/16 ; i++){
        aes(p+4+i*16, 16, key);//AES加密
        PRINT(GREEN "after encryption,%dth\n"NONE,i);
        printASCCI(p+4+i*16,16);
    }
#endif
    msg_len = p[2]*256 + p[3];
    if (p[msg_len+4-1] != '\n' || p[msg_len+4-2] != '\r'){
        PRINT("error1\n");
        return -1;
    }

    /*
     * 解密
     * */

#ifndef CRYPTO_16
    deAes(p+4, msg_len -2, key);
    PRINT(GREEN "after Decrypt\n" NONE);
    printASCCI(p+4,msg_len-2);
#else
    for (i = 0 ;i< (msg_len-2)/16 ; i++){
        deAes(p+4+i*16, 16, key);
        PRINT(GREEN "after Decrypt,%dth\n" NONE,i);
        printASCCI(p+4+i*16,16);
    }
#endif

    msg_len = p[2]*256 + p[3];

    if (p[msg_len+4-1] != '\n' || p[msg_len+4-2] != '\r'){
        PRINT("error2\n");
        return -1;
    }

    /*
     * 解析
     * */

    cJSON *root;
    char mystr[100]= {0};
    root=cJSON_Parse(p+4);
    int type = cJSON_GetObjectItem(root,"T")->valueint;

    strcpy(mystr,cJSON_GetObjectItem(root,"verify")->valuestring);
    PRINT(GREEN"after parse\n"NONE);
    PRINT("%s\n",mystr);

    /*
     * 释放内存
     * */

    cJSON_Delete(root);

    free(p);

    return 0;
}
