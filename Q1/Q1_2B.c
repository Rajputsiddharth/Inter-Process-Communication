#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

#define N 5

sem_t sticks[N];
sem_t bowl;
int bowl_count = 0;

//To calculate the right philosopher we use the following functions
int right(int i){
    return ((i+1)%N);
}

//To calculate the left philosopher we use the following functions
int left(int i){
    return ((i)%N);
}

void *philosopher(void *arg){
    int *i = (int *)arg;
    while(1){
        printf("Philosopher %d is thinking\n", *i);
        sleep(1);
        if(*i == 0){
        sem_wait(&sticks[left(*i)]);
        sem_wait(&sticks[right(*i)]);
        printf("Philosopher %d has taken the fork %d and %d\n", *i,left(*i),right(*i));
        sem_wait(&bowl);
        bowl_count++;
        printf("Philosopher %d has taken the bowl,the number of bowls remaining is %d\n", *i,2-bowl_count);
        }
        else{
        sem_wait(&sticks[right(*i)]);
        sem_wait(&sticks[left(*i)]);
        printf("Philosopher %d has taken the fork %d and %d\n", *i,left(*i),right(*i));
        sem_wait(&bowl);
        bowl_count++;
        printf("Philosopher %d has taken the bowl,the number of bowls remaining is %d\n", *i,2-bowl_count);
        }
    
        printf("Philosopher %d is eating\n", *i);
        sleep(1);
        sem_post(&bowl);
        bowl_count--;
        printf("Philosopher %d has put down the bowl,the number of bowls remaining is %d\n", *i,2-bowl_count);
        printf("Philosopher %d has put down the fork %d and %d\n", *i,left(*i),right(*i));
        sem_post(&sticks[left(*i)]);
        sem_post(&sticks[right(*i)]);

    }
}



 int main(){
    pthread_t phil[N];
    for (int i = 0; i < N; i++){
        sem_init(&sticks[i], 0, 1);
    }
    sem_init(&bowl, 0, 2);//2 bowls
    int temp[N];
    for(int i = 0; i < N; i++){
        temp[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &temp[i]);
    }
 
    for (int i = 0; i < N; i++){
        pthread_join(phil[i], NULL);
    }

    return 0;
 }
