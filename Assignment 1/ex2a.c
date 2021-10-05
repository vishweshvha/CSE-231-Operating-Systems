#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "ex2c.c"

void A(){
    printf("-----------");
    printf("\n Entered A");
    printf("\n-----------");
    
    unsigned long long num = INT64_C(4702111234474983745);
    printf("\n64 Bit Number: %llu\n", num);
    extern void B(unsigned long long num);
    B(num);
}

int main(){
    A();
}

//5208492444341059905 = AAAHHHHH
//4702111234474983745 = AAAAAAAA

