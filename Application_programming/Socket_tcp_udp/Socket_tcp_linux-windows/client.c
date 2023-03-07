///*client_tcp.c      gcc -o client client.c -lws2_32   */  
#include <stdio.h>
#include <Windows.h>

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
    //����socket�����ںͷ����ͨ��
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    //�����˷�����������
    struct sockaddr_in serv_addr;//����Ҫָ��һ������˵�ip��ַ+�˿ڣ����������ĸ�����˷�������
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.124.16");//ע�⣬�����Ƿ���˵�ip�Ͷ˿�
    serv_addr.sin_port = htons(8081);
    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1){
		printf("connect Socket Failed! Error: %d\n", GetLastError());
            getchar();
	}else{
		printf("Connect success!\n\n");
	}
    
    char send_buf[2560];
    char recv_buf[5120];
    char flag[256]="exit";
    while(1){
    	memset(&recv_buf, 0, sizeof(recv_buf));
	    memset(&send_buf, 0, sizeof(send_buf));
	    		
	    //�����˷�����Ϣ
	    printf("Write:");
	    scanf("%s",send_buf);
	    
	    //�ж� �Ƿ�ر��׽��� 
	    if(!strcmp(send_buf,flag)){	 
	    	send(sock,send_buf,sizeof(send_buf),0);
			printf("\nExit success!\n");  	
	    	closesocket(sock);   //�Ͽ����� 
	   		break; 
		} 
	    
	    send(sock,send_buf,sizeof(send_buf),0);
	    
	    //���շ���˷�������Ϣ
	    recv(sock,recv_buf,sizeof(recv_buf)-1,0);
	   
		printf("Server_send:%s\n",recv_buf);
	}
	WSACleanup( );
    return 0;
}

