///*client_tcp.c*/
#include <unistd.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>

int main()
{
    //����socket�����ںͷ����ͨ��
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //�����˷�����������
    struct sockaddr_in serv_addr;//����Ҫָ��һ������˵�ip��ַ+�˿ڣ����������ĸ�����˷�������
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.124.16");//ע�⣬�����Ƿ���˵�ip�Ͷ˿�
    serv_addr.sin_port = htons(8099);
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1){
    	printf("connect socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
	}else{
		printf("Connect success!\n\n");
	}
    
    char send_buf[2560];
    char recv_buf[5120];
    while(1){
    	memset(&recv_buf, 0, sizeof(recv_buf));
	    memset(&send_buf, 0, sizeof(send_buf));
	    		
	    //�����˷�����Ϣ
	    printf("Write:");
	    fgets(send_buf,128,stdin);
	    
	    //�ж� �Ƿ�ر��׽��� 
		if(strncmp(send_buf,"exit",4) ==0){	 
	    	write(sock,send_buf,sizeof(send_buf));
			printf("\nExit success!\n");  	
	    	close(sock);   //�Ͽ����� 
	   		break; 
		} 
	    
	    write(sock,send_buf,sizeof(send_buf));
	    
	    //���շ���˷�������Ϣ
	    if(read(sock,recv_buf,sizeof(recv_buf)-1));
			printf("ack:%s\n",recv_buf);
	}
    return 0;
}



