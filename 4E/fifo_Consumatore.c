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
    int fd, numeri[DIM_ARRAY], somma = 0;

    if ((fd = open("sum", O_RDONLY)) < 0)
    {
        perror("Errore nell'apertura della FIFO");
        exit(-1);
    }
    if (read(fd, numeri, sizeof(numeri)) == -1)
    {
        printf("Errore in lettura nela FIFO\n");
        exit(-1);
    }
    for (int i = 0; i < DIM_ARRAY; i++)
    {
        somma += numeri[i];
    }

    printf("La sommma totale dei 5 numeri è: %d\n", somma);

    close(fd);

    return 0;
}