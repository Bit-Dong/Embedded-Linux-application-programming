#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void err_quit(char *);

int main(void)
{
     sigset_t newset;

     /* �����źż� */
     if((sigemptyset(&newset)) < 0)    //���źż���ʼ��Ϊ��
	     err_quit("sigemptyset");
     /* Adding SIGTERM and SIGALRM */   // SIGTERM:��������ź�    SIGALRM:��ʱ����ֹʱ���͸����̵��ź�
     if((sigaddset(&newset, SIGTERM)) < 0)   //��ָ���ź���ӵ��źż�set��
	     err_quit("sigaddset:SIGTERM");
     if((sigaddset(&newset, SIGALRM)) < 0)
	     err_quit("sigaddset:SIGALRM");
     
     /* Block the signals without handling them �����źŶ�����������*/    
     if((sigprocmask(SIG_BLOCK, &newset, NULL)) < 0)   //SIG_BLOCK: ��newset�е��ź���ӵ��ź���������    
	 												   //SIG_UNBLOCK��newset�ṩ�������ֽ����źŵĽ�����Ρ����newset�е��źŽ��н�����
     												   //SIG_SETMASK: newset�ṩ���ź�������������ϵͳ�ź�����
	     err_quit("sigprocmask");
	     
/*
int sigismember(sigset_t *set, int signo);    �ú������������жϸ������ź�signo�Ƿ����źż��е�һ����Ա �Ƿ���1,���Ƿ���0,�������ź���Ч����-1
int sigdelset(sigset_t *set, int signo);     �ú����������ǰ��ź�signo���źż�set��ɾ��
int sigfillset(sigset_t *set);     �ú����������ǰ��źż���ʼ�����������Ѷ�����ź�
int sigpending(sigset_t *set);     �ú����������ǽ����������ź���ͣ���ڴ�����״̬��һ���ź�д������setָ����źż���
int sigsuspend(const sigset_t *sigmask);    �ú���ͨ�������̵��������滻Ϊ�ɲ���sigmask�������źż���Ȼ�������̵�ִ��
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
