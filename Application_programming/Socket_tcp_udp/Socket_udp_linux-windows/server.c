#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
	int sockfd = socket(AF_INET,SOCK_DGRAM,0);
	int flag=1;
	assert(sockfd != -1 );
	
	//ָ����ַ��Ϣ
	struct sockaddr_in saddr,caddr;
	memset(&saddr,0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	//��ͨ���ֿ�����htons()����ת�����������ݸ�ʽ������)
	saddr.sin_port = htons(8080);
	//�����ʮ���Ƶ�IP��ַת��Ϊ������
	saddr.sin_addr.s_addr = inet_addr("192.168.124.16");
	//�󶨵�ַ��Ϣ
	int res = bind(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));
	assert(res != -1);
	printf("Waiting...\n");
	
	char buff1[128]={0};
	int len1 = sizeof(caddr);
    int t=recvfrom(sockfd,buff1,127,0,(struct sockaddr*)&caddr,&len1);
    
    //	UDP����listen����
	while(1)
	{
        char buff[128]={0};
		int len = sizeof(caddr);
		
		if(t>0&&flag==1){
			flag=0;	
			printf("Client Connect success!\n\n");
		}

        //	UDPʹ��recvform��������
        //	UDP����accept
		int n = recvfrom(sockfd,buff,127,0,(struct sockaddr*)&caddr,&len);
		if(strncmp(buff,"exit",4) ==0 )
		{
			printf("\nExit success!\n");
			break;
		}
		
		assert(n!=-1);
		//	������н��
		printf("Client_send:%s",buff);
	
    	//	UDPʹ��sendto��������
        sendto(sockfd,"OK",2,0,(struct sockaddr*)&caddr,sizeof(caddr));
	}
    close(sockfd);
    exit(0);
}



