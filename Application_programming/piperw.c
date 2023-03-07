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
    int fd[2]; //文件描述符fd[0]表示读取管道，fd[1]表示写入管道
    int fdin; /* 输入文件描述符 */
    char buf[BUFSZ];//buf为缓冲区
    int pid, len;

    /* Create the pipe */
    if((pipe(fd)) < 0)
        err_quit("pipe");
    
    /* 分叉并关闭适当的描述符 */
    if((pid = fork()) < 0)
        err_quit("fork");
    if (pid == 0) {
        close(fd[1]);//关闭子进程的写数据
		//read()函数调用成功会返回读取到的字节数
        while((len = read(fd[0], buf, BUFSZ)) > 0)
			//STDOUT_FILENO表示将buf中的内容写到标准输出
            write(STDOUT_FILENO, buf, len);//STDIN_FILENO表示标准输出
        close(fd[0]);
    } else {
        /* Parent是writer，关闭读描述符 */
        close(fd[0]);
		//open函数打开文件成功
        if((fdin = open(argv[1], O_RDONLY)) < 0) {
            perror("open");
            /* 发送一些东西，因为我们无法打开输入 */
            write(fd[1], "123\n", 4);
    	} else {
        //管道里的数据必须被读走
        while((len = read(fdin, buf, BUFSZ)) > 0)
        	write(fd[1], buf, len);
        	close(fdin);
    	}
   		/* 关闭写描述符 */
   		close(fd[1]);
    }
    //waitpid会使目前进程暂停，直到有信号来或者子进程结束
    waitpid(pid, NULL, 0);
    
    

    exit(EXIT_SUCCESS);
}
    
void err_quit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}
