#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>

int main(int argc, char *argv[])
{
    int fd;			/* FIFO文件描述符 */
  	int len;			/* 写入FIFO的字节 */
    char buf[PIPE_BUF];	/* 确保原子写入 */
    time_t tp;			/* For time call */

    /* Identify myself */
    printf("I am %d\n", getpid());

    /* Open the FIFO write-only */
    if((fd = open(argv[1], O_WRONLY)) < 0) {
       perror("open");
       exit(EXIT_FAILURE);
    }

    /* Generate some data to write */
    while(1) {
        /* 获取当地时间 */
        time(&tp);
        /* 创建要写入的字符串 */
        len = sprintf(buf, "wrfifo %d sends %s", getpid(), ctime(&tp));
        /* 使用(len + 1)，因为sprintf不计算结束的null */
        if((write(fd, buf, len + 1)) < 0) {
            perror("write");
            close(fd);
            exit(EXIT_FAILURE);
        }
        printf("%s",buf); 
        sleep(3);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
