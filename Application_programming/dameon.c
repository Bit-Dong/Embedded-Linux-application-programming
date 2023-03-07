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
	int i,fd,len;//fdΪ�ļ�������
	char *buf="This is a Dameon\n";
	len =strlen(buf);		//��ȡ�ַ����ĳ���
	pc=fork(); 			//����һ���½���
	if(pc<0){			//pid<0 ,print error information
		printf("error fork\n");
		exit(1);
	}else if(pc>0)			
	exit(0);			//�˳�������
	
	printf("the process pid is:%d\n",getpid());//��ȡ�ӽ���ID
	setsid();				//����һ���µĶԻ�
	chdir("/");				//�ı乤��Ŀ¼Ϊ��/��
	umask(0);				//�����ļ�����  ����ǰ���̴����ļ�����Ŀ¼���ɲ�����Ȩ��
	for(i=0;i<MAXFILE;i++)			//�رռ̳и����̵�fd
		close(i);
	while(1){		//���������ļ�damenon.log������Ȩ��
		if((fd=open("/tmp/dameon.log",O_CREAT|O_WRONLY|O_APPEND,0600))<0){
			
			perror("open");
			exit(1);
			}
		write(fd, buf, len); //������д��fd
		close(fd);		
		sleep(5);
	}
}
