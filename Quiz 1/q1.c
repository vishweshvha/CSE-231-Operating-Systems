#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
    pid_t pid1 ;
    printf("before fork()");

    if((pid1 = fork()) >0){
        waitpid(pid1, NULL, 0);
        printf("hello");
    }

    else if (pid1 == 0){
        execl("/usr/bin/bash", "bash", NULL);
        printf("done launching the shell");

    }

    else{
        perror("fork()");
    }
    printf("he");
    return 0;
}