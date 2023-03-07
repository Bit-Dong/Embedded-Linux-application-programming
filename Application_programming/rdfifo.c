#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>

void myfunc1(int sign_no)
{
	if(sign_no==SIGINT){
		printf("\nExit pipe!\n");
	}   
		
	else if(sign_no==SIGQUIT)
		printf("I have get SIGQUIT\n");  
}

int main(int argc, char *argv[])
{
	printf("I am %d\n", getpid());
    int fd;	/* Descriptor for FIFO */
    int len; /* Bytes read from FIFO */
    char buf[PIPE_BUF];
    char buf1[50]="Hello,Bit-Dong!";

	//在当前目录下创建一个有名管道
	unlink("test_rdfifo");
    if((mkfifo("test_rdfifo",0777)) < 0) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    /* Open the FIFO read-write */
    if((fd = open("test_rdfifo", O_RDWR)) < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    if((write(fd,buf1,50))<0){
           perror("write");
   }
    /* 读取并显示FIFO的输出直到EOF */
    	len = read(fd, buf, PIPE_BUF - 1); 
        printf("rdfifo read: %s\n", buf);
    	signal(SIGINT, myfunc1);
   		sleep(10);   
    

    close(fd);

    exit(EXIT_SUCCESS);
}


