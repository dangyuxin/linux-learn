#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define SER_PORT 8000
int main(void)
{
	int sockfd;
	struct sockaddr_in serveraddr;
	int len;
	char wbuf[1024],rbuf[1024];
	//1、socket 通信用套接字，创建一个sockfd
	sockfd = socket(AF_INET,SOCK_STREAM,0);
    char ipstr[]="127.0.0.1";
	//2、编辑要连接的服务器地址，并绑定
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;            //设置地址族协议
	serveraddr.sin_port = htons(SER_PORT);      //设置端口号
	inet_pton(AF_INET,ipstr,&serveraddr.sin_addr.s_addr);//设置ip地址   点分十进制转成网络字节序
	//2、connect 连接服务器 sockfd传出服务器套接字
	connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
	//3、读写
	while(1)
	{
		memset(wbuf,0,sizeof(wbuf));
		memset(rbuf,0,sizeof(rbuf));
		//发送消息
		printf("send to server:");
		fgets(wbuf,sizeof(wbuf),stdin);
		write(sockfd,wbuf,strlen(wbuf));
		
		//接收消息
		len=read(sockfd,rbuf,sizeof(rbuf));
		if(len==0)//表示断开连接
		{
			printf("server is close....\n");
		}
		printf("receive from server:%s",rbuf);
		
		
	}
	//4、close
	close(sockfd);
	return 0;
}

