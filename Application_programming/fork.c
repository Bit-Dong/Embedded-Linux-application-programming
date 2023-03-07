#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>

int main()
{
	puts("getpid():");
	printf("\tPID  = %d\n", getpid());
    printf("\tPPID = %d\n\n", getppid());
    
    puts("fork()/wait():");
    int status;
	pid_t child=fork();
	if(-1==child){
		perror("fork");
		exit(EXIT_FAILURE);
	} else if(child == 0) {
	    puts("in child");
	    printf("\tchild pid = %d\n", getpid());
	    printf("\tchild ppid = %d\n", getppid());
	    exit(EXIT_SUCCESS);
    } else {
    	//waitpid(child, &status, 0); 
    	wait(&status);//父进程执行到此，马上阻塞自己，直到有子进程结束。当发现有子进程结束时，就会回收它的资源。
	    puts("in parent");
	    printf("\tparent pid = %d\n", getpid());
	    printf("\tparent ppid = %d\n", getppid());
	    printf("\tchild exited with %d\n\n", status);
    }
    
   	puts("execve():");
    char *argv[]={"ls","-al", NULL};
    char *envp[]={0,NULL}; //传递给执行文件新的环境变量数组
    if(-1==execve("/bin/ls",argv,envp)){
    	perror("execve");
		exit(EXIT_FAILURE);
	}
	
    exit(EXIT_SUCCESS);
}
