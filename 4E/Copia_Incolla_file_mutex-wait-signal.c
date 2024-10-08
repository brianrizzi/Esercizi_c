#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_DIM 64
#define BUFFER_SIZE 16

typedef struct
{
    unsigned char buffer[BUFFER_DIM];
    int n;
} Buffer;

int iRead = 0, iWrite = 0, nBlock = 0, end = 0;
Buffer ring_buffer[BUFFER_SIZE];
pthread_mutex_t mutex, critical;
pthread_cond_t nFull, nEmpty;
FILE *org, *dest;

void *Lettura(void *f)
{
    int n;

    while (!feof(org))
    {
        pthread_mutex_lock(&critical);

        if (nBlock >= BUFFER_SIZE)
        {
            pthread_cond_wait(&nFull, &critical);
        }
        n = fread(ring_buffer[iWrite].buffer, 1, BUFFER_DIM, org);

        if (n > 0)
        {
            ring_buffer[iWrite].n = n;
            iWrite = (iWrite + 1) % BUFFER_SIZE;
            pthread_mutex_lock(&mutex);
            nBlock++;
            pthread_mutex_unlock(&mutex);
            pthread_cond_signal(&nEmpty);
        }
        pthread_mutex_unlock(&critical);
    }
    end = 1;
    pthread_cond_signal(&nEmpty);
    pthread_exit(NULL);
}

void *Scrittura(void *par)
{
    while (1)
    {
        if (end && nBlock == 0)
        {
            fwrite(ring_buffer[iRead].buffer, 1, ring_buffer[iRead].n, dest);
            iRead = (iRead + 1) % BUFFER_SIZE;
            pthread_mutex_lock(&mutex);
            nBlock--;
            pthread_mutex_unlock(&mutex);
            pthread_cond_signal(&nFull);
        }
        else
        {
            pthread_cond_wait(&nEmpty, &critical);
        }
        pthread_mutex_unlock(&critical);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t write, read;

    if (argc != 3)
    {
        printf("Errore negli argomenti\n");
        exit(-1);
    }

    org = fopen(argv[1], "rb");

    if (org == NULL)
    {
        printf("Errore nell'apertura del file\n");
        exit(-1);
    }

    dest = fopen(argv[2], "wb");

    if (dest == NULL)
    {
        printf("Errore nell'apertura del file\n");
        fclose(org);
        exit(-1);
    }

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&critical, NULL);
    pthread_cond_init(&nFull, NULL);
    pthread_cond_init(&nEmpty, NULL);

    pthread_create(&read, NULL, &Lettura, NULL);
    pthread_create(&write, NULL, &Scrittura, NULL);

    pthread_join(read, NULL);
    pthread_join(write, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&critical);
    pthread_cond_destroy(&nFull);
    pthread_cond_destroy(&nEmpty);

    fclose(org);
    fclose(dest);

    return 0;
}
