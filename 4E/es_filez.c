#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    FILE* f;
    int n;
    char c;

    f = fopen("Biblioteca.c", "r");

    if (f == NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(-1);
    }

    if(argc != 2)
    {
        printf("Inserisci il numero corretto di elementi\n");
        exit(-1);
    }

    n = atoi(argv[1]);

    fseek(f, n, SEEK_SET);

    c = getc(f);

    printf("%c\n", c);
    fclose(f);
    return 0;
}
