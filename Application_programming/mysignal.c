#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void my_func(int sign_no)
{
	if(sign_no==SIGINT)    //������ֹ(interrupt)�ź�, ���û�����INTR�ַ�(ͨ����Ctrl-C)ʱ����������֪ͨǰ̨��������ֹ����
		printf("I have get SIGINT\n");
	else if(sign_no==SIGQUIT)
		printf("I have get SIGQUIT\n"); //SIGQUIT �źŶ�Ӧ�� signo = 03����ʾ�û��Ӽ��̰���quit������ ctrl+\ ��
		                                //�������յ� SIGQUIT �˳�ʱ����� core �ļ��������������������һ����������źš�
}
int main()
{
	printf("Waiting for signal SIGINT or SIGQUIT \n ");
	signal(SIGINT, my_func);      //����һ�������ź�   ������������ʽ 
	signal(SIGQUIT, my_func);
	pause();   //��Ŀǰ�Ľ�����ͣ(����˯��״̬), ֱ�����ź�(signal)���ж�
	exit(0);
}
