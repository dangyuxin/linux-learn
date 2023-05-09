#include <sys/types.h>
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
	int sockfd,connfd;//
	int len;
	char wbuf[1024];
	char rbuf[1024];
	struct sockaddr_in serveraddr,clientaddr; //两个结构体 一个用于绑定身份到套接字  一个用于接收客服端的结构体
	//1.创建监听套接字
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	//2.bind（通信需要套接字 把家的地址 门牌号绑上去 ip和端口）
	bzero(&serveraddr,sizeof(serveraddr)); //类似memset 清空结构体
	//地址族协议，选择IPV4
	serveraddr.sin_family = AF_INET;     //属于ipv4还是ipv6
	//IP地址 本机任意可用ip地址
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SER_PORT);//端口号	
	bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	//3.监听 和服务器连接的总和
	listen(sockfd,128);	
	int size = sizeof(clientaddr);
	//4.accept 阻塞监听 客服端链接的请求
	connfd = accept(sockfd,(struct sockaddr *)&clientaddr,&size); 	
	//输出客服端的ip和端口
	char ipstr[128];
	printf("client ip%s ,port %d\n",inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ipstr,sizeof(ipstr)),
		ntohs(clientaddr.sin_port));
	//5.处理客户端请求
	//读和写
	while(1)
	{
		memset(wbuf,0,sizeof(wbuf));//清空
		memset(rbuf,0,sizeof(wbuf));	
		//接收消息	
		int len = read(connfd,rbuf,sizeof(rbuf));
		if(len==0)//表示断开连接
		{
			printf("client is close....\n");
		}
		printf("receive from client:%s",rbuf);
		//发送消息
		printf("send to client:");
		fgets(wbuf,sizeof(wbuf),stdin);
		write(connfd,wbuf,strlen(wbuf));	
	}
	close(connfd);
	close(sockfd);
	return 0;
}

