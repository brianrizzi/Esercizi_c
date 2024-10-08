#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_DIM 10

void *RicercaTd1(void *s)
{
    int *arr = (int *)s;

    for (int i = 0; i < ARRAY_DIM / 2; i++)
    {
        if (arr[i] == 8)
        {
            printf("Sono il thread 1. Ho trovato il numero in posizione %d", i);
        }
    }
}
void *RicercaTd2(void *s)
{
    int *arr = (int *)s;

    for (int i = ARRAY_DIM / 2; i < ARRAY_DIM; i++)
    {
        if (arr[i] == 8)
        {
            printf("Sono il thread 2. Ho trovato il numero in posizione %d", i);
        }
    }
}

int main(int agrc, char *argv[])
{
    int arr[ARRAY_DIM] = {1, 4, 2, 8, 3, 5, 6, 9, 7, 0};
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, &RicercaTd1, (void *)arr);
    pthread_create(&thread2, NULL, &RicercaTd2, (void *)arr);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}