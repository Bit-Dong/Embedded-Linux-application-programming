//  gcc -o server server.c -pthread
//  ./server 8092

#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <strings.h>

int main(int argc, char* argv[]){
	if (argc!=2)
	{
		/* code */
		printf("argc error!\n");
		return -1;
	}
	// ��һ�� �����׽���������
	int server_socket=socket(PF_INET,SOCK_STREAM,0);
	//�ڶ��� ������������ַ�ṹ
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));    //�Ƽ�ʹ��memset���bzero   memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    //INADDR_ANY����ָ����ַΪ0.0.0.0�ĵ�ַ�������ַ��ʵ�ϱ�ʾ��ȷ����ַ�������е�ַ�����������ַ���� һ����˵���ڸ���ϵͳ�о������Ϊ0ֵ��
    server_addr.sin_addr.s_addr = /*htonl()*/INADDR_ANY;
    // ������ ���׽���
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
    {
    	/* code */
    	printf("bind error!\n");
    	return -1;
    }
    // ���Ĳ� �����׽���
    if (listen(server_socket,10))
    {
    	/* code */
    	printf("listen error!\n");
    	return -1;
    }
    // ���岽 ���������
    struct sockaddr_in client_addr;
    int client_addr_size=sizeof(client_addr);
    while(1)
   	{
   		int client_socket=0;
   		bzero(&client_addr,sizeof(client_addr));
	    if((client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_size)) == -1)
	    {
	      	printf("accept error!\n-----client_socket=%d",client_socket);
	      	return -1;
	    }
	    // �����ӽ��� fork()
	    /*
			��ֵ�������ӽ���ʧ�ܡ�
			�㣺���ص��´������ӽ��̡�
			��ֵ�����ظ����̻�����ߡ���ֵ�����´������ӽ��̵Ľ���ID
	    */
	    int pid=fork();
	    // �����µ��ӽ��̳ɹ�
	    if (pid==0)
	    {
	    	// ������ʱ�ͻ��˵�ַ�ṹ�����ڴ�ſ�ʼaccept���Ŀͻ�������
	    	struct sockaddr_in client_in_addr;
	    	client_in_addr.sin_addr.s_addr=client_addr.sin_addr.s_addr;
	    	client_in_addr.sin_port=client_addr.sin_port;
	    	printf("Join client  ip:%s  port:%d\n",inet_ntoa(client_addr.sin_addr),client_in_addr.sin_port);
	    	// �رյ�ǰ���̵��׽�����������
	    	close(server_socket);
            char buf[1024];
            char send_buf[100]="ok";
            int recv_len;
            while(1)
            {
            	bzero(buf, sizeof(buf));           	
                if((recv_len = recv(client_socket, buf, sizeof(buf), 0)) < 0)
                    return -1;
                // �ж�������յ�Ϊ0���и��ͻ����˳�������ѭ��
                if(!recv_len){
                    printf("Have client exit,ip:%s  port:%d\n", inet_ntoa(client_in_addr.sin_addr),client_in_addr.sin_port);//struct in_addr
                	break;
                }
                if(!strncmp(buf,"yes",3)){
                	printf("OK\n");
				}
                printf("Client-%s -%d:%s\n",inet_ntoa(client_in_addr.sin_addr),client_in_addr.sin_port,buf);
            	if(send(client_socket,send_buf, strlen(send_buf), 0) <= 0)
                    return -1;
            }
            close(client_socket);
            return 0;
	    }
	    // ���ظ��������ӽ���id  �����̾Ϳ��Թرս��յ��׽���������
        else if(pid > 0)
        {
            close(client_socket);
        }
        else
        //�����ӽ���ʧ�ܣ�ֱ���˳�
           exit(-1);
   	}

    return 0;
}


