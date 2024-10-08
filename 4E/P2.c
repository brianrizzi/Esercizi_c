#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// creo la struct di tipo studente inserendo il nome, il cognome e l'età
typedef struct
{
    char nome[20], cognome[20];
    int anni;
} Studente;

int main(int argc, char *argv[])
{
    if (argc > 4) // controllo gli argomenti
    {
        printf("Errore negli argomenti\n");
        exit(-1);
    }
    else
    {
        // stampo i dati della struct
        printf("NOME: %s, COGNOME: %s, ETA': %s\n", argv[1], argv[2], argv[3]);
    }
    return 0;
}