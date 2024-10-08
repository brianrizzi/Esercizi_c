#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_DIM 1000

int n;

void *RicercaTd1(void *s)
{
    int *arr = (int *)s;

    for (int i = 0; i < ARRAY_DIM - 750; i++)
    {
        if (arr[i] == n)
        {
            printf("Sono il thread 1. Ho trovato il numero in posizione %d", i);
        }
    }
}
void *RicercaTd2(void *s)
{
    int *arr = (int *)s;

    for (int i = 250; i < ARRAY_DIM - 500; i++)
    {
        if (arr[i] == n)
        {
            printf("Sono il thread 2. Ho trovato il numero in posizione %d", i);
        }
    }
}
void *RicercaTd3(void *s)
{
    int *arr = (int *)s;

    for (int i = 500; i < ARRAY_DIM - 250; i++)
    {
        if (arr[i] == n)
        {
            printf("Sono il thread 3. Ho trovato il numero in posizione %d", i);
        }
    }
}
void *RicercaTd4(void *s)
{
    int *arr = (int *)s;

    for (int i = 750; i < ARRAY_DIM; i++)
    {
        if (arr[i] == n)
        {
            printf("Sono il thread 4. Ho trovato il numero in posizione %d", i);
        }
    }
}
void ArrayNum(int arr[])
{
    for (int i = 0; i < ARRAY_DIM; i++)
    {
        arr[i] = rand() % 501;
    }
}
int main(int argc, char *argv[])
{
    int arr[ARRAY_DIM];
    pthread_t thread1, thread2, thread3, thread4;

    ArrayNum(arr);

    printf("Inserisci il numero da ricercare: \n");
    scanf("%d", &n);

    pthread_create(&thread1, NULL, &RicercaTd1, (void *)arr);
    pthread_create(&thread2, NULL, &RicercaTd2, (void *)arr);
    pthread_create(&thread3, NULL, &RicercaTd3, (void *)arr);
    pthread_create(&thread4, NULL, &RicercaTd4, (void *)arr);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    return 0;
}