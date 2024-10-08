#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define ARRAY_DIM 10
#define FUNCTIONS 10

int arr[ARRAY_DIM];
int arrDim;

void generazione(int arr[], int dim)
{
    srand(time(NULL));

    for (int i = 0; i < dim; i++)
    {
        arr[i] = (rand() % 50) + 1;
    }
}

int menu(char *arr[])
{
    int scelta;

    do
    {
        for (int i = 0; i < FUNCTIONS; i++)
        {
            printf("[%d] <<  %s\n", i + 1, arr[i]);
        }
        scanf("%d", &scelta);

        if (scelta < 1 || scelta > FUNCTIONS)
        {
            printf("\nErrore! Inserisci un numero compreso tra 1 e %d\n\n", FUNCTIONS);
        }
    } while (scelta < 1 || scelta > FUNCTIONS);

    return scelta;
}

void stampa(int arr[], int dim)
{
    for (int i = 0; i < dim; i++)
    {
        printf("[%d°]: %d\n", i + 1, arr[i]);
    }
}

void inverso(int arr[], int dim)
{
    for (int i = dim - 1; i >= 0; i--)
    {
        printf("[%d°]: %d\n", i + 1, arr[i]);
    }
}

int somma(int arr[], int dim)
{
    int s = 0;

    for (int i = 0; i < dim; i++)
    {
        s += arr[i];
    }
    return s;
}

float media(int arr[], int dim)
{
    return (float)somma(arr, dim) / dim;
}

void pari(int arr[], int dim)
{
    int n = 0;

    for (int i = 0; i < dim; i++)
    {
        if (arr[i] % 2 == 0)
        {
            printf("[%d°]: %d\n", n + 1, arr[i]);
            n++;
        }
    }
}

void dispari(int arr[], int dim)
{
    int n = 0;

    for (int i = 0; i < dim; i++)
    {
        if (arr[i] % 2 == 1)
        {
            printf("[%d°]: %d\n", n + 1, arr[i]);
            n++;
        }
    }
}

int ricerca(int arr[], int n, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        if (arr[i] == n)
        {
            return i;
        }
    }
    return -1;
}

int elimina(int arr[], int *dim, int pos)
{
    for (int i = pos; i < *dim - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    (*dim)--; 
    return pos;
}

void alterna(int arr[], int dim)
{
    int n;

    for (int i = 0; i < dim - 1; i += 2)
    {
        n = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = n;
    }
    stampa(arr, dim);
}

void ordina(int arr[], int dim)
{
    int n;

    for (int i = 0; i < dim - 1; i++)
    {
        for (int y = 0; y < dim - 1 - i; y++)
        {
            if (arr[y] > arr[y + 1])
            {
                n = arr[y];
                arr[y] = arr[y + 1];
                arr[y + 1] = n;
            }
        }
    }
    stampa(arr, dim);
}

void menuEsecuzione(int arr[], int scelta, int *dim)
{
    switch (scelta)
    {
    case 1:
        stampa(arr, *dim);
        break;

    case 2:
        inverso(arr, *dim);
        break;

    case 3:
        printf("Somma dei numeri: %d\nMedia dei numeri: %.2f\n", somma(arr, *dim), media(arr, *dim));
        break;

    case 4:
        pari(arr, *dim);
        break;

    case 5:
        dispari(arr, *dim);
        break;

    case 6:
    {
        int n, pos;
        printf("Inserisci il numero da ricercare: ");
        scanf("%d", &n);
        pos = ricerca(arr, n, *dim);

        if (pos > -1)
        {
            printf("Numero trovato in posizione %d\n", pos + 1);
        }
        else
        {
            printf("Numero non presente nell'array\n");
        }
        break;
    }

    case 7:
    {
        int num, pos;
        printf("Inserisci il numero da eliminare: ");
        scanf("%d", &num);
        pos = ricerca(arr, num, *dim);

        if (pos > -1)
        {
            elimina(arr, dim, pos);
            printf("Numero eliminato\n");
        }
        else
        {
            printf("Numero non presente nell'array\n");
        }
        break;
    }

    case 8:
        alterna(arr, *dim);
        break;

    case 9:
        ordina(arr, *dim);
        break;
    }
}

int main(int argc, char *argv[])
{
    char *funz[FUNCTIONS] = {"Stampa", "Inverso", "Somma e Media", "Num Pari", "Num Dispari", "Ricerca", "Elimina", "Alterni", "Ordina", "Esci"};
    int scelta, dim = ARRAY_DIM;

    generazione(arr, dim);

    while (1)
    {
        scelta = menu(funz);

        if (scelta == FUNCTIONS)
        {
            printf("\nProgramma terminato\n");
            break;
        }
        else
        {
            menuEsecuzione(arr, scelta, &dim);
        }
    }
    return 0;
}