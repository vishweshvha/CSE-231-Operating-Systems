#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>


#include "utils.h"

int main(){
    //srand(time(NULL));
    char string_array[50][MAX_STRING_LENGTH];
    for(int i = 0; i < 50; i++ ){
        generate_random_string(string_array[i], MAX_STRING_LENGTH);
    }

    int file_descriptor;
    char * myfifo = "/tmp/myfifo";

    mkfifo(myfifo, 0666);

    struct StringEntry string_entries;
    char buffer[1024];
    int id_req = -1;
    while(id_req < 50){
        file_descriptor = open(myfifo, O_RDONLY);
        int ret = read(file_descriptor, buffer, sizeof(struct StringEntry));
        if (ret==-1){
            perror("accept");
            continue;
        } else if (ret == 0){
            break;
        }
        id_req = *((int *)buffer);
        printf("ID: %d\n", id_req);

        if (id_req > 0) {
            id_req += 1;
        }
        if (id_req == 50) {
            break;
        }
        close(file_descriptor);

        file_descriptor = open(myfifo, O_WRONLY);
        for (int i=id_req; i<id_req+5; i++) {
            string_entries.id_[i - id_req] = i;
            strncpy(string_entries.str_[i - id_req], string_array[i], MAX_STRING_LENGTH);
        }

        write(file_descriptor, (char *) &string_entries, sizeof(string_entries));
        close(file_descriptor);
    }
    return 0;
}