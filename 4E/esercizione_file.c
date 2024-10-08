#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define NOME "miafifo"
#define SIZE_BUFFER 2048

int main(int argc, char *argv[])
{
    int fd;
    if (mkfifo(NOME, 0777) == -1)
    {
        if (errno != EEXIST) // controlla se la fifo è già esistente
        {
            printf("Errore nella creazione della pipe\n");
            exit(-1);
        }
    }

    if ((fd = open(NOME, O_WRONLY)) == -1)
    {
        printf("Errore nell'apertura della fifo\n");
        exit(-1);
    }

    FILE *f;
    char buffer[SIZE_BUFFER];
    int n;

    if ((f = fopen("Biblioteca.c", "r")) == NULL)
    {
        printf("Errore nell'apertura del file\n");
        close(fd);
        exit(-1);
    }

    while ((n = fread(buffer, 1, SIZE_BUFFER, f)) > 0)
    {
        if (write(fd, buffer, n) == -1)
        {
            printf("Errore nella scrittura\n");
            close(fd);
            fclose(f);
            exit(-1);
        }
    }
    close(fd);
    fclose(f);
    return 0;
}