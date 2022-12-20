#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
 
#define N 5

//This is used to describe the state of each philosopher
struct State {
    int thinking;
    int not_eating;
    int eating;
};


//To calculate the right philosopher we use the following functions
int right(int i){
    return (i+1)%N;
}

//To calculate the left philosopher we use the following functions
int left(int i){
    return (i+N-1)%N;
}
 
//To keep a track in which state the philosopher is in we use the array s
struct State s[5];


//Defining the semaphores
sem_t mutex;
sem_t semap[N];


//To put the philosophers in a thinking state we use the following function
void think(int numb){
    printf("Philosopher %d is thinking\n", numb+1);
       s[numb].thinking = 1;
       s[numb].not_eating = 0;
       s[numb].eating = 0;
    sleep(1);
}


//to test if the philosopher can eat and if the neighbouring philosophers are eating or not
void checking(int numb)
{
    if (s[numb].not_eating == 1
        && s[left(numb)].eating == 0
        && s[right(numb)].eating == 0) {
        s[numb].eating = 1;
        s[numb].not_eating = 0;
        s[numb].thinking = 0;
        sleep(2);
 
        printf("Philosopher %d uses fork %d and %d\n",
                      numb + 1, left(numb) + 1, numb + 1);
 
        printf("Philosopher %d is Eating\n", numb + 1);
        sem_post(&semap[numb]);
    }
}

//To make the philosopher eat we use the following function
void eat(int numb)
{
 
    sem_wait(&mutex);
    s[numb].thinking = 0;
    s[numb].not_eating = 1;
    s[numb].eating = 0;
 
    printf("Philosopher %d wants to eat\n", numb + 1);
    checking(numb);
    sem_post(&mutex);
    sem_wait(&semap[numb]);
    sleep(1);
}
 
//To make the philosopher stop eating and bring him back to the thinking state we use the following function
void stop_eat(int numb)
{
 
    sem_wait(&mutex);
    s[numb].thinking = 1;
    s[numb].not_eating = 0;
    s[numb].eating = 0;
 
    printf("Philosopher %d stops using %d and %d\n",
           numb + 1, left(numb) + 1, numb + 1);

    printf("Philosopher %d is thinking\n", numb + 1);
 
    checking(left(numb));
    checking(right(numb));
 
    sem_post(&mutex);
}


//Phiosopher function which gives the philosopher a number and makes him think and eat
void* philosopher(void* num)
{
    while (1) {
        int* i = num;
        int deref = *i;
        think(deref);
        eat(deref);
        stop_eat(deref);
    }
}
 
int main()
{
    pthread_t phil_thread[5];
 
    // initialize the semaphores
    sem_init(&mutex, 0, 1);

    int temp[N];
    for (int i = 1; i <=N; i++){
        temp[i-1] = i-1;
        sem_init(&semap[i-1], 0, 0);
    }
 
    for (int i = 1; i <=N; i++) {
        pthread_create(&phil_thread[i-1], NULL,
                       philosopher, &temp[i-1]);
    }
 
    for (int i = 1; i <=N; i++){
        pthread_join(phil_thread[i-1], NULL);
    }
}
