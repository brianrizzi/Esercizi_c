#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// creo la struct di tipo studente inserendo il nome, il cognome e l'età
typedef struct
{
    char nome[20], cognome[20];
    int anni;
} Studente;

int main(int argc, char *argv[])
{
    // dichiaro la variabile di tipo studente, la p per la fork e status per la wait
    Studente s;
    int p, status;

    // inserisco nome, cognome e l'età direttamente dal programma
    strcpy(s.nome, "Brian");
    strcpy(s.cognome, "Rizzi");
    s.anni = 17;

    // creo la fork
    p = fork();

    if (p < 0) // messaggio di errore se riscontro problemi nella creazione della fork
    {
        printf("Errore nella creazione della fork\n");
        exit(-1);
    }
    else if (p > 0) // processo padre che aspetta il processo figlio
    {
        wait(&status);
        exit(-1);
    }
    else // processo figlio che passa i dati con execl
    {
        // creo un array di caratteri dove, utilizzando sprintf, che mi permette di scrivere dati formattati in stringhe, passo gli anni
        char str_anni[20];
        sprintf(str_anni, "%d", s.anni);

        execl("./P2", "P2", s.nome, s.cognome, str_anni, NULL);

        // printf che mi segnala un'errore nella chiamata dell'execl
        printf("Errore nella nella chiamata dell'execl\n");
        exit(-1);
    }
    return 0;
}