#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SIZE_ARRAY 20

int main(int argc, char *argv[])
{
    int p, fd[2], num[SIZE_ARRAY];
    // int *num;

    if (pipe(fd) == -1)
    {
        printf("Errore nella creazione della pipe\n");
        exit(-1);
    }
    // num = (int *)malloc(sizeof(int) * SIZE_ARRAY);

    p = fork();

    if (p < 0)
    {
        printf("Errore nella creazione della fork\n");
        // free(num);
        exit(-1);
    }
    else if (p > 0) // processo padre
    {
        close(fd[0]); // chiusura della pipe in lettura
        srand(time(NULL));

        for (int i = 0; i < SIZE_ARRAY; i++)
        {
            num[i] = rand() % 100 + 1;
        }

        if (write(fd[1], num, sizeof(num)) == -1)
        {
            printf("Errore nella scrittura\n");
            close(fd[1]); // chiusura della pipe in scrittura
            exit(-1);
        }

        // if (write(fd[1], num, sizeof(int) * SIZE_ARRAY) == -1)
        // {
        //     printf("Errore nella scrittura\n");
        //     close(fd[1]); // chiusura della pipe in scrittura
        //     free(num);
        //     exit(-1);
        // }
        wait();
        close(fd[1]); // chiusura della pipe in scrittura
    }
    else // processo figlio
    {
        close(fd[1]); // chiusura della pipe in scrittura

        if (read(fd[0], num, sizeof(num)) == -1)
        {
            printf("Errore nella lettura\n");
            close(fd[0]);
            exit(-1);
        }
        // if (read(fd[0], num, sizeof(int) * SIZE_ARRAY) == -1)
        // {
        //     printf("Errore nella lettura\n");
        //     close(fd[0]);
        //     free(num);
        //     exit(-1);
        // }

        for (int i = 0; i < SIZE_ARRAY; i++)
        {
            printf("[%d]° numero generato: %d\n", i + 1, num[i]);
        }

        close(fd[0]); // chiusura della pipe in lettura
    }
    // free(num);

    return 0;
}
