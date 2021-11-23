#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <sys/wait.h>

int main (void){
    int a = 2 , *b = NULL;
    b = &a;
    printf("%p\n", b+1);
    printf("%p\n", (char*)b+1);
    printf("%p\n", (void*)b+1);
}