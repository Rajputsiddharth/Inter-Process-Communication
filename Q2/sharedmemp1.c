
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <math.h>
int main()
{
    // Initializing the array
    char send_arr[50][7];
    int ret_id;
    char pass_arr[5][7];

    // Storing the id as 1st element
    for (int i = 0; i < 50; i++)
    {
        send_arr[i][0] = i;
    }

    // Storing the strings
    for (int i = 0; i < 50; i++)
    {
        for (int j = 1; j <= 5; j++)
        {
            send_arr[i][j] = (rand() % 26) + 97;
        }
        send_arr[i][6] = '\0';
    }

    //Creating the shared memory segment
    int shmid;
    key_t key;
    key = ftok("gen1key", 65);

    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    //attaching the shared memory segment to data space
    char *shared_mem = shmat(shmid, (void *)0, 0);
    if (shared_mem == (char *)(-1))
    {
        perror("shmat");
        exit(1);
    }
    struct timespec startA, endA;
    clock_gettime(CLOCK_REALTIME, &startA);
    char* str;
    str=shared_mem;
    int index = 0;
    for (int i = index; i < index + 5; i++){
        strcpy(pass_arr[i - index], send_arr[i]);
    }
    for (int i = 0; i < 5; i++)
    {   
        strcpy(str, pass_arr[i]);
        str += 7;
    }
    while (1)
    {
        pid_t pid = fork();
        if(pid==0){
            printf("Child process\n");
            execlp("./s2", "s2", NULL);
        }
        else{
            wait(NULL);
            printf("Parent process\n");
            ret_id = *shared_mem-48;
            printf("The index of the maximum string is %d\n", ret_id);
            index = ret_id + 1;
            if (index >= 50)
            {
                break;
            }
            for (int i = index; i < index + 5; i++)
            {
                strcpy(pass_arr[i - index], send_arr[i]);
            }
            str=shared_mem;
            for (int i = 0; i < 5; i++)
            {
                strcpy(str, pass_arr[i]);
                str += 7;
            }

        }
    }
    //detach from shared memory
    if (shmdt(shared_mem) == -1)
    {
        perror("shmdt");
        exit(1);
    }
    //destroy the shared memory segment
    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        perror("shmctl");
        exit(1);
    }
      clock_gettime(CLOCK_REALTIME, &endA);
    double timeA = (endA.tv_sec - startA.tv_sec) * 1000000000 + (endA.tv_nsec - startA.tv_nsec);
    printf("Time taken by process is: %lf\n", (timeA/(long long int)pow(10,9)));
    return 0;
}
