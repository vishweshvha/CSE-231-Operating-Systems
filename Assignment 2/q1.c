#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigterm(){
    printf("CHILD: I have received a SIGTERM\n");
}

void S1(){
    printf("1 %d\n", getpid());
    kill(getpid(), SIGTERM);
}

void ST(){
    printf("t %d\n", getpid());
    char *args[]={"./E1",NULL};
    execv(args[0],args);
}

void SR(){
    printf("r %d\n", getpid());
    char *args[]={"./E1",NULL};
    execv(args[0],args);
}

int main(){
    pid_t pid, pid_st, pid_sr;

    if ((pid = fork()) < 0){
        perror("\nError in fork()");
        exit(0);
    }

    if (pid == 0){
        signal(SIGTERM, sigterm);
        S1();

        if ((pid_st = fork()) < 0){
            perror("\nError in fork()");
            exit(0);
        }

        if (pid_st == 0){
            ST();

            if ((pid_sr = fork()) < 0){
                perror("\nError in fork()");
                exit(0);
            }

            if (pid_sr == 0){
                SR();
            }

            waitpid(pid_sr, NULL, 0);
        }

        waitpid(pid_st, NULL, 0);
    }

    waitpid(pid, NULL, 0);

    return(0);
}