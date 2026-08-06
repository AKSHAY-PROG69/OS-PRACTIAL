/* Q10. Inter-process communication using message queue
   Note: Requires System V IPC support on the judge/compiler */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
};

int main() {
    key_t key = ftok(".", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg_buffer message;

    message.msg_type = 1;
    printf("Enter a message to send: ");
    fgets(message.msg_text, 100, stdin);

    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Message sent: %s\n", message.msg_text);

    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Message received: %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
