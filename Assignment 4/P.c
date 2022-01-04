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
#define SYS_WRITER 449
#define PORT 8080

sem_t *sem;

long ConvertCharToLong(char *array) {
    int i=1;
    long result = (int)array[0] - '0';
    while(i<strlen(array)){
         result = result * 10 + ((int)array[i] - '0');
         ++i;
    }
    return result;
}

struct s_buffer {
    long mesg_type;
    long *addr;
} sbuffer;

int main()
{
    //sem = sem_open("/sem", O_CREAT, 0644, 0);
    int random = open("/dev/urandom", O_RDONLY);
    if (random < 0)
    {
        printf("ERROR! Couldn't open /dev/urandom\n");
        return 0;
    }

    char buffer[8];
    ssize_t result = read(random, buffer, sizeof buffer);
    if (result < 0)
    {
        printf("ERROR! Couldn't read random data from /dev/urandom\n");
        return 0;
    }

    //sem_wait(sem);
    long num = ConvertCharToLong(buffer);
    printf("Sending %ld to Writer()\n", num);
    long *ptr = syscall(SYS_WRITER, num);
    //sem_post(sem);

    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    sbuffer.mesg_type = 1;
    sbuffer.addr = ptr;  
    msgsnd(msgid, &sbuffer, sizeof(sbuffer), 0);
    //msgctl(msgid, IPC_RMID, NULL);

    int res = close(random);
    if (res < 0){
        printf("ERROR! Couldn't close /dev/urandom\n");
        return 0;
    }

    return 0;
}