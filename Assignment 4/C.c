#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/msg.h>

#define _GNU_SOURCE
#define SYS_READER 450
#define PORT 8080

sem_t *sem;

struct s_buffer {
    long mesg_type;
    long *addr;
} sbuffer;

int main()
{   
    //sem = sem_open("/sem", O_CREAT, 0644, 0);
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    msgrcv(msgid, &sbuffer, sizeof(sbuffer), 1, 0);
    msgctl(msgid, IPC_RMID, NULL);
    long *ptr = sbuffer.addr;
    //sem_wait(sem);
    long num = syscall(SYS_READER, ptr);
    printf("Recieved %ld from Reader()\n", num);
    //sem_post(sem);
    return 0;
}