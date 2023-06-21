#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

int main()
{
    char *path = "./fifofile";
    mkfifo(path, 0666);
    char sto_arr[5][7];
    for (int i = 0; i < 10; i++)
    {
        int fd = open("./fifofile", O_RDONLY);

        if (fd == -1)
        {
            perror("Unable to open the FIFO!\n");
        }

        int read_flag = read(fd, sto_arr, sizeof(sto_arr));
        if (read_flag < 0)
        {
            perror("Unable to read from the FIFO!\n");
        }
        close(fd);
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


        fd = open("./fifofile", O_WRONLY);
        if (fd == -1)
        {
            perror("Unable to open the FIFO!\n");
        }
        int write_flag = write(fd, &index, sizeof(index));
        if (write_flag < 0)
        {
            perror("Unable to write to the FIFO!\n");
        }
        close(fd);

    }
    return 0;
}
