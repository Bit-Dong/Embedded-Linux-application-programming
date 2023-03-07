///*client_tcp.c      gcc -o client client.c -lws2_32   */  
#include <stdio.h>
#include <Windows.h>

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
    //创建socket，用于和服务端通信
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    //向服务端发起请求连接
    struct sockaddr_in serv_addr;//首先要指定一个服务端的ip地址+端口，表明是向哪个服务端发起请求
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("192.168.124.16");//注意，这里是服务端的ip和端口
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
	    		
	    //向服务端发送消息
	    printf("Write:");
	    scanf("%s",send_buf);
	    
	    //判断 是否关闭套接字 
	    if(!strcmp(send_buf,flag)){	 
	    	send(sock,send_buf,sizeof(send_buf),0);
			printf("\nExit success!\n");  	
	    	closesocket(sock);   //断开连接 
	   		break; 
		} 
	    
	    send(sock,send_buf,sizeof(send_buf),0);
	    
	    //接收服务端发来的消息
	    recv(sock,recv_buf,sizeof(recv_buf)-1,0);
	   
		printf("Server_send:%s\n",recv_buf);
	}
	WSACleanup( );
    return 0;
}

