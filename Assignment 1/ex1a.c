#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>

void average(char sec){
    int student_record = open("student_record.csv", O_RDONLY);   
    float avg = 0, count = 0;
    float sum[6] = {0,0,0,0,0,0};
    int row = 0, column = 0, char_ct = 0;
    char line[100][50];
    char *data = malloc(sizeof(char)*2000);

    read(student_record, data, 2000);
    close(student_record);

    while(data[char_ct]){
        if(data[char_ct] == '\n') row++;
        char_ct++;
    } 
    
    char* lines = strtok(data, "\n");

    for(int i=0; i<row; i++){
        lines = strtok(NULL, "\n");
        strcpy(line[i], lines);
    }

    for(int i=0; i<row; i++){
        column = 0;
    
        char* value = strtok(line[i], ",");
        while(value){
            if ((column == 1) && (*value!=sec)) break;
            if ((column == 1) && (*value==sec)) count++;
            if (column == 2) sum[0] += atoi(value);
            if (column == 3) sum[1] += atoi(value);
            if (column == 4) sum[2] += atoi(value);
            if (column == 5) sum[3] += atoi(value);
            if (column == 6) sum[4] += atoi(value);
            if (column == 7) sum[5] += atoi(value);
            value = strtok(NULL, ",");
            column++;
        }
    }

    printf("Averages for Section %c", sec);
    for(int i=0; i<6; i++){
        avg = sum[i]/count;
        printf("\nAssignment %d ", i+1);
        printf("Average: %0.2f", avg);
    }
    printf("\n");
}

int main (){
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0){
        average('A');
        exit(1);
    }

    waitpid(pid, &status, 0);
    printf("\n");
    average('B');
    return(0);
}