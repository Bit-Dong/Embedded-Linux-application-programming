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
    int fd;			/* FIFO�ļ������� */
  	int len;			/* д��FIFO���ֽ� */
    char buf[PIPE_BUF];	/* ȷ��ԭ��д�� */
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
        /* ��ȡ����ʱ�� */
        time(&tp);
        /* ����Ҫд����ַ��� */
        len = sprintf(buf, "wrfifo %d sends %s", getpid(), ctime(&tp));
        /* ʹ��(len + 1)����Ϊsprintf�����������null */
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
