#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>

float averages[6] = {0,0,0,0,0,0};
float ct = 0;

void average(char sec){
    int student_record = open("student_record.csv", O_RDONLY);   
    float avg = 0, count = 0;
    float sum[6] = {0,0,0,0,0,0};
    int row = 0, column = 0, char_ct = 0;
    char line[100][50];
    char *data = malloc(sizeof(char)*2000);

    read(student_record, data, 1000);
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
        averages[i] += sum[i];
    }
    ct += count;
    printf("\n");
}

void *averageA(void *vargp)
{
    average('A');
}

void *averageB(void *vargp)
{
    sleep(1);
    printf("\n");
    average('B');
}

void *averageAll(void *vargp)
{   
    sleep(2);
    printf("\nAverages for both Sections");
    for(int i=0; i<6; i++){
        printf("\nAssignment %d ", i+1);
        printf("Average: %0.2f", (averages[i]/ct));
    }
    printf("\n");
}

int main()
{
    pthread_t p1, p2, p3;
    pthread_create(&p1, NULL, averageA, NULL);
    pthread_create(&p2, NULL, averageB, NULL);
    pthread_create(&p3, NULL, averageAll, NULL);

    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);

    return 0;
}