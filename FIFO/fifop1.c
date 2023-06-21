#include<sys/types.h>
#include<stdio.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <math.h>
#include <time.h>

int main(){
    //Making a FIFO file
    char *path="./fifofile";
    mkfifo(path,0666);

    //Sending the strings to the FIFO file
    char send_arr[50][7];
    int ret_id;
    char pass_arr[5][7];

    //Storing the id as 1st element
    for(int i=0; i<50;i++){
        send_arr[i][0]=i;
    }

    //Storing the strings
    for(int i=0; i<50;i++){
        for (int j=1;j<=5;j++){
            send_arr[i][j]=(rand()%26)+97;
        }
        send_arr[i][6]='\0';
    }

    //Sending the strings to the FIFO file and receiving the index of the maximum string
    int index=0;
    struct timespec startA, endA;
    clock_gettime(CLOCK_REALTIME, &startA);
    while(1){
    for(int i = index;i<index+5;i++){
        strcpy(pass_arr[i-index],send_arr[i]);
    }
    int fd=open("./fifofile",O_WRONLY);

    if(fd == -1) 
    {
        perror("Unable to open the FIFO!\n");
    }

    int write_flag=write(fd,pass_arr,sizeof(pass_arr));
    if(write_flag<0) 
    {
        perror("Unable to write to the FIFO!\n");
    }
    close(fd);
    fd=open("./fifofile",O_RDONLY);
    if(fd == -1) 
    {
        perror("Unable to open the FIFO!\n");
    }
    int read_flag=read(fd,&ret_id,sizeof(ret_id));

    if(read_flag<0) 
    {
        perror("Unable to read from the FIFO!\n");
    }
   
    printf("The index of the maximum string is %d\n",ret_id);
    index=ret_id;
    close(fd);
    index=index+1;
    
    if(index==50){
        break;
    }
    }
    clock_gettime(CLOCK_REALTIME, &endA);
    double timeA = (endA.tv_sec - startA.tv_sec) * 1000000000 + (endA.tv_nsec - startA.tv_nsec);
    printf("Time taken by process is: %lf\n", (timeA/(long long int)pow(10,9)));
    return 0;
}
