
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<errno.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <math.h>
#include <time.h>

char *socket_path = "socketer";
int main(int argc, char *argv[])
{   //Sending the strings to the FIFO file
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
    
    struct timespec startA, endA;
    clock_gettime(CLOCK_REALTIME, &startA);
    //Sending the strings to the FIFO file and receiving the index of the maximum string
    int index=0;


    struct sockaddr_un addr;
    char buf[100];
    int fd, rc;
    if (argc > 1)
        socket_path = argv[1];
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
    {
        perror("socket error");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    if (*socket_path == '\0')
    {
        *addr.sun_path = '\0';
        strncpy(addr.sun_path + 1, socket_path + 1,
                sizeof(addr.sun_path) - 2);
    }
    else
    {
        strncpy(addr.sun_path, socket_path,
                sizeof(addr.sun_path) - 1);
    }
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
    {
        perror("connect error");
        exit(-1);
    }

    while (1)
    {
        for (int i = index; i < index + 5; i++)
        {
            strcpy(pass_arr[i - index], send_arr[i]);
        }

        if (fd == -1)
        {
            perror("Unable to open the Socket!\n");
        }

        int write_flag = write(fd, pass_arr, sizeof(pass_arr));
        if (write_flag < 0)
        {
            perror("Unable to write to the Socket!\n");
        }
        if (fd == -1)
        {
            perror("Unable to open the Socket!\n");
        }
        int read_flag = read(fd, &ret_id, sizeof(ret_id));

        if (read_flag < 0)
        {
            perror("Unable to read from the Socket!\n");
        }

        printf("The index of the maximum string is %d\n", ret_id);
        index = ret_id;
        index = index + 1;

        if (index == 50)
        {
            break;
        }
    }
    clock_gettime(CLOCK_REALTIME, &endA);
    double timeA = (endA.tv_sec - startA.tv_sec) * 1000000000 + (endA.tv_nsec - startA.tv_nsec);
    printf("Time taken by process is: %lf\n", (timeA/(long long int)pow(10,9)));
    return 0;
}
