
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include<string.h>
#include<stdlib.h>


int main(){
    //Initialising Storage array
    char sto_arr[5][7];

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
    char* str;
    str=shared_mem;
    for (int i = 0; i < 5; i++)
    {   
        strcpy(sto_arr[i], str);
        str += 7;
    }
    for (int i = 0; i < 5; i++)
    {
        char print_arr[6];
        for (int k = 0; k < 5; k++)
        {
            print_arr[k] = sto_arr[i][k + 1];
        }
        print_arr[5] = '\0';
        printf("ID: %d String: %s\n", sto_arr[i][0], print_arr);
    }
    printf("\n");
    int ret=sto_arr[4][0];
    char retc=(char)(ret+48);
    
    shared_mem[0]=retc;
    shared_mem[1]='\0';
    
    return 0;
}
