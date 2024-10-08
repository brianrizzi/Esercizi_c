#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ARR_SIZE 5

int main(int argc, char *argv[])
{
    int p, n, prod;
    int fd[2], num[ARR_SIZE];

    if (pipe(fd) == -1)
    {
        printf("Errore nella creazione della pipe");
        exit(-1);
    }

    p = fork(); // padre genera un figlio

    if (p < 0)
    {
        printf("Errore nella generazione del figlio");
    }
    if (p = 0) // processo figlio
    {
        printf("Sono il figlio. Il mio PID: %d, PID padre: %d\n", getpid(), getppid());
        close(fd[0]);

        for (int i = 0; i < ARR_SIZE; i++)
        {
            printf("Inserisci il %d° numero: ", i);
            scanf("%d", &num[i]);
        }

        if (write(fd[1], num, ARR_SIZE) == -1)
        {
            printf("Errore di scrittura nella pipe");
            close(fd[1]);
            exit(-1);
        }

        close(fd[1]);
    }
    else // processo padre
    {
        printf("Sono il padre. Il mio PID: %d, PID figlio: %d\n", getpid(), p);
        close(fd[0]);

        n = read(fd[0], num, ARR_SIZE);

        if (n == -1)
        {
            printf("Errore nell'apertura della pipe");
            close(fd[0]);
            exit(-1);
        }
        else
        {
            printf("Inserisci il numero da moltiplicare: ");
            scanf("%d", &prod);

            for (int i = 0; i < ARR_SIZE; i++)
            {
                printf("%d <<  %d", num[i], num[i] * prod);
            }

            close(fd[0]);
        }
    }
    return 0;
}
