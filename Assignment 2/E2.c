#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void sigalrm(){
    printf("CHILD: I have received a SIGALRM\n");
}

int main(){
    kill(getpid(), SIGALRM);
    return(0);
}