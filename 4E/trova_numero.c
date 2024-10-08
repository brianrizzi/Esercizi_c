#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 1000

int array[SIZE];

typedef struct 
{
    int target;
    int inizio;
    int fine;
} Parametri;

void*ScriviNumeriFile(void*arg)
{
    FILE*fileNumeri=(FILE*)arg;

    for(int i=0;i<SIZE;i++)
    {
        fprintf(fileNumeri,"Numeri stampati:%d\n",array[i]);
    }
    pthread_exit(NULL);
}

void*RicercaNumero(void*arg)
{
   Parametri*params=(Parametri*)arg;
    for(int i=params->inizio;i<params->fine;i++)
    {
        if(array[i]==params->target)
        {
            printf("La posizione del numero è %d\n",i);
            pthread_exit(NULL);
        }
        

    }
    printf("Numero non trovato\n");
}
int main(int argc,char *argv[])
{   
    FILE*fileNumeri;
    fileNumeri=fopen(argv[1],"w");
    if(fileNumeri==NULL)
    {
        printf("Errore apertura\n");
        exit(1);
    }

    Parametri p1={87,0,SIZE/4};
    Parametri p2={87,SIZE/4,SIZE/2};
    Parametri p3={87,SIZE/2,(SIZE-SIZE/4)};
    Parametri p4={(87,SIZE-SIZE/4),SIZE};

    pthread_t t1,t2,t3,t4,threadFile;


    for(int i=0;i<SIZE;i++)
    {
        array[i]=(rand()%500);
        printf("%d\n",array[i]);
    }
    pthread_create(&t1,NULL,RicercaNumero,(void*)&p1);
    pthread_create(&t2,NULL,RicercaNumero,(void*)&p2);
    pthread_create(&t3,NULL,RicercaNumero,(void*)&p3);
    pthread_create(&t4,NULL,RicercaNumero,(void*)&p4);
    pthread_create(&threadFile,NULL,ScriviNumeriFile,(void*)fileNumeri);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(threadFile,NULL);
    return 0;
}