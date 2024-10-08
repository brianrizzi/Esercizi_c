#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_DIM 1024

int main(int argc, char *argv[])
{
    int p, n;
    int fd[2];
    char buffer[BUFFER_DIM];
    FILE *origine, *destinazione;

    if (pipe(fd) == -1)
    {
        printf("Errore nella creazione della pipe\n");
        exit(-1);
    }

    p = fork();

    if (p < 0) // errore
    {
        printf("Errore nella generazione del processo figlio\n");
        exit(-1);
    }

    if (p > 0) // processo padre
    {
        close(fd[0]);

        if (argc != 3)
        {
            fprintf(stderr, "Inserisci il numero di parametri:\n");
            exit(-1);
        }

        origine = fopen(argv[1], "r");

        if (origine == NULL)
        {
            printf("Errore nell'apertura del file di origine\n");
            exit(-1);
        }

        while ((n = fread(buffer, 1, sizeof(buffer), origine)) > 0)
        {
            write(fd[1], buffer, n);
        }

        fclose(origine);
        close(fd[1]);
    }
    else // processo figlio
    {
        close(fd[1]);

        destinazione = fopen(argv[2], "w");

        if (destinazione == NULL)
        {
            printf("Errore nell' apertura del file di destinazione\n");
            close(fd[0]);

            exit(-1);
        }

        while ((n = read(fd[0], buffer, sizeof(buffer))) > 0)
        {
            fwrite(buffer, 1, n, destinazione); 
        }
        fclose(destinazione);
        close(fd[0]); 
    }
    return 0;
}