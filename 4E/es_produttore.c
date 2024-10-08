#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

typedef struct
{
    char titolo[20], autore[20];
    int identificativo;
} Libro;

void Inserimento(Libro biblioteca[], int nLibri)
{
    srand(time(NULL));

    for (int i = 0; i < nLibri; i++)
    {

        printf("Inserisci il titolo del %d° libro:\n", i + 1);
        scanf("%s", biblioteca[i].titolo);
        printf("Inserisci il nome dell'autore del %d° libro:\n", i + 1);
        scanf("%s", biblioteca[i].autore);
        biblioteca[i].identificativo = rand() % 500 + 500;
    }
}

int main(int argc, char *argv[])
{
    int n, fd;

    if (argc != 2)
    {
        printf("Inserisci il numero corretto di parametri\n");
        exit(-1);
    }
    n = atoi(argv[1]);

    fd = open("fifocmd", O_WRONLY);

    if (fd == -1)
    {
        printf("Errore nell'apertura della fifo\n");
        exit(-1);
    }

    Libro biblioteca[n];

    Inserimento(biblioteca, n);

    if (write(fd, &n, sizeof(int)) == -1)
    {
        printf("Errore nella scrittura\n");
        close(fd);
        exit(-1);
    }
    if (write(fd, biblioteca, sizeof(biblioteca)) == -1)
    {
        printf("Errore nella scrittura\n");
        close(fd);
        exit(-1);
    }
    close(fd);
    return 0;
}