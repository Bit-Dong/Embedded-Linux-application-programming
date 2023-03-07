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
	    sleep(30);//ʹ��ǰ����˯��30s
     } else {			/* in the parent */
	    /* ����һ�������Ե��ź� */
	    printf("sending SIGCHLD to %d\n", child);//SIGCHLD��ʶ�ӽ���ֹͣ��������ź�
	    errret = kill(child, SIGCHLD);    //��child���̺ŷ���SIGCHLD�ź� 
	    if(errret < 0)
	       perror("kill:SIGCHLD");
	    else
	       printf("%d still alive\n", child);

	    /* now murder the child */
	    printf("killing %d\n", child);
	    if((kill(child, SIGTERM)) < 0)//SIGTERM��kill���͵���������ź�
	       perror("kill:SIGTERM");
	    /* have to wait to reap the status */
	    waitpid(child, NULL, 0 );   //�����ӽ��� 
     }
     exit(EXIT_SUCCESS);
}
