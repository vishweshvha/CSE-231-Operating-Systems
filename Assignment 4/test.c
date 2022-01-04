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

#define _GNU_SOURCE
#define SYS_WRITER 449
#define SYS_READER 450
#define PORT 8080

long ConvertCharToLong(char *array) {
    int i=1;
    long result = (int)array[0] - '0';
    while(i<strlen(array)){
         result = result * 10 + ((int)array[i] - '0');
         ++i;
    }
    return result;
}

int main()
{
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

    long num = ConvertCharToLong(buffer);

    printf("Sending %ld to Writer()\n", num);
    long *ptr = syscall(SYS_WRITER, num);

    num = 0;

    num = syscall(SYS_READER, ptr);
    printf("Recieved %ld from Reader()\n", num);
   
    return 0;
}