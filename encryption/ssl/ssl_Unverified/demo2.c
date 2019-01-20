/* OpenSSL headers */
#include "openssl/bio.h"
#include "openssl/ssl.h"
#include "openssl/err.h"
#include <stdio.h>
#include <strings.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
	BIO * bio;
	SSL_CTX * ctx = SSL_CTX_new(SSLv23_client_method());
	SSL * ssl;
	//SSL_library_init
#if 0

	if(! SSL_CTX_load_verify_locations(ctx, "/path/to/TrustStore.pem", NULL))
	{
		/* Handle failed load here */
	}

	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);

#else
	/* Use this at the command line */
	/* then call this from within the application */
	if(! SSL_CTX_load_verify_locations(ctx, NULL, "/path/to/certfolder"))
	{
		/* Handle error here */
	}

#endif 
	bio = BIO_new_ssl_connect(ctx);
	BIO_get_ssl(bio, & ssl);
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

	/* Attempt to connect */
	BIO_set_conn_hostname(bio, "hostname:port");
	/* Verify the connection opened and perform the handshake */
	if(BIO_do_connect(bio) <= 0)
	{
		/* Handle failed connection */
	}


	if(SSL_get_verify_result(ssl) != X509_V_OK)
	{
		/* Handle the failed verification */
	}

	

	SSL_CTX_free(ctx);
	BIO_reset(bio);
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	/* To free it from memory, use this line */
	BIO_free_all(bio);

	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);

	return 0;
}
