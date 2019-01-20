/* OpenSSL headers */
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#if 0
/* Initializing OpenSSL */
SSL_load_error_strings();
ERR_load_BIO_strings();
OpenSSL_add_all_algorithms();
#endif

int main(int argc, const char *argv[])
{
	BIO * bio;

	char buf[100];

	int len = sizeof(buf);

	bio = BIO_new_connect("www.baidu.com:80");
	if(bio == NULL)
	{

		printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
		/* Handle the failure */
	}

#if 0
#endif
	if(BIO_do_connect(bio) <= 0)
	{
		printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
		/* Handle failed connection */
	}
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);

	bzero(buf,sizeof(buf));

	int x = BIO_read(bio, buf, len);
	if(x == 0)
	{
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
		/* Handle closed connection */
	}
	else if(x < 0)
	{
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
		if(! BIO_should_retry(bio))
		{
			/* Handle failed read here */
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
		}
		/* Do something to handle the retry */
	}
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);

	if(BIO_write(bio, buf, len) <= 0)
	{
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
		if(! BIO_should_retry(bio))
		{
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
			/* Handle failed write here */
		}
		/* Do something to handle the retry */
	}

	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	/* To reuse the connection, use this line */
	BIO_reset(bio);
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	/* To free it from memory, use this line */
	sleep(5);
	BIO_free_all(bio);
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);

	return 0;
}
