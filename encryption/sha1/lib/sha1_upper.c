#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "common.h"


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  获取文件的SHA1值
 *
 * @Param FileNameInPut 文件路径
 * @Param outSHA1 输出的 sha1值
 *
 * @Returns   failed negtive , success 0
 */
/* ----------------------------------------------------------------------------*/
int get_file_sha1(char *FileNameInPut, char *outSHA1)
{
	if(FileNameInPut==NULL)
		return -1;
	FILE *fp;
	char buffer[4096];
	size_t n;
	SHA1_CONTEXT ctx;
	int i;

	fp = fopen ( FileNameInPut, "rb");
	if (!fp)
		return -2;
	sha1_init (&ctx);
	while ( (n = fread (buffer, 1, sizeof buffer, fp))){
		// 最后一个字符 是 '\n' ,需要去掉
		sha1_write (&ctx, (unsigned char *)buffer, n-1);
	}
	if (ferror (fp))
		return -3;
	sha1_final (&ctx);
	fclose (fp);

	for ( i=0; i < 20; i++)
	{
		sprintf(outSHA1 + 2*i, "%02x", (unsigned char)ctx.buf[i]);
	}
	outSHA1[2*i] = '\0';


	return 0;
}


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  获取字符串的sha1
 *
 * @Param buffer 字符串的头指针
 * @Param length 字符串的长度
 * @Param outSHA1 输出的 sha1
 *
 * @Returns   失败返回负数,成功 0
 */
/* ----------------------------------------------------------------------------*/
int get_str_sha1(char *buffer,int length, char *outSHA1)
{
	SHA1_CONTEXT ctx;
	int i;

	if(buffer==NULL)
		return -1;

	sha1_init (&ctx);
	sha1_write (&ctx, (unsigned char *)buffer, length);
	sha1_final (&ctx);

	for ( i=0; i < 20; i++)
	{
		sprintf(outSHA1 + 2*i, "%02x", (unsigned char)ctx.buf[i]);
	}
	outSHA1[2*i] = '\0';

	return 0;
}


