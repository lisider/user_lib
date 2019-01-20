#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "common.h"


/* --------------------------------------------------------------------------*/
/**
 * @Synopsis  ��ȡ�ļ���SHA1ֵ
 *
 * @Param FileNameInPut �ļ�·��
 * @Param outSHA1 ����� sha1ֵ
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
		// ���һ���ַ� �� '\n' ,��Ҫȥ��
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
 * @Synopsis  ��ȡ�ַ�����sha1
 *
 * @Param buffer �ַ�����ͷָ��
 * @Param length �ַ����ĳ���
 * @Param outSHA1 ����� sha1
 *
 * @Returns   ʧ�ܷ��ظ���,�ɹ� 0
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


