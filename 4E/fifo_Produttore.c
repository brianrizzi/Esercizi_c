#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h> //serve per aprire le FIFO

#define DIM_ARRAY 5

int main(int argc, char *argv[])
{
    int fd, numeri[DIM_ARRAY];
    srand((unsigned int)getpid());

    if ((fd = open("sum", O_WRONLY)) < 0)
    {
        printf("Errore nell'apertura della FIFO");
        exit(-1);
    }
    for (int i = 0; i < DIM_ARRAY; i++)
    {
        numeri[i] = rand() % 100;
    }
    if (write(fd, numeri, sizeof(numeri)) == -1)
    {
        printf("Errore in scrittura nela FIFO\n");
        exit(-1);
    }
    close(fd);

    return 0;
}