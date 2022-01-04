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

sem_t sauce1;
sem_t sauce2;
sem_t sauce3;
sem_t sauce4;


void feeder1(){
    sem_wait(&fork1);
    int s = 0;
    if(sem_trywait(&sauce1) == 0){
        sleep(1);
        sem_post(&sauce1);
        s = 1;
    }

    else if(sem_trywait(&sauce2) == 0){
        sleep(1);
        sem_post(&sauce2);
        s = 2;
    }

    else if(sem_trywait(&sauce3) == 0){
        sleep(1);
        sem_post(&sauce3);
        s = 3;
    }

    else if(sem_trywait(&sauce4) == 0){
        sleep(1);
        sem_post(&sauce4);
        s = 4;
    }

    else{
        sem_trywait(&sauce1);
        s = 1;
    }

    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 1 ate sauce %d at %f with fork 1\n", s, current);
    sem_post(&fork1);
}

void feeder2(){
    sem_wait(&fork2);
    int s = 0;
    if(sem_trywait(&sauce1) == 0){
        sleep(1);
        sem_post(&sauce1);
        s = 1;
    }

    else if(sem_trywait(&sauce2) == 0){
        sleep(1);
        sem_post(&sauce2);
        s = 2;
    }

    else if(sem_trywait(&sauce3) == 0){
        sleep(1);
        sem_post(&sauce3);
        s = 3;
    }

    else if(sem_trywait(&sauce4) == 0){
        sleep(1);
        sem_post(&sauce4);
        s = 4;
    }

    else{
        sem_trywait(&sauce1);
        s = 1;
    }

    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 2 ate sauce %d at %f with fork 2\n", s, current);
    sem_post(&fork2);
}

void feeder3(){
    sem_wait(&fork3);
    int s = 0;
    if(sem_trywait(&sauce1) == 0){
        sleep(1);
        sem_post(&sauce1);
        s = 1;
    }

    else if(sem_trywait(&sauce2) == 0){
        sleep(1);
        sem_post(&sauce2);
        s = 2;
    }

    else if(sem_trywait(&sauce3) == 0){
        sleep(1);
        sem_post(&sauce3);
        s = 3;
    }

    else if(sem_trywait(&sauce4) == 0){
        sleep(1);
        sem_post(&sauce4);
        s = 4;
    }

    else{
        sem_trywait(&sauce1);
        s = 1;
    }

    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 3 ate sauce %d at %f with fork 3\n", s, current);
    sem_post(&fork3);
}

void feeder4(){
    sem_wait(&fork4);
    int s = 0;
    if(sem_trywait(&sauce1) == 0){
        sleep(1);
        sem_post(&sauce1);
        s = 1;
    }

    else if(sem_trywait(&sauce2) == 0){
        sleep(1);
        sem_post(&sauce2);
        s = 2;
    }

    else if(sem_trywait(&sauce3) == 0){
        sleep(1);
        sem_post(&sauce3);
        s = 3;
    }

    else if(sem_trywait(&sauce4) == 0){
        sleep(1);
        sem_post(&sauce4);
        s = 4;
    }

    else{
        sem_trywait(&sauce1);
        s = 1;
    }

    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 4 ate sauce %d at %f with fork 4\n", s, current);
    sem_post(&fork4);
}

void feeder5(){
    sem_wait(&fork5);
    int s = 0;
    if(sem_trywait(&sauce1) == 0){
        sleep(1);
        sem_post(&sauce1);
        s = 1;
    }

    else if(sem_trywait(&sauce2) == 0){
        sleep(1);
        sem_post(&sauce2);
        s = 2;
    }

    else if(sem_trywait(&sauce3) == 0){
        sleep(1);
        sem_post(&sauce3);
        s = 3;
    }

    else if(sem_trywait(&sauce4) == 0){
        sleep(1);
        sem_post(&sauce4);
        s = 4;
    }

    else{
        sem_trywait(&sauce1);
        s = 1;
    }

    double current = (double) clock();
    current = current/CLOCKS_PER_SEC;
    printf("Philosopher 5 ate sauce %d at %f with fork 5\n", s, current);
    sem_post(&fork5);
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

    sem_init(&sauce1, 0, 1);
    sem_init(&sauce2, 0, 1);
    sem_init(&sauce3, 0, 1);
    sem_init(&sauce4, 0, 1);

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

    sem_destroy(&sauce1);
    sem_destroy(&sauce2);
    sem_destroy(&sauce3);
    sem_destroy(&sauce4);
    return 0;
}