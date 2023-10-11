#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//dichiaro la struct student_t
typedef struct
{
    char nome[20];
    char cognome[20];
    int media;

} student_t;

int main(int argc, char *argv[])
{
    //faccio un array di 3 studenti di tipo student_t
    student_t *studenti[3];

    for (int i = 0; i < 3; i++)
    {
        //allocazione di memoria per ogni studente dell'array
        studenti[i] = (student_t *)malloc(sizeof(student_t));

        //chiedo all'utente di inserire nome, cognome e media per ogni studente
        printf("Inserisci il nome del %d° studente: ", i + 1);
        scanf("%s", studenti[i]->nome);
        printf("\nInserisci il cognome del %d° studente: ", i + 1);
        scanf("%s", studenti[i]->cognome);
        printf("\nInserisci la media del %d° studente: ", i + 1);
        scanf("%d", &studenti[i]->media);
        printf("\n\n");
    }

    //stampo nome, cognome, media e indirizzo di memoria per ogni studente
    for (int j = 0; j < 3; j++) 
    {
        printf("%d° Studente:\n", j + 1);
        printf("Nome <<  %s\n", studenti[j]->nome);
        printf("Cogome <<  %s\n", studenti[j]->cognome);
        printf("Media <<  %d\n", studenti[j]->media);
        printf("Indirizzo di memoria <<  %p\n\n", &studenti[j]);
    }

    //utilizzando un ciclo for libero l'area di memoria di ogni studente
    for (int y = 0; y < 3; y++)
    {
        free(studenti[y]);
    }

    return 0;
}
