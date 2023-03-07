//  gcc -o client client.c -pthread
//  ./client 192.168.124.16 8092

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
	if (argc != 3)
	{
		printf("Argc error!\n");
		return -1;
	}
	// 第一步创建网络通信套接字描述符
	int client_socket=socket(AF_INET,SOCK_STREAM,0);
	// 第二步创建服务器的地址结构体
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));  //推荐使用memset替代bzero
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	// 第三步 连接服务器
	if (connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
	{
		/* code */
		printf("Connect error!\n");
		return -1;
	}
	printf("Connect success!\n");
	char message[1024];
	bzero(message,sizeof(message));
	char buf[1024];
	printf("If want to exit,please enter q or Q.\n");
	while(1)
	{
		printf("Send to server:");
		scanf("%s",buf);
		if (strlen(buf)==1)
		{
			if(buf[0] == 'q' || buf[0] == 'Q')
                break;
		}
		if(strlen(buf) != write(client_socket, buf, strlen(buf))){
            printf("write() error!\n");
            exit(-1);
        }
        if(read(client_socket, message, sizeof(message)) <= 0){
            printf("read() error!\n");
            return -1;
        }
        printf("ack:%s\n", message);
        bzero(buf, sizeof(buf));
        bzero(message, sizeof(message));
	}
	close(client_socket);
	printf("Server exit!\n");
    return 0;
}


