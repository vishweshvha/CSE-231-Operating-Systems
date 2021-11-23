#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ipc.h>

#include "utils.h"

int main()
{
    int file_descriptor;
    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    int id_req = 0;
    char buffer[sizeof(struct StringEntry)];
    while(id_req < 49){
        file_descriptor = open(myfifo,O_WRONLY);
        write(file_descriptor, (char *) &id_req, sizeof(id_req));
        close(file_descriptor);

        file_descriptor = open(myfifo,O_RDONLY);
        read(file_descriptor, buffer, sizeof(struct StringEntry));
        struct StringEntry *data = (struct StringEntry*) buffer;
        for (int j = 0; j < 5; j++){
            printf("%d: %s\n", data->id_[j], data->str_[j]);
        }
        id_req = data->id_[4];
        close(file_descriptor);
    }
    file_descriptor = open(myfifo,O_WRONLY);
    write(file_descriptor, (char *) &id_req, sizeof(id_req));
    close(file_descriptor);
    return 0;
}