#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>

#define BUFSZ PIPE_BUF

void err_quit(char *msg);

int main(int argc, char *argv[])
{
    int fd[2]; //�ļ�������fd[0]��ʾ��ȡ�ܵ���fd[1]��ʾд��ܵ�
    int fdin; /* �����ļ������� */
    char buf[BUFSZ];//bufΪ������
    int pid, len;

    /* Create the pipe */
    if((pipe(fd)) < 0)
        err_quit("pipe");
    
    /* �ֲ沢�ر��ʵ��������� */
    if((pid = fork()) < 0)
        err_quit("fork");
    if (pid == 0) {
        close(fd[1]);//�ر��ӽ��̵�д����
		//read()�������óɹ��᷵�ض�ȡ�����ֽ���
        while((len = read(fd[0], buf, BUFSZ)) > 0)
			//STDOUT_FILENO��ʾ��buf�е�����д����׼���
            write(STDOUT_FILENO, buf, len);//STDIN_FILENO��ʾ��׼���
        close(fd[0]);
    } else {
        /* Parent��writer���رն������� */
        close(fd[0]);
		//open�������ļ��ɹ�
        if((fdin = open(argv[1], O_RDONLY)) < 0) {
            perror("open");
            /* ����һЩ��������Ϊ�����޷������� */
            write(fd[1], "123\n", 4);
    	} else {
        //�ܵ�������ݱ��뱻����
        while((len = read(fdin, buf, BUFSZ)) > 0)
        	write(fd[1], buf, len);
        	close(fdin);
    	}
   		/* �ر�д������ */
   		close(fd[1]);
    }
    //waitpid��ʹĿǰ������ͣ��ֱ�����ź��������ӽ��̽���
    waitpid(pid, NULL, 0);
    
    

    exit(EXIT_SUCCESS);
}
    
void err_quit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
