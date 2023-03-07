#include<fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h> 
         
#define MAXFILE 65535
int main()
{
	pid_t pc;
	int i,fd,len;//fd为文件描述符
	char *buf="This is a Dameon\n";
	len =strlen(buf);		//获取字符串的长度
	pc=fork(); 			//创建一个新进程
	if(pc<0){			//pid<0 ,print error information
		printf("error fork\n");
		exit(1);
	}else if(pc>0)			
	exit(0);			//退出父进程
	
	printf("the process pid is:%d\n",getpid());//获取子进程ID
	setsid();				//创建一个新的对话
	chdir("/");				//改变工作目录为“/”
	umask(0);				//重置文件掩码  允许当前进程创建文件或者目录最大可操作的权限
	for(i=0;i<MAXFILE;i++)			//关闭继承父进程的fd
		close(i);
	while(1){		//创建并打开文件damenon.log并设置权限
		if((fd=open("/tmp/dameon.log",O_CREAT|O_WRONLY|O_APPEND,0600))<0){
			
			perror("open");
			exit(1);
			}
		write(fd, buf, len); //将数据写入fd
		close(fd);		
		sleep(5);
	}
}
