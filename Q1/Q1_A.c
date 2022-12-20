#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

#define N 5

pthread_mutex_t sticks[N];

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
        pthread_mutex_lock(&sticks[left(*i)]);
        pthread_mutex_lock(&sticks[right(*i)]);
        printf("Philosopher %d has taken the fork %d and %d\n", *i,left(*i),right(*i));
        }
        else{
        pthread_mutex_lock(&sticks[right(*i)]);
        pthread_mutex_lock(&sticks[left(*i)]);
        printf("Philosopher %d has taken the fork %d and %d\n", *i,left(*i),right(*i));
        }
    
        printf("Philosopher %d is eating\n", *i);
        sleep(1);
        printf("Philosopher %d has put down the fork %d and %d\n", *i,left(*i),right(*i));
        pthread_mutex_unlock(&sticks[left(*i)]);
        pthread_mutex_unlock(&sticks[right(*i)]);

    }
}



 int main(){
    pthread_t phil[N];
    for (int i = 0; i < N; i++){
        pthread_mutex_init(&sticks[i], NULL);
    }
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
