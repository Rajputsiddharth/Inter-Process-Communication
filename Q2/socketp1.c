#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(){
    //Initializing the array
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

    //Creating the socket
    struct sockaddr_un server_add;

    int sock_fd=socket(AF_UNIX,SOCK_STREAM,0);
    if(sock_fd==-1){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&server_add,0,sizeof(server_add));
    server_add.sun_family=AF_UNIX;
    strcpy(server_add.sun_path,"orange");

    //Connecting to the server
    int len=SUN_LEN(&server_add);
    struct timespec startA, endA;
    clock_gettime(CLOCK_REALTIME, &startA);
    int index=0;
    while(1){
        int conn=connect(sock_fd,(struct sockaddr*)&server_add,len);
        if(conn==-1){
            perror("Connection failed");
            exit(EXIT_FAILURE);
        }
        for(int i = index;i<index+5;i++){
            strcpy(pass_arr[i-index],send_arr[i]);
        }

        int write_flag=write(sock_fd,pass_arr,sizeof(pass_arr));
        if(write_flag==-1) 
        {
            perror("Unable to write to the socket!\n");
        }
        int read_flag=read(sock_fd,&ret_id,sizeof(ret_id));
        if(read_flag==-1) 
        {
            perror("Unable to read from the socket!\n");
        }
        printf("The index of the maximum string is %d\n",ret_id);
        index=ret_id;
        index++;
        if(index==50){
            break;
        }

    }
    clock_gettime(CLOCK_REALTIME, &endA);
    double timeA = (endA.tv_sec - startA.tv_sec) * 1000000000 + (endA.tv_nsec - startA.tv_nsec);
    printf("Time taken by process is: %lf\n", (timeA/(long long int)pow(10,9)));
    return 0;
}
