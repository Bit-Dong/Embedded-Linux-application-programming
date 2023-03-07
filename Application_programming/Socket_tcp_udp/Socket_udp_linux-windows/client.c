#include <stdio.h>
#include <Windows.h>
#include <assert.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSADATA s; // �����������AfxSocketInitȫ�ֺ������ص�Windows Sockets��ʼ����Ϣ  
	if (WSAStartup(MAKEWORD(2, 2), &s) != 0) // ͨ�����������������޷��Ų���,�׸�����Ϊ���ֽ�,ʹ��2.2�汾��Socket
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
		//	UDPʹ��sendto��������
		sendto(sockfd,buff,strlen(buff),0,(struct sockaddr*)&saddr,sizeof(saddr));
		memset(buff,0,128);
        int len=sizeof(saddr);
        //	UDPʹ��recvform��������
		recvfrom(sockfd,buff,127,0,(struct sockaddr*)&saddr,&len);
        printf("ack=%s\n",buff);
	}
	closesocket(sockfd);
	WSACleanup( );
    exit(0);
}


