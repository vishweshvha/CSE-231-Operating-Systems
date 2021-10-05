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

void sigterm(){
    int key = ftok("hello.txt", 'R');
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *data = shmat(shmid, NULL, 0);
    printf("%s\n", data);
    shmdt(&data);
    shmctl(shmid, IPC_RMID, 0);
}

void SR(int ppid){
    char pid[10];
    sprintf(pid, "%d", ppid);
    char *args[]={"./E1", pid , NULL};
    execv(args[0], args);
}

void ST(int ppid){
    char pid[10];
    sprintf(pid, "%d", ppid);
    char *args[]={"./E2", pid , NULL};
    execv(args[0], args);
}

int main(){
    pid_t pid, pid_st, pid_sr;
    if ((pid = fork()) < 0){
        perror("\nError in fork()");
        exit(0);
    }

    if (pid == 0){
        signal(SIGTERM, sigterm);
        struct itimerval val;
        val.it_interval.tv_sec = 0;
        val.it_interval.tv_usec = 0;
        val.it_value.tv_sec = 2; 
        val.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &val,0);
        while (1);
    }

    else{
        if ((pid_st = fork()) < 0){
            perror("\nError in fork()");
            exit(0);
        }

        if (pid_st == 0){
            if ((pid_sr = fork()) < 0){
                perror("\nError in fork()");
                exit(0);
            }

            if (pid_sr == 0){
                SR(pid);
            }

            ST(pid);
        }
    }
    waitpid(pid, NULL, 0);
    return(0);
}