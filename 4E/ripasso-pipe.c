#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// dichiaro la struct biblioteca
typedef struct
{
    char titolo[30];
    char autore[30];
    float prezzo;

} libro;

int main(int argc, char *argv[])
{
    int p, n;
    int fd[2];

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
    else if (p > 0) // processo padre
    {
         printf("Sono il padre. Il mio PID: %d, PID figlio: %d\n", getpid(), p);
        close(fd[0]);

        libro libro1 = {"La Luna e i falò", "Cesare Pavese", 6.99};
        write(fd[1], &libro1, sizeof(libro));

        libro libro2 = {"Il sentiero dei nidi di ragno", "Italo Calvino", 14.99};
        write(fd[1], &libro2, sizeof(libro));
        close(fd[1]);

        wait(NULL);
    }
    else if (p == 0) // processo figlio
    {
        printf("Sono il figlio. Il mio PID: %d, PID padre: %d\n", getpid(), getppid());
        close(fd[1]);

        libro libro1;
        read(fd[0], &libro1, sizeof(libro));
        printf("Titolo: %s\n", libro1.titolo);
        printf("Autore: %s\n", libro1.autore);
        printf("Prezzo: %.2f\n\n", libro1.prezzo);

        libro libro2;
        read(fd[0], &libro2, sizeof(libro));
        printf("Titolo: %s\n", libro2.titolo);
        printf("Autore: %s\n", libro2.autore);
        printf("Prezzo: %.2f\n", libro2.prezzo);

        close(fd[0]);
    }
    return 0;
}
