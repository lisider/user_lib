#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define MAXBUF 1024

void usage(void){

	printf("usag : \n");
	printf("./server_ssl  port    lisnum    ip 				certificate_file    PrivateKey_file \n");
	printf("./server_ssl  60000   1         192.168.1.128   \"certificate_file\" \"PrivateKey_file\" \n");

	return ;
}


int main(int argc, char **argv)
{
	int sockfd, new_fd;
	socklen_t len;
	struct sockaddr_in my_addr, their_addr;
	unsigned int myport, lisnum;
	char buf[MAXBUF + 1];
	SSL_CTX *ctx;

	if(argc != 6)
	{
		usage();
		exit(0);
	}

	if (argv[1])
		myport = atoi(argv[1]);
	else
		myport = 7838;
	if (argv[2])
		lisnum = atoi(argv[2]);
	else
		lisnum = 2;

	printf("sws : %s,%s,line = %d,argc = %d\n",__FILE__,__func__,__LINE__,argc);
	//*****************************************************************************//
	//初始化
	//创建SSL会话环境
	//*****************************************************************************//
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	ctx = SSL_CTX_new(SSLv23_server_method());
	if (ctx == NULL) {
		ERR_print_errors_fp(stdout);
		exit(1);
	}
	//*****************************************************************************//
	//server独有
	//*****************************************************************************//
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	if (SSL_CTX_use_certificate_file(ctx, argv[4], SSL_FILETYPE_PEM) <= 0) { //用户证书
		ERR_print_errors_fp(stdout);
		exit(1);
	}
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	if (SSL_CTX_use_PrivateKey_file(ctx, argv[5], SSL_FILETYPE_PEM) <= 0) {//用户私钥
		ERR_print_errors_fp(stdout);
		exit(1);
	}
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	if (!SSL_CTX_check_private_key(ctx)) {
		ERR_print_errors_fp(stdout);
		exit(1);
	}
	//*****************************************************************************//
	//普通的连接
	//*****************************************************************************//
	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	} else
		printf("socket created\n");

	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	bzero(&my_addr, sizeof(my_addr));
	my_addr.sin_family = PF_INET;
	my_addr.sin_port = htons(myport);
	if (argv[3])
		my_addr.sin_addr.s_addr = inet_addr(argv[3]);
	else
		my_addr.sin_addr.s_addr = INADDR_ANY;

	if (bind(sockfd, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))== -1) {
		perror("bind");
		exit(1);
	} else
		printf("binded\n");

	if (listen(sockfd, lisnum) == -1) {
		perror("listen");
		exit(1);
	} else
		printf("begin listen\n");

	printf("sws : %s,%s,line = %d\n",__FILE__,__func__,__LINE__);
	while (1) {
		SSL *ssl;
		len = sizeof(struct sockaddr);

		if ((new_fd = accept(sockfd, (struct sockaddr *) &their_addr, &len)) == -1) {
			perror("accept");
			exit(errno);
		} else
			printf("server: got connection from %s, port %d, socket %d\n",inet_ntoa(their_addr.sin_addr),ntohs(their_addr.sin_port), new_fd);

		//*****************************************************************************//
		//建立连接之后的事情
		//*****************************************************************************//


		//SSL套接字是建立在普通的TCP套接字基础之上，建立SSL套接字

		ssl = SSL_new(ctx); //对应 SSL_free
		SSL_set_fd(ssl, new_fd);
		if (SSL_accept(ssl) == -1) { //相应客户端 SSL_connect
			perror("accept");
			close(new_fd);
			break;
		}

		//SSL的收发
		bzero(buf, MAXBUF + 1);
		strcpy(buf, "server->client");
		len = SSL_write(ssl, buf, strlen(buf));

		if (len <= 0) {
			printf("消息'%s'发送失败！错误代码是%d，错误信息是'%s'\n",buf, errno, strerror(errno));
			goto finish;
		} else
			printf("消息'%s'发送成功，共发送了%d个字节！\n",buf, len);

		bzero(buf, MAXBUF + 1);
		len = SSL_read(ssl, buf, MAXBUF);
		if (len > 0)
			printf("接收消息成功:'%s'，共%d个字节的数据\n",buf, len);
		else
			printf("消息接收失败！错误代码是%d，错误信息是'%s'\n",errno, strerror(errno));

finish:
		SSL_shutdown(ssl);//对应SSL_set_fd
		SSL_free(ssl);
		close(new_fd);//acceptfd
	}
	close(sockfd);
	SSL_CTX_free(ctx);
	return 0;
}
