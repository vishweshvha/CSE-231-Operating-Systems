#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

sem_t fork1;
sem_t fork2;
sem_t fork3;
sem_t fork4;
sem_t fork5;

void feeder1(){
    sem_wait(&fork1);
    sem_wait(&fork2);
    sleep(1);
    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 1 ate at %f with fork 1 and 2\n", current);
    sem_post(&fork1);
    sem_post(&fork2);
}

void feeder2(){
    sem_wait(&fork3);
    sem_wait(&fork2);
    sleep(1);
    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 2 ate at %f with fork 2 and 3\n", current);
    sem_post(&fork3);
    sem_post(&fork2);
}

void feeder3(){
    sem_wait(&fork3);
    sem_wait(&fork4);
    sleep(1);
    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 3 ate at %f with fork 3 and 4\n", current);
    sem_post(&fork3);
    sem_post(&fork4);
}

void feeder4(){
    sem_wait(&fork5);
    sem_wait(&fork4);
    sleep(1);
    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 4 ate at %f with fork 4 and 5\n", current);
    sem_post(&fork5);
    sem_post(&fork4);
}

void feeder5(){
    sem_wait(&fork5);
    sem_wait(&fork1);
    sleep(1);
    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 5 ate at %f with fork 5 and 1\n", current);
    sem_post(&fork5);
    sem_post(&fork1);
}

void* handler1(void* arg){
    while(1){
        sleep(1);
        feeder1();
    }
}

void* handler2(void* arg){
    while(1){
        sleep(1);
        feeder2();
    }
}

void* handler3(void* arg){
    while(1){
        sleep(1);
        feeder3();
    }
}

void* handler4(void* arg){
    while(1){
        sleep(1);
        feeder4();
    }
}

void* handler5(void* arg){
    while(1){
        sleep(1);
        feeder5();
    }
}

int main()
{
    sem_init(&fork1, 0, 1);
    sem_init(&fork2, 0, 1);
    sem_init(&fork3, 0, 1);
    sem_init(&fork4, 0, 1);
    sem_init(&fork5, 0, 1);

    pthread_t t1, t2, t3, t4, t5;
    pthread_create(&t1, NULL, handler1, NULL);
    pthread_create(&t2, NULL, handler2, NULL);
    pthread_create(&t3, NULL, handler3, NULL);
    pthread_create(&t4, NULL, handler4, NULL);
    pthread_create(&t5, NULL, handler5, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);

    sem_destroy(&fork1);
    sem_destroy(&fork2);
    sem_destroy(&fork3);
    sem_destroy(&fork4);
    sem_destroy(&fork5);
    return 0;
}