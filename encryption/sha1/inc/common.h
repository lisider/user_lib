/*************************************************************************
    > File Name: inc/common.h
    > Author: Sues
    > Mail: sumory.kaka@foxmail.com 
    > Created Time: Tue 10 Apr 2018 02:00:35 PM CST
 ************************************************************************/

#ifndef __COMMON_H_
#define __COMMON_H_

typedef unsigned int u32;

typedef struct {
	u32  h0,h1,h2,h3,h4;
	u32  nblocks;
	unsigned char buf[64];
	int  count;
} SHA1_CONTEXT;

void sha1_init( SHA1_CONTEXT *hd );
void sha1_write( SHA1_CONTEXT *hd, unsigned char *inbuf, size_t inlen);
void sha1_final(SHA1_CONTEXT *hd);

int get_file_sha1(char *FileNameInPut, char *outSHA1);
int get_str_sha1(char *buffer,int length, char *outSHA1);
#endif
