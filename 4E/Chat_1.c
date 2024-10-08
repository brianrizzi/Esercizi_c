#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048
#define FIFO_1 "firstFifo.fifo"

int main(int argc, char *argv[])
{
    int fd, p, n;
    char buffer[BUFFER_SIZE];

    if (mkfifo(FIFO_1, 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Errore nella creazione della fifo\n");
            exit(-1);
        }
    }

    p = fork();

    if (p < 0)
    {
        printf("Errore nella creazione della fork\n");
        close(fd);
        exit(-1);
    }
    else if (p > 0)
    {
        if ((fd = open(FIFO_1, O_WRONLY)) == -1)
        {
            printf("Errore nell'apertura della fifo in scrittura\n");
            close(fd);
            exit(-1);
        }
        else
        {
            do
            {
                if ((strlen(buffer) > 0) && (buffer[strlen(buffer) - 1] == '\n'))
                {
                    buffer[strlen(buffer) - 1] = '\0';
                }
                write(fd, buffer, strlen(buffer));

            } while (strcmp(buffer, "HALT"));
        }
    }
    else if (p == 0)
    {
        if ((fd = open(FIFO_1, O_RDONLY)) == -1)
        {
            printf("Errore nell'apertura della fifo in lettura\n");
            close(fd);
            exit(-1);
        }
        while ((n = read(fd, buffer, BUFFER_SIZE)) > 0)
        {
            if (n != BUFFER_SIZE)
            {
                buffer[n] = '\0';
            }
            if (strcmp(buffer, "HALT") == 0)
            {
                break;
            }
        }
    }
    close(fd);
    return 0;
}