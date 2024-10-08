#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    char nome[100];
    char cognome[100];
    char classe[100];
    float media;
} Studente;

void *StampaStudente(void *par)
{
    Studente *s = (Studente *)par;

    printf("NOME: %s, COGNOME: %s, CLASSE: %s, MEDIA: %f", s->nome, s->cognome, s->classe, s->media);
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    Studente s;

    strcpy(s.nome, "Brian");
    strcpy(s.cognome, "Rizzi");
    strcpy(s.classe, "4E");
    s.media = 7.3;

    pthread_create(&thread, NULL, &StampaStudente, (void *)&s);
    pthread_join(thread, NULL);

    return 0;
}