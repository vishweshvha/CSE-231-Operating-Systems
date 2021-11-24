#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>

void sigalrm(){
    int key = ftok("hello.txt", 'R');
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *data = shmat(shmid, NULL, 0);
    strncpy(data, "RDRAND", 6);
    shmdt(&data);
}

int main(int argc, char **argv){
    signal(SIGALRM, sigalrm);
    kill(getpid(), SIGALRM);
    kill(atoi(argv[1]), SIGTERM);
    return(0);
}