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
    unsigned sec, lo;
    int h, m, s;
    __asm__ volatile ("rdtsc" : "=a"(lo), "=d"(sec));
    h = (sec/3600); 
	m = (sec -(3600*h))/60;
	s = (sec -(3600*h)-(m*60));
    char num[64];
    sprintf(num, "%.2d:%.2d:%.2d", h, m, s);
    int key = ftok("hello.txt", 'R');
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *data = shmat(shmid, NULL, 0);
    strncpy(data, num, 64);
    shmdt(&data);
}

int main(int argc, char **argv){
    sleep(1);
    signal(SIGALRM, sigalrm);
    kill(getpid(), SIGALRM);
    kill(atoi(argv[1]), SIGTERM);
    return(0);
}