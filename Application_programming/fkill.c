#include <sys/types.h>
#include <wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
     pid_t child;
     int errret;
 
     if((child = fork()) < 0) {
	    perror("fork");
	    exit(EXIT_FAILURE);
     } else if(child == 0) {	/* in the child process */
	    sleep(30);//使当前进程睡眠30s
     } else {			/* in the parent */
	    /* 发送一个被忽略的信号 */
	    printf("sending SIGCHLD to %d\n", child);//SIGCHLD标识子进程停止或结束的信号
	    errret = kill(child, SIGCHLD);    //向child进程号发送SIGCHLD信号 
	    if(errret < 0)
	       perror("kill:SIGCHLD");
	    else
	       printf("%d still alive\n", child);

	    /* now murder the child */
	    printf("killing %d\n", child);
	    if((kill(child, SIGTERM)) < 0)//SIGTERM是kill发送的软件结束信号
	       perror("kill:SIGTERM");
	    /* have to wait to reap the status */
	    waitpid(child, NULL, 0 );   //回收子进程 
     }
     exit(EXIT_SUCCESS);
}
