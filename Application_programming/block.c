#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void err_quit(char *);

int main(void)
{
     sigset_t newset;

     /* 创建信号集 */
     if((sigemptyset(&newset)) < 0)    //将信号集初始化为空
	     err_quit("sigemptyset");
     /* Adding SIGTERM and SIGALRM */   // SIGTERM:软件结束信号    SIGALRM:定时器终止时发送给进程的信号
     if((sigaddset(&newset, SIGTERM)) < 0)   //把指定信号添加到信号集set中
	     err_quit("sigaddset:SIGTERM");
     if((sigaddset(&newset, SIGALRM)) < 0)
	     err_quit("sigaddset:SIGALRM");
     
     /* Block the signals without handling them 屏蔽信号而不处理它们*/    
     if((sigprocmask(SIG_BLOCK, &newset, NULL)) < 0)   //SIG_BLOCK: 将newset中的信号添加到信号屏蔽字中    
	 												   //SIG_UNBLOCK：newset提供的屏蔽字进行信号的解除屏蔽。针对newset中的信号进行解屏。
     												   //SIG_SETMASK: newset提供的信号设置重新设置系统信号设置
	     err_quit("sigprocmask");
	     
/*
int sigismember(sigset_t *set, int signo);    该函数的作用是判断给定的信号signo是否是信号集中的一个成员 是返回1,不是返回0,给定的信号无效返回-1
int sigdelset(sigset_t *set, int signo);     该函数的作用是把信号signo从信号集set中删除
int sigfillset(sigset_t *set);     该函数的作用是把信号集初始化包含所有已定义的信号
int sigpending(sigset_t *set);     该函数的作用是将被阻塞的信号中停留在待处理状态的一组信号写到参数set指向的信号集中
int sigsuspend(const sigset_t *sigmask);    该函数通过将进程的屏蔽字替换为由参数sigmask给出的信号集，然后挂起进程的执行
*/

     /* Wait for a signal */
     pause();
     
     exit(EXIT_SUCCESS);
}
     
void err_quit(char *msg)
{
     perror(msg);
     exit(EXIT_FAILURE);
}
