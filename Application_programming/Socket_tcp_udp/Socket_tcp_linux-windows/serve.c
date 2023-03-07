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
	//创建一个socket文件，也就是打开一个网络通讯端口,类型是IPV4（AF_INET）+TCP（SOCK_STREAM）
	int serv_sock = socket(AF_INET, SOCK_STREAM,0);
	  
	//绑定服务器ip和端口到这个socket
	struct sockaddr_in serv_addr;//这里因为是ipv4，使用的结构体是ipv4的地址类型sockaddr_in
	memset(&serv_addr, 0, sizeof(serv_addr));//先清空一下初始的值，写上地址和端口号，可以用bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("192.168.124.16");//本机ip环回地址，这里还可以使用inet_pton函数进行地址转换
	serv_addr.sin_port = htons(8081);//随意选了一个端口8899
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	  
    //将socket设置为监听状态
    if(listen(serv_sock,128)==-1){//设置最大连接数为128
		printf("listen socket error: %s(errno: %d)\n",strerror(errno),errno);
		exit(0);
	}else{
		printf("Waiting for client's request...\n");
	}
    //准备接收客户端的请求连接,这里的步骤可以重复进行，接收多个客户端的请求

    //接收客户端的请求连接后，返回一个新的socket（clnt_sock）用于和对应的客户端进行通信
    struct sockaddr_in clnt_addr;//作为一个传出参数
    socklen_t clnt_addr_size = sizeof(clnt_addr);//作为一个传入+传出参数
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
  	if(clnt_sock!=-1)  printf("Connect success!\n\n");
    
    char recv_buf[2560];
    char send_buf[5120];
    char flag[256]="exit";
    char tmp[10]="OK!";
    while(1){
	    memset(&recv_buf, 0, sizeof(recv_buf));
	    memset(&send_buf, 0, sizeof(send_buf));
	    
		//读取客户端发送来的数据
	    read(clnt_sock,recv_buf,sizeof(recv_buf)-1);
	    
	    //判断是否关闭客户端连接
	    if(!strcmp(recv_buf,flag)){
	    	write(clnt_sock,flag,sizeof(flag));
	    	printf("\nExit success!\n");
	    	close(clnt_sock);
	    	close(serv_sock);  //关闭服务端监听的socket
	   		break; 
		}
		
	    //打印出客户端发来的消息
	    if(recv_buf[0]!='\0')
	    	printf("Client_Send:%s\n",recv_buf);
	    
	    //加上hello处理后返回给客户端
	   // strcpy(send_buf+strlen("hello "),recv_buf);//注意这里不能用sizeof，要用strlen，不然包含了‘\0’，后面的jingjing就打印不出来了。
	   
	   //向客户端发送OK，表示接收成功 
	    write(clnt_sock,tmp,sizeof(tmp));   
    } 
  return 0;
}


