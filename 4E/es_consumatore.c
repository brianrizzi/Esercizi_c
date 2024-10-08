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

int main(int argc, char *argv[])
{
    int fd, n, a;
    FILE *f;

    fd = open("fifocmd", O_RDONLY);

    if (fd == -1)
    {
        printf("Errore nell'apertura della fifo\n");
        exit(-1);
    }
    printf("%d", n);

    if (read(fd, &n, sizeof(int)) == -1)
    {
        printf("Errore nella lettura\n");
        close(fd);
        exit(-1);
    }

    Libro biblioteca[n];

    f = fopen("filestruct.txt", "w");

    if (f == NULL)
    {
        printf("Errore nell'apertura del file\n");
        close(fd);
        exit(-1);
    }

    if (a = read(fd, biblioteca, sizeof(biblioteca)) > 0)
    {
    }
    else
    {
        printf("Errore nella lettura\n");
        close(fd);
        fclose(f);
        exit(-1);
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(f, "TITOLO: %s, AUTORE: %s, IDENTIFICATIVO: %d\n", biblioteca[i].titolo, biblioteca[i].autore, biblioteca[i].identificativo);
    }

    fclose(f);
    close(fd);
    return 0;
}