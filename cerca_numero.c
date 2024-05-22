#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define ARRAY_DIM 1000 // dimensione dell'array di numeri

typedef struct
{
    int numScelto; // il numero scelto da ricercare
    int inizio;    // inizio della ricerca
    int fine;      // fine della ricerca
} Struct;

int array[ARRAY_DIM]; // array di numeri

void *ScriviNelFile(void *args) // funzione che mi scrive l'array nel file
{
    FILE *f = (FILE *)args; // conversione dell'argomento in puntatore a FILE

    for (int i = 0; i < ARRAY_DIM; i++) // ciclo che stampa l'array
    {
        fprintf(f, "[%d]: %d\n", i + 1, array[i]);
    }
    pthread_exit(NULL); // termina il thread
}

void *Ricerca(void *args) // funzione che ricerca il numero nell'array
{
    Struct *s = (Struct *)args; // conversione dell'argomento in puntatore a Struct

    for (int i = s->inizio; i < s->fine; i++) // ciclo sugli elementi della porzione di array
    {
        if (array[i] == s->numScelto) // se l'elemento corrente è uguale al numero cercato lo stampo
        {
            printf("Numero trovato in posizione %d\n", i + 1);
            pthread_exit(NULL); // termina il thread
        }
    }
    pthread_exit(NULL); // termina il thread
}

int main(int argc, char *argv[])
{
    FILE *f;
    pthread_t t1, t2, t3, t4, tFile;

    f = fopen(argv[1], "w"); // apertura file in scrittura

    if (f == NULL) // controllo apertura file
    {
        printf("Errore nell'apertura del file\n");
        exit(-1);
    }

    for (int i = 0; i < ARRAY_DIM; i++)
    {
        array[i] = (rand() % 500); // assegno un numero casuale da 0 a 499 ad ogni elemento dell'array
    }

    int nScelto = atoi(argv[2]); // passo il numero scelto con argv

    // inizializzo le struct per ogni thread
    Struct pt1 = {nScelto, 0, ARRAY_DIM / 4};
    Struct pt2 = {nScelto, ARRAY_DIM / 4, ARRAY_DIM / 2};
    Struct pt3 = {nScelto, ARRAY_DIM / 2, ARRAY_DIM - (ARRAY_DIM / 4)};
    Struct pt4 = {nScelto, ARRAY_DIM - (ARRAY_DIM / 4), ARRAY_DIM};

    // creazione dei thread
    pthread_create(&t1, NULL, Ricerca, (void *)&pt1);
    pthread_create(&t2, NULL, Ricerca, (void *)&pt2);
    pthread_create(&t3, NULL, Ricerca, (void *)&pt3);
    pthread_create(&t4, NULL, Ricerca, (void *)&pt4);
    pthread_create(&tFile, NULL, ScriviNelFile, (FILE *)f);

    // attendo la terminazione dei thread
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(tFile, NULL);

    return 0;
}
