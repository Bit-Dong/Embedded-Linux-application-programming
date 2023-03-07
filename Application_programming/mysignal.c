#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void my_func(int sign_no)
{
	if(sign_no==SIGINT)    //程序终止(interrupt)信号, 在用户键入INTR字符(通常是Ctrl-C)时发出，用于通知前台进程组终止进程
		printf("I have get SIGINT\n");
	else if(sign_no==SIGQUIT)
		printf("I have get SIGQUIT\n"); //SIGQUIT 信号对应的 signo = 03，表示用户从键盘按下quit键，即 ctrl+\ ，
		                                //进程在收到 SIGQUIT 退出时会产生 core 文件，在这个意义上类似于一个程序错误信号。
}
int main()
{
	printf("Waiting for signal SIGINT or SIGQUIT \n ");
	signal(SIGINT, my_func);      //参数一：处理信号   参数二：处理方式 
	signal(SIGQUIT, my_func);
	pause();   //令目前的进程暂停(进入睡眠状态), 直到被信号(signal)所中断
	exit(0);
}
