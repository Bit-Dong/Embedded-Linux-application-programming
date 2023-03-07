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
	// 第一步 创建套接字描述符
	int server_socket=socket(PF_INET,SOCK_STREAM,0);
	//第二步 创建服务器地址结构
    struct sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));    //推荐使用memset替代bzero   memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    //INADDR_ANY就是指定地址为0.0.0.0的地址，这个地址事实上表示不确定地址，或“所有地址”、“任意地址”。 一般来说，在各个系统中均定义成为0值。
    server_addr.sin_addr.s_addr = /*htonl()*/INADDR_ANY;
    // 第三步 绑定套接字
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)))
    {
    	/* code */
    	printf("bind error!\n");
    	return -1;
    }
    // 第四步 监听套接字
    if (listen(server_socket,10))
    {
    	/* code */
    	printf("listen error!\n");
    	return -1;
    }
    // 第五步 多进程连接
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
	    // 创建子进程 fork()
	    /*
			负值：创建子进程失败。
			零：返回到新创建的子进程。
			正值：返回父进程或调用者。该值包含新创建的子进程的进程ID
	    */
	    int pid=fork();
	    // 创建新的子进程成功
	    if (pid==0)
	    {
	    	// 创建临时客户端地址结构体用于存放开始accept到的客户端数据
	    	struct sockaddr_in client_in_addr;
	    	client_in_addr.sin_addr.s_addr=client_addr.sin_addr.s_addr;
	    	client_in_addr.sin_port=client_addr.sin_port;
	    	printf("Join client  ip:%s  port:%d\n",inet_ntoa(client_addr.sin_addr),client_in_addr.sin_port);
	    	// 关闭当前进程的套接字描述符，
	    	close(server_socket);
            char buf[1024];
            char send_buf[100]="ok";
            int recv_len;
            while(1)
            {
            	bzero(buf, sizeof(buf));           	
                if((recv_len = recv(client_socket, buf, sizeof(buf), 0)) < 0)
                    return -1;
                // 判断如果接收到为0就有个客户端退出，跳出循环
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
	    // 返回给父进程子进程id  父进程就可以关闭接收的套接字描述符
        else if(pid > 0)
        {
            close(client_socket);
        }
        else
        //创建子进程失败，直接退出
           exit(-1);
   	}

    return 0;
}


