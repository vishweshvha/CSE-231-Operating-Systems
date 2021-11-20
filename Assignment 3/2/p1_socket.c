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
    srand(time(NULL));
    char string_array[50][MAX_STRING_LENGTH];
    for(int i = 0; i < 50; i++ ){
        generate_random_string(string_array[i], MAX_STRING_LENGTH);
    }

    int func_descriptpr, new_socket;
    struct sockaddr_in socket_address;
    int len = sizeof(socket_address);
    char buffer[sizeof(struct StringEntry)];
    
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(2000);

    if ((func_descriptpr = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    if (bind(func_descriptpr, (struct sockaddr *)&socket_address, sizeof(socket_address))<0){
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(func_descriptpr, 3) < 0){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(func_descriptpr, (struct sockaddr *)&socket_address, (socklen_t*)&len))<0){
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    while(1) {
        struct StringEntry string_entries;
        int ret = read(new_socket, buffer, sizeof(struct StringEntry));
        if (ret==-1){
            perror("accept");
            continue;
        } else if (ret == 0){
            break;
        }
        
        int id_req = *((int *)buffer);
        printf("ID: %d\n", id_req);

        if (id_req > 0) {
            id_req += 1;
        }
        
        for (int i=id_req; i<id_req+5; i++) {
            string_entries.id_[i - id_req] = i;
            strncpy(string_entries.str_[i - id_req], string_array[i], MAX_STRING_LENGTH);
        }

        send(new_socket, (char *) &string_entries, sizeof(string_entries), 0);
    }

    close(new_socket);
    return 0;
}