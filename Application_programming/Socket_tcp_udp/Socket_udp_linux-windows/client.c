#include <stdio.h>
#include <Windows.h>
#include <assert.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA s; // 用来储存调用AfxSocketInit全局函数返回的Windows Sockets初始化信息  
	if (WSAStartup(MAKEWORD(2, 2), &s) != 0) // 通过连接两个给定的无符号参数,首个参数为低字节,使用2.2版本的Socket
        {
            printf("Init Windows Socket Failed! Error: %d\n", GetLastError());
            getchar();
            return -1;
        }
	
	SOCKET sockfd = socket(AF_INET,SOCK_DGRAM,0);
	int flag=1;
	assert(sockfd != -1 );

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = inet_addr("192.168.124.16");
	int c=sendto(sockfd,"1",1,0,(struct sockaddr*)&saddr,sizeof(saddr));
	while(1)
	{
		if(c>0&&flag==1){
			flag=0;
			printf("Server Connect success!\n\n");
		}
		
		char buff[128] = {0};
		printf("write:");
		fgets(buff,128,stdin);
				
		if(strncmp(buff,"exit",4) ==0 )
		{
			sendto(sockfd,"exit",4,0,(struct sockaddr*)&saddr,sizeof(saddr));
			printf("\nExit success!\n");
			break;
		}
		//	UDP使用sendto发送数据
		sendto(sockfd,buff,strlen(buff),0,(struct sockaddr*)&saddr,sizeof(saddr));
		memset(buff,0,128);
        int len=sizeof(saddr);
        //	UDP使用recvform接收数据
		recvfrom(sockfd,buff,127,0,(struct sockaddr*)&saddr,&len);
        printf("ack=%s\n",buff);
	}
	closesocket(sockfd);
	WSACleanup( );
    exit(0);
}


