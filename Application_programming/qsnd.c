//向先前打开的队列发送消息

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSZ 512

/* Message structure */
struct msg {
    long msg_type;
    char msg_text[BUFSZ];
};

int main(int argc, char *argv[])
{
    int qid; /* The queue identifier */
    int len; /* Length of data sent */
    struct msg pmsg; /* Pointer to message structure 指向消息结构的指针*/
     
    /* Expect the queue ID passed on the command-line 期望通过命令行传递队列ID*/
    if(argc != 2) {
        puts("USAGE: qsnd <queue ID>");
        exit(EXIT_FAILURE);
    }
    qid = atoi(argv[1]);  //把参数所指向的字符串转换为一个整数（类型为 int 型）。

    /* Get the message to add to the queue 获取要添加到队列中的消息*/
    puts("Enter message to post:");
    if((fgets((&pmsg)->msg_text, BUFSZ, stdin)) == NULL) {
        puts("no message to post");
        exit(EXIT_SUCCESS);
    }
     
    /* Associate the message with this process 将消息与此流程关联*/
    pmsg.msg_type = getpid();
    /* Add the message to the queue */
    len = strlen(pmsg.msg_text);
    if((msgsnd(qid, &pmsg, len, 0)) < 0) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    puts("message posted");  //消息发布

    exit(EXIT_SUCCESS);
}
