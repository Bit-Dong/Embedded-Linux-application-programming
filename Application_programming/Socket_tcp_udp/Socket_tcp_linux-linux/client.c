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
    //创建socket，用于和服务端通信
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    //向服务端发起请求连接
    struct sockaddr_in serv_addr;//首先要指定一个服务端的ip地址+端口，表明是向哪个服务端发起请求
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.124.16");//注意，这里是服务端的ip和端口
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
	    		
	    //向服务端发送消息
	    printf("Write:");
	    fgets(send_buf,128,stdin);
	    
	    //判断 是否关闭套接字 
		if(strncmp(send_buf,"exit",4) ==0){	 
	    	write(sock,send_buf,sizeof(send_buf));
			printf("\nExit success!\n");  	
	    	close(sock);   //断开连接 
	   		break; 
		} 
	    
	    write(sock,send_buf,sizeof(send_buf));
	    
	    //接收服务端发来的消息
	    if(read(sock,recv_buf,sizeof(recv_buf)-1));
			printf("ack:%s\n",recv_buf);
	}
    return 0;
}



