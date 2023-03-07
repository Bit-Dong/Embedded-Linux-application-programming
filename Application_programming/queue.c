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
    key_t key; /* The queue key */
    int len; /* Length of data sent */
    int len1; /* Length of message */
    struct msg pmsg; /* Pointer to message structure 指向消息结构的指针*/

    key = 80;

    /* Create the queue */
    printf("\nCreat Queue:\n");
    if((qid = msgget(key, IPC_CREAT | 0666)) < 0) {
        perror("msgget:create");
        exit(EXIT_FAILURE);
    }
    printf("\tcreated queue id = %d\n", qid);
     
    /* Open the queue again */
    if((qid == msgget(key, 0)) < 0) {
        perror("msgget:open");
        exit(EXIT_FAILURE);
    }
    printf("\topened queue id = %d\n", qid);
    printf("Creat Success!\n\n");
    
    puts("Send a message to queue:");
    if((fgets((&pmsg)->msg_text, BUFSZ, stdin)) == NULL) {
        puts("no message to post");
        exit(EXIT_SUCCESS);
    }
    /* Associate the message with this process 将消息与此进程关联*/
    pmsg.msg_type = getpid();
    /* Add the message to the queue */
    len = strlen(pmsg.msg_text);
    if((msgsnd(qid, &pmsg, len, 0)) < 0) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    puts("Send Success!");  //消息发布
    
    printf("\nRead all message from queue:\n");
    /* Retrieve and display a message from the queue 从队列检索并显示一条消息*/
    len1 = msgrcv(qid, &pmsg, BUFSZ, 0, 0);
    if(len1 > 0) {
        (&pmsg)->msg_text[len1] = '\0';
        printf("\treading queue id: %05d\n", qid);
        printf("\tmessage type: %05ld\n", (&pmsg)->msg_type);
		printf("\tmessage length: %d bytes\n", len1); 
        printf("\tmessage text: %s", (&pmsg)->msg_text);
    } else {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    puts("Read Success!");
    
    printf("\nRemove Queue:\n");
    if((msgctl(qid, IPC_RMID, NULL)) < 0) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("\tqueue %d removed Success!\n", qid);
    
    exit(EXIT_SUCCESS);
}
