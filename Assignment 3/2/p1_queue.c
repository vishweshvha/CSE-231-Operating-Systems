#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/msg.h>

#include "utils.h"

struct s_buffer {
    long type;
    struct StringEntry string_entries;
} sbuffer;

struct r_buffer {
    long type;
    int id;
} rbuffer;

int main(){
    srand(time(NULL));
    char string_array[50][MAX_STRING_LENGTH];
    for(int i = 0; i < 50; i++ ){
        generate_random_string(string_array[i], MAX_STRING_LENGTH);
    }

    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    int id_req = -1;
    while(id_req < 50){
        msgrcv(msgid, &rbuffer, sizeof(rbuffer), 1, 0);
        id_req = rbuffer.id;
        printf("ID: %d\n", id_req);
        if (id_req > 0) {
            id_req += 1;
        }
        if (id_req == 50) {
            break;
        }
        sbuffer.type = 1;
        for (int i=id_req; i<id_req+5; i++) {
            sbuffer.string_entries.id_[i - id_req] = i;
            strncpy(sbuffer.string_entries.str_[i - id_req], string_array[i], MAX_STRING_LENGTH);
        }
        msgsnd(msgid, &sbuffer, sizeof(sbuffer), 0);
    }
    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}