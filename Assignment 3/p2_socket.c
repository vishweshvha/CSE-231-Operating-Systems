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
#include <netinet/in.h>

#include "utils.h"

int main(){
    int new_socket = 0;
    struct sockaddr_in server_address;
    char buffer[sizeof(struct StringEntry)];
    if ((new_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket creation error \n");
        return EXIT_FAILURE ;
    }
   
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(2000);
       
    
   
    if (connect(new_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        printf("\nConnection Failed \n");
        return EXIT_FAILURE ;
    }

    int id_req = 0;
    send(new_socket, (char *) &id_req, sizeof(id_req), 0);

    for(int i = 0; i < 50; i += 5){
        read(new_socket, buffer, sizeof(struct StringEntry));
        struct StringEntry *data = (struct StringEntry*) buffer;
        for (int j = 0; j < 5; j++){
            printf("%d: %s\n", data->id_[j], data->str_[j]);
        }
        id_req = data->id_[4];
        send(new_socket, (char *) &id_req, sizeof(id_req), 0);
    }
    
    close(new_socket);
    return 0;
}