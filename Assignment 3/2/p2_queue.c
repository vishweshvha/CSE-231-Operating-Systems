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
    long mesg_type;
    struct StringEntry string_entries;
} sbuffer;

struct r_buffer {
    long mesg_type;
    int id;
} rbuffer;
  
int main()
{
    key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    int id_req = 0;
    while(id_req < 49){
        rbuffer.mesg_type = 1;
        rbuffer.id = id_req;
        msgsnd(msgid, &rbuffer, sizeof(rbuffer), 0);
        msgrcv(msgid, &sbuffer, sizeof(sbuffer), 1, 0);
        struct StringEntry data = sbuffer.string_entries;
        for (int j = 0; j < 5; j++){
            printf("%d: %s\n", data.id_[j], data.str_[j]);
        }
        id_req = data.id_[4];
    }
    rbuffer.id = id_req;
    msgsnd(msgid, &rbuffer, sizeof(rbuffer), 0);
    return 0;
}