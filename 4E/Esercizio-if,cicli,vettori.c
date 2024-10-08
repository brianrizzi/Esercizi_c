#include <stdio.h>

int main(int argc, char *argv)
{
    // dichiaro le variabili da utilizzare per sviluppare il codice
    int limite1, limite2, limiteInferiore, limiteSuperiore, somma = 0, cont = 1;
    int n[5];

    // faccio un ciclo while che itera finchè non vengono inseriti due numeri compres tra 30 e 50
    while (1)
    {

        // chiedo all'utente di inserire due numeri
        printf("Inserisci 2 numeri interi compresi tra limite1 = 30 e limite2 = 50");

        printf("\nInserisci il primo limite: limite1 >>  ");
        scanf("%d", &limite1);

        printf("Inserisci il secondo limite: limite2 >>  ");
        scanf("%d", &limite2);

        printf("\n");

        // controllo se i numeri inseriti dall'utente sono compreso tra 30 e 50
        if (limite1 >= 30 && limite1 <= 50 && limite2 >= 30 && limite2 <= 50)
        {
            break;
        }
    }

    // controllo quale dei due numeri inseriti è il limite inferiore e quale quello superiore. Successivamente li assegno alle rispettive variabili
    if (limite1 < limite2)
    {
        limiteInferiore = limite1;
        limiteSuperiore = limite2;
        printf("\nLimite inferiore: %d \n", limiteInferiore);
        printf("Limite superiore: %d \n", limiteSuperiore);
    }
    else
    {
        limiteInferiore = limite2;
        limiteSuperiore = limite1;
        printf("\nLimite inferiore: %d \n", limiteInferiore);
        printf("Limite superiore: %d \n", limiteSuperiore);
    }

    // chiedo all'utente di inserire 5 numeri. Di questi numeri verranno sommati solo quelli compresi fra i limiti inseriti precedentemente
    printf("\nInserisci 5 numeri \n");
    printf("Se saranno compresi tra il limite inferiore = %d e il limite superiore = %d, allora verranno sommati tra loro\n", limiteInferiore, limiteSuperiore);

    // faccio un ciclo for per inserire i 5 numeri
    for (int i = 0; i < 5; i++)
    {
        printf("\nInserisci il %d^ numero intero <<  ", cont);
        scanf("%d", &n[i]);

        // controllo se il numero inserito è compreso nei limiti
        if (n[i] >= limiteInferiore && n[i] <= limiteSuperiore)
        {
            somma = somma + n[i];
        }
        cont++;
    }

    // riassegno alla variabile cont il valore 1, per utilizzare ne momento in cui dobbiamo fornire la posizione di un numero all'interno dell'array
    cont = 1;

    printf("\n\nContenuto dell'array: \n");

    //faccio un ciclo for per stampare il contenuto dell'array
    for (int i = 0; i < 5; i++)
    {

        //se il numero è compreso tra i limiti, verranno stampati anche indice e posizione. In caso contrario verrà stampato solamente il numero
        if (n[i] >= limiteInferiore && n[i] <= limiteSuperiore)
        {
            printf("\nnumero <<  [%d] indice <<  [%d] posizione <<  [%d]\n", n[i], i, cont);
        } else 
        {
            printf("\nnumero <<  %d\n", n[i]);
        }
        cont++;
    }

    // stampo a video la somma
    printf("\n\nSomma dei numeri compresi tra %d e %d = %d \n", limiteInferiore, limiteSuperiore, somma);

    return 0;
}
