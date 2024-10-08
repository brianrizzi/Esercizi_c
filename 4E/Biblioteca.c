#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// dichiaro la struct biblioteca
typedef struct
{
    char titolo[20];
    char autore[20];
    float prezzo;

} biblioteca;

// faccio un metodo che mi permette di inserire nome, autore e prezzo per ogni libro
void Inserimento(biblioteca *libri, int nLibri)
{
    for (int i = 0; i < nLibri; i++)
    {
        printf("Inserisci il titolo del %d° libro: ", i + 1);
        scanf("%s", libri[i].titolo);
        printf("\nInserisci l'autore del %d° libro: ", i + 1);
        scanf("%s", libri[i].autore);
        printf("\nInserisci il prezzo del %d° libro: ", i + 1);
        scanf("%f", &libri[i].prezzo);
        printf("\n\n");
    }
}

// faccio un metodo che mi permette di stampare nome, autore e prezzo per ogni libro
void Stampa(biblioteca *libri, int nLibri)
{
    for (int i = 0; i < nLibri; i++)
    {
        printf("========== %d° LIBRO ==========", i + 1);
        printf("\ntitolo <<  %s", libri[i].titolo);
        printf("\nautore <<  %s", libri[i].autore);
        printf("\nprezzo <<  %.2f\n", libri[i].prezzo);
        printf("==============================\n\n");
    }
}

// faccio un metodo che mi applica uno sconto scelto dall'utente per ogni libro
void Sconto(biblioteca *libri, int nLibri)
{
    float prezzoScontato, sconto;

    printf("Inserisci lo sconto da applicare ad ogni libro: ");
    scanf("%f", &sconto);

    sconto = sconto / 100;

    for (int i = 0; i < nLibri; i++)
    {
        libri[i].prezzo = libri[i].prezzo - (libri[i].prezzo * sconto);
    }
}

// faccio un metodo che libera l'area di memoria di ogni libro

int main(int argc, char *argv[])
{

    // faccio un array di 3 libri di tipo biblioteca
    int nLibri = 3;
    biblioteca libri[3];

    // richiamo tutti i metodi
    Inserimento(libri, nLibri);
    Stampa(libri, nLibri);
    Sconto(libri, nLibri);
    Stampa(libri, nLibri);

    return 0;
}