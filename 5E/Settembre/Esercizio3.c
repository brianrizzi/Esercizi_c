#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 30
#define NAUTO 3

typedef struct
{
    char modelloAuto[SIZE], marca[SIZE];
    int cilindrata, annoImmatricolazione, prezzo;
} Auto;

void inserisci(Auto a[])
{
    for (int i = 0; i < NAUTO; i++)
    {
        printf("Inserisci il modello della %d° auto: ", i + 1);
        scanf("%s", a[i].modelloAuto);
        printf("Inserisci la marca della %d° auto: ", i + 1);
        scanf("%s", a[i].marca);
        printf("Inserisci la cilindrata della %d° auto: ", i + 1);
        scanf("%d", &a[i].cilindrata); 
        printf("Inserisci l'anno di immatricolazione della %d° auto: ", i + 1);
        scanf("%d", &a[i].annoImmatricolazione); 
        printf("Inserisci il prezzo della %d° auto: ", i + 1);
        scanf("%d", &a[i].prezzo); 
    }
}

void trovaPrezzo(Auto a[])
{
    int pBasso = INT_MAX, pAlto = 0, n = 0, m = 0;

    for (int i = 0; i < NAUTO; i++)
    {
        if (a[i].prezzo > pAlto)
        {
            pAlto = a[i].prezzo;
            n = i;
        }
        if (a[i].prezzo < pBasso)
        {
            pBasso = a[i].prezzo;
            m = i;
        }
    }
    printf("\nAuto più costosa:\nModello: %s << Prezzo: %d\n", a[n].modelloAuto, a[n].prezzo);
    printf("\nAuto meno costosa:\nModello: %s << Prezzo: %d\n\n", a[m].modelloAuto, a[m].prezzo);
}

void ordina(Auto a[])
{
    Auto n;

    for (int i = 0; i < NAUTO - 1; i++)
    {
        for (int j = 0; j < NAUTO - i - 1; j++)
        {
            if (a[j].annoImmatricolazione > a[j + 1].annoImmatricolazione)
            {
                // Scambia gli oggetti Auto
                n = a[j];
                a[j] = a[j + 1];
                a[j + 1] = n;
            }
        }
    }
}

void visualizza(Auto a[])
{
    int p;

    printf("Inserisci il prezzo di partenza: ");
    scanf("%d", &p);

    for (int i = 0; i < NAUTO; i++)
    {
        if (a[i].prezzo >= p)
        {
            printf("Modello: %s << Marca: %s << Cilindrata: %d << Immatricolazione: %d << Prezzo: %d\n", a[i].modelloAuto, a[i].marca, a[i].cilindrata, a[i].annoImmatricolazione, a[i].prezzo);
        }
    }
}

int main()
{
    Auto a[NAUTO];

    inserisci(a);
    trovaPrezzo(a);
    visualizza(a);
    
    ordina(a);

    printf("\nAuto ordinate per anno di immatricolazione:\n");
    for (int i = 0; i < NAUTO; i++)
    {
        printf("Modello: %s << Marca: %s << Cilindrata: %d << Immatricolazione: %d << Prezzo: %d\n", a[i].modelloAuto, a[i].marca, a[i].cilindrata, a[i].annoImmatricolazione, a[i].prezzo);
    }
    return 0;
}