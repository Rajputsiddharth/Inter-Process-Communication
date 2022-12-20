

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

char *socket_path = "socketer";
int main(int argc, char *argv[])
{
    char sto_arr[5][7];
    struct sockaddr_un addr;
    char buf[100];
    int fd, cl, rc;
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
        strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path) - 1);
        unlink(socket_path);
    }
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)

    {
        perror("bind error");
        exit(-1);
    }

    if (listen(fd, 5) == -1)
    {
        perror("listen error");
        exit(-1);
    }

    if ((cl = accept(fd, NULL, NULL)) == -1)
    {
        perror("accept error");
    }
    for (int i = 0; i < 10; i++)
    {

        int read_flag = read(cl, sto_arr, sizeof(sto_arr));
        if (read_flag < 0)
        {
            perror("Unable to read from the Socket!\n");
        }
        int index = sto_arr[4][0];
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

        if (fd == -1)
        {
            perror("Unable to open the Socket!\n");
        }
        int write_flag = write(cl, &index, sizeof(index));
        if (write_flag < 0)
        {
            perror("Unable to write to the Socket!\n");
        }
    }
    return 0;
}
