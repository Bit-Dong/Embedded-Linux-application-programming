#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
     sigset_t set, pendset;
     struct sigaction action;

     sigemptyset(&set);   //将信号集初始化为空

     /* Add the interesting signal */
     sigaddset(&set, SIGTERM);   
     /* Block the signal */
     sigprocmask(SIG_BLOCK, &set, NULL);
	
     /* Send SIGTERM to myself */
     kill(getpid(), SIGTERM);

     /* Get pending signals 获取挂起信号*/
     sigpending(&pendset);
     /* If SIGTERM pending, ignore it */
     if(sigismember(&pendset, SIGTERM)){    
	    sigemptyset(&action.sa_mask);  //将信号集初始化为空
	    action.sa_handler = SIG_IGN; /* Ignore SIGTERM   SIG_DFL:表示默认动作    SIG_IGN:表示忽略该信号*/ 
	    sigaction(SIGTERM, &action, NULL);
     }
     
     /* Unblock SIGTERM */
     sigprocmask(SIG_UNBLOCK, &set, NULL);
     
     exit(EXIT_SUCCESS);
}
