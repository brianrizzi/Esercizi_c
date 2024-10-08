#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

#define BUFFER_SIZE 1024 // dimensione del buffer
#define NUM_SLICE 16     // numero slice del buffer

typedef struct // struttura per il buffer
{
    unsigned char bufferStruct[BUFFER_SIZE]; // buffer per contenere i dai letti
    int n;                                   // numero di byte letti nel buffer
} BufferStruct;

BufferStruct buffer[NUM_SLICE];                   // dichiarazione array di strutture BufferStruct
int read_index = 0, write_index = 0, nSlices = 0; // indici di lettura, scrittura e numero di slice
bool end = false;                                 // booleano che indica la fine della lettura

pthread_mutex_t mutex;              // dichiarazione mutex
pthread_cond_t not_full, not_empty; // dichiarazione cond

void *Scrittura(void *args) // funzione eseguita dal thread di scrittura
{
    FILE *f = (FILE *)args; // conversione dell'argomento in puntatore a FILE

    while (1)
    {
        if (end && nSlices == 0) // se la lettura è finita e non ci sono più slice da scrivere, termina il ciclo
        {
            break;
        }
        pthread_mutex_lock(&mutex); // acquisisce il mutex

        if (nSlices > 0) // controllo se ci sono slice disponibili
        {
            fwrite(buffer[read_index].bufferStruct, 1, buffer[read_index].n, f); // scrive il contenuto del buffer nel file
            read_index = (read_index + 1) % NUM_SLICE;                           // aggiorna l'indice di lettura
            nSlices--;                                                           // decrementa il numero di slice disponibili
        }
        else
        {
            pthread_cond_signal(&not_full); // segnala che c'è spazio disponibile per scrivere nel buffer
            pthread_mutex_unlock(&mutex);   // rilascia il mutex
        }
        pthread_cond_signal(&not_full); // segnala che c'è spazio disponibile per scrivere nel buffer
        pthread_mutex_unlock(&mutex);   // rilascia il mutex
    }

    pthread_exit(NULL); // termina il thread
}

void *Lettura(void *args) // funzione eseguita dal thread di lettura
{
    FILE *f = (FILE *)args; // conversione dell'argomento in puntatore a FILE
    int n;

    while (!feof(f)) // continua a leggere finché non si raggiunge la fine del file
    {
        pthread_mutex_lock(&mutex); // acquisisce il mutex

        if (nSlices > NUM_SLICE) // se il buffer è pieno
        {
            pthread_cond_wait(&not_empty, &mutex); // attende che ci sia spazio disponibile nel buffer
        }

        n = fread(buffer[write_index].bufferStruct, 1, BUFFER_SIZE, f); // legge dati dal file nel buffer

        if (n > 0) // se ha letto dati
        {
            buffer[write_index].n = n;                   // imposta il numero di byte letti nel buffer
            write_index = (write_index + 1) % NUM_SLICE; // aggiorna l'indice di scrittura
            nSlices++;                                   // incrementa il numero di slice disponibili
            pthread_cond_signal(&not_empty);             // segnala che ci sono dati disponibili nel buffer
        }
        pthread_mutex_unlock(&mutex); // rilascia il mutex
    }
    end = true;                      // indica che la lettura è finita
    pthread_cond_signal(&not_empty); // segnala che ci sono dati disponibili nel buffer
    pthread_exit(NULL);              // termina il thread
}

int main(int argc, char *argv[])
{
    FILE *org, *dest;          // dichiarazione dei puntatori a FILE per i file di origine e destinazione
    pthread_t t_write, t_read; // dichiarazione dei thread

    if (argc != 3) // controllo degli argomenti
    {
        printf("Errore negli argomenti\n");
        exit(-1);
    }

    org = fopen(argv[1], "rb"); // apertura file origine in lettura binaria

    if (org == NULL) // controllo apertura file origine
    {
        printf("Errore nell'apertura del file\n");
        exit(-1);
    }

    dest = fopen(argv[2], "wb"); // apertura file destinazione in scrittura binaria

    if (dest == NULL) // controllo apertura file destinazione
    {
        printf("Errore nell'apertura del file\n");
        exit(-1);
    }

    // inizializzazione dei mutex e dei cond
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    // creazione dei thread di lettura e scrittura
    pthread_create(&t_read, NULL, &Lettura, org);
    pthread_create(&t_write, NULL, &Scrittura, dest);

    // attesa della terminazione dei thread
    pthread_join(t_read, NULL);
    pthread_join(t_write, NULL);

    // Distruzione dei mutex e dei cond
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return 0;
}
