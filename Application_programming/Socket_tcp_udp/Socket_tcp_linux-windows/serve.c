///*serve_tcp.c*/
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
	//����һ��socket�ļ���Ҳ���Ǵ�һ������ͨѶ�˿�,������IPV4��AF_INET��+TCP��SOCK_STREAM��
	int serv_sock = socket(AF_INET, SOCK_STREAM,0);
	  
	//�󶨷�����ip�Ͷ˿ڵ����socket
	struct sockaddr_in serv_addr;//������Ϊ��ipv4��ʹ�õĽṹ����ipv4�ĵ�ַ����sockaddr_in
	memset(&serv_addr, 0, sizeof(serv_addr));//�����һ�³�ʼ��ֵ��д�ϵ�ַ�Ͷ˿ںţ�������bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.124.16");//����ip���ص�ַ�����ﻹ����ʹ��inet_pton�������е�ַת��
	serv_addr.sin_port = htons(8081);//����ѡ��һ���˿�8899
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	  
    //��socket����Ϊ����״̬
    if(listen(serv_sock,128)==-1){//�������������Ϊ128
		printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
	}else{
		printf("Waiting for client's request...\n");
	}
    //׼�����տͻ��˵���������,����Ĳ�������ظ����У����ն���ͻ��˵�����

    //���տͻ��˵��������Ӻ󣬷���һ���µ�socket��clnt_sock�����ںͶ�Ӧ�Ŀͻ��˽���ͨ��
    struct sockaddr_in clnt_addr;//��Ϊһ����������
    socklen_t clnt_addr_size = sizeof(clnt_addr);//��Ϊһ������+��������
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
  	if(clnt_sock!=-1)  printf("Connect success!\n\n");
    
    char recv_buf[2560];
    char send_buf[5120];
    char flag[256]="exit";
    char tmp[10]="OK!";
    while(1){
	    memset(&recv_buf, 0, sizeof(recv_buf));
	    memset(&send_buf, 0, sizeof(send_buf));
	    
		//��ȡ�ͻ��˷�����������
	    read(clnt_sock,recv_buf,sizeof(recv_buf)-1);
	    
	    //�ж��Ƿ�رտͻ�������
	    if(!strcmp(recv_buf,flag)){
	    	write(clnt_sock,flag,sizeof(flag));
	    	printf("\nExit success!\n");
	    	close(clnt_sock);
	    	close(serv_sock);  //�رշ���˼�����socket
	   		break; 
		}
		
	    //��ӡ���ͻ��˷�������Ϣ
	    if(recv_buf[0]!='\0')
	    	printf("Client_Send:%s\n",recv_buf);
	    
	    //����hello����󷵻ظ��ͻ���
	   // strcpy(send_buf+strlen("hello "),recv_buf);//ע�����ﲻ����sizeof��Ҫ��strlen����Ȼ�����ˡ�\0���������jingjing�ʹ�ӡ�������ˡ�
	   
	   //��ͻ��˷���OK����ʾ���ճɹ� 
	    write(clnt_sock,tmp,sizeof(tmp));   
    } 
  return 0;
}


