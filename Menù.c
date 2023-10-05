/*Dato un array di dimensione massima pari a SHRT_MAX,
inserire in input un numero arbitrario di interi positivi.
L'inserimento termina quando viene inserito il valore -1.

Si mostri quindi un menu cosi strutturato:
    premere 1 per mostrare il contenuto dell'array
    premere 2 per inserire un elemento in coda
    premere 3 per modificare un elemento, se presente
    premere 4 per eliminare un elemento, se presente
    premere 5 per ricercare un elemento
    premere 6 per inserire un elemento in una certa posizione
    premere 7 per mostrare il contenuto dell'array all'inverso
    premere 8 per mostrare il valore massimo dell'array
    premere 0 per terminare

dopo ogni operazione il menu deve essere nuovamente mostrato.

osservazione:
SHRT_MAX è dichiarata in limits.h

Vincolo:
è obbligatorio strutturare il programma in funzioni*/

#include <stdio.h>
#include <limits.h>

int Menu_scelta()
{
    int scelta;

    printf("\npremere 1 per mostrare il contenuto dell'array\n");
    printf("premere 2 per inserire un elemento in coda\n");
    printf("premere 3 per modificare un elemento, se presente\n");
    printf("premere 4 per eliminare un elemento, se presente\n");
    printf("premere 5 per ricercare un elemento\n");
    printf("premere 6 per inserire un elemento in una certa posizione\n");
    printf("premere 7 per mostrare il contenuto dell'array all'inverso\n");
    printf("premere 8 per mostrare il valore massimo dell'array\n");
    printf("premere 0 per terminare\n");

    scanf("%d", &scelta);
    return scelta;
}

void Stampa(int numeri[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\nIl numero nella posizione %d è: %d\n", i, numeri[i]);
    }
}

int Inserimento_coda(int numeri[], int *n, int numero)
{
    numeri[*n] = numero;
    (*n)++;
    return *n;
}

int Ricerca(int numeri[], int n, int numero)
{
    for (int i = 0; i < n; i++)
    {
        if (numeri[i] == numero)
        {
            return i;
        }
    }
    return -1;
}

int Modifica(int numeri[], int posizione, int numero)
{
    numeri[posizione] = numero;
    return posizione;
}

int Elimina(int numeri[], int *n, int posizione)
{
    for (int i = posizione; i < *n; i++)
    {
        numeri[i] = numeri[i + 1];
    }
    (*n)--;
    return posizione;
}

int Inserimento_posizione(int numeri[], int *n, int posizione, int numero)
{
    for (int i = *n; i > posizione; i--)
    {
        numeri[i] = numeri[i - 1];
    }
    numeri[posizione] = numero;
    (*n)++;
    return posizione;
}

void Stampa_inverso(int numeri[], int n)
{
    for (int i = n; i >= 0; i--)
    {
        printf("\nIl numero nella posizione %d è: %d\n", i, numeri[i]);
    }
}

int Numero_massimo(int numeri[], int n)
{
    int max;
    max = numeri[0];
    for (int i = 1; i < n; i++)
    {
        if (numeri[i] > max)
        {
            max = numeri[i];
        }
    }
    return max;
}

void Menu_esecuzione(int scelta, int numeri[], int *n)
{
    if (scelta == 1)
    {
        Stampa(numeri, *n);
    }

    if (scelta == 2)
    {
        int num, posizione;
        printf("\nInserisci il numero da aggiungere nell'array: ");
        scanf("%d", &num);
        posizione = Inserimento_coda(numeri, n, num);
        printf("\nIl numero %d è stato inserito in posizione: %d\n", num, posizione - 1);
    }

    if (scelta == 3)
    {
        int num, posizione;
        printf("Inserisci il numero che vuoi sostituire: ");
        scanf("%d", &num);
        posizione = Ricerca(numeri, *n, num);

        if (posizione > -1)
        {
            printf("\nInserisci il nuovo numero: ");
            scanf("%d", &num);
            Modifica(numeri, posizione, num);
        }
        else
        {
            printf("\nIl numero scelto non è presente nell'array\n");
        }
    }

    if (scelta == 4)
    {
        int num, posizione;
        printf("Inserisci il numero che vuoi eliminare dall'array: ");
        scanf("%d", &num);
        posizione = Ricerca(numeri, *n, num);

        if (posizione > -1)
        {
            Elimina(numeri, n, posizione);
        }
        else
        {
            printf("\nIl numero scelto non è presente nell'array\n");
        }
    }

    if (scelta == 5)
    {
        int num, posizione;
        printf("Inserisci il numero che vuoi cercare: ");
        scanf("%d", &num);
        posizione = Ricerca(numeri, *n, num);

        if (posizione > -1)
        {
            printf("\nIl numero %d è stato trovato in posizione: %d\n", num, posizione);
        }
        else
        {
            printf("\nIl numero scelto non è presente nell'array\n");
        }
    }

    if (scelta == 6)
    {
        int num, posizione;
        printf("Inserisci un numero: ");
        scanf("%d", &num);
        printf("Inserisci la posizione dove inserire il numero: ");
        scanf("%d", &posizione);

        if (posizione < *n)
        {
            Inserimento_posizione(numeri, n, posizione, num);
        }
        else
        {
            printf("\nLa posizione inserita non esiste\n");
        }
    }

    if (scelta == 7)
    {
        Stampa_inverso(numeri, *n);
    }

    if (scelta == 8)
    {
        int max;
        max = Numero_massimo(numeri, *n);
        printf("\nIl numero più grande presente nell'array è: %d\n", max);
    }
}

int main(int argc, char *argv[])
{
    int cont = 0, scelta, input, numeri[SHRT_MAX];

    while (input != -1)
    {
        printf("Inserisci un numero: ");
        scanf("%d", &input);
        if (input != -1)
        {
            numeri[cont] = input;
            cont++;
        }
    }

    while (1)
    {
        scelta = Menu_scelta();

        if (scelta != 0)
        {
            Menu_esecuzione(scelta, numeri, &cont);
        }
        else
        {
            printf("\nProgramma terminato\n");
            return 0;
        }
    }
}