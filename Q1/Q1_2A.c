#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#define N 5

bool sticks[N]; //initially all false
bool bowls[2];  //initially all false
int bowl_count = 0;

// To calculate the right philosopher we use the following functions
int right(int i)
{
    return ((i + 1) % N);
}

// To calculate the left philosopher we use the following functions
int left(int i)
{
    return ((i) % N);
}

void *philosopher(void *arg)
{
    int *i = (int *)arg;
    while (1)
    {
        printf("Philosopher %d is thinking\n", *i);
        sleep(1);
        if (*i == 0 && sticks[left(*i)] == false && sticks[right(*i)] == false && bowls[bowl_count] == false && bowl_count < 2)
        {
            sticks[left(*i)] = true;
            sticks[right(*i)] = true;

            printf("Philosopher %d has taken the fork %d and %d\n", *i, left(*i), right(*i));
            
            bowls[bowl_count] = true;
            bowl_count++;
            printf("Philosopher %d has taken the bowl,the number of bowls remaining is %d\n", *i,2-bowl_count);
            printf("Philosopher %d is eating\n", *i);
            sleep(1);
            bowls[bowl_count] = false;
            bowl_count--;
            printf("Philosopher %d has put down the bowl,the number of bowls remaining is %d\n", *i,2-bowl_count);
            printf("Philosopher %d has put down the fork %d and %d\n", *i, left(*i), right(*i));
            sticks[left(*i)] = false;
            sticks[right(*i)] = false;
        }
        else if (*i != 0 && sticks[right(*i)] == false && sticks[left(*i)] == false)
        {
            sticks[right(*i)] = true;
            sticks[left(*i)] = true;
            printf("Philosopher %d has taken the fork %d and %d\n", *i, left(*i), right(*i));
            bowls[bowl_count] = true;
            bowl_count++;
            printf("Philosopher %d has taken the bowl,the number of bowls remaining is %d\n", *i,2-bowl_count);
            printf("Philosopher %d is eating\n", *i);
            sleep(1);
            bowls[bowl_count] = false;
            bowl_count--;
            printf("Philosopher %d has put down the bowl,the number of bowls remaining is %d\n", *i,2-bowl_count);
            printf("Philosopher %d has put down the fork %d and %d\n", *i, left(*i), right(*i));
            sticks[left(*i)] = false;
            sticks[right(*i)] = false;
        }
    }
}

int main()
{
    pthread_t phil[N];
    for (int i = 0; i < N; i++)
    {
        sticks[i] = false;
    }
    for (int i = 0; i < 2; i++)
    {
        bowls[i] = false;
    }
    int temp[N];
    for (int i = 0; i < N; i++)
    {
        temp[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &temp[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(phil[i], NULL);
    }

    return 0;
}
