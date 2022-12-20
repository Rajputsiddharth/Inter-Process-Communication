#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main(){
    //Initializing the array
    char sto_arr[5][7];
    int ret_id;

    //Creating the socket
    struct sockaddr_un server_add;
    int conn_fd=socket(AF_UNIX,SOCK_STREAM,0);
    if(conn_fd==-1){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&server_add,0,sizeof(server_add));

    server_add.sun_family=AF_UNIX;

    strcpy(server_add.sun_path,"orange");
    int len=SUN_LEN(&server_add);
    int conn=bind(conn_fd,(struct sockaddr*)&server_add,len);
    if(conn==-1){
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    int lst=listen(conn_fd,0);
    if(conn==-1){
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
     for (int i = 0; i < 10; i++){
        
        int temp_fd=accept(conn_fd,NULL,NULL);
        if(conn_fd==-1){
            perror("Connection failed");
            exit(EXIT_FAILURE);
        }
        int read_flag=read(conn_fd,sto_arr,sizeof(sto_arr));
        if(read_flag<0) 
        {
            perror("Unable to read from the socket!\n");
        }

        int index = sto_arr[4][0];
        ret_id = index;
        for (int j = 0; j < 5; j++)
        {
            char print_arr[6];
            for (int k = 0; k < 5; k++)
            {
                print_arr[k] = sto_arr[j][k + 1];
            }
            print_arr[5] = '\0';
            printf("ID: %d String: %s\n", sto_arr[j][0], print_arr);
        }
        printf("\n");

        int write_flag=write(conn_fd,&ret_id,sizeof(ret_id));
        if(write_flag<0) 
        {
            perror("Unable to write to the socket!\n");
        }
    }
    printf("The connection is closed\n");
    unlink(server_add.sun_path);
    return 0;
}
