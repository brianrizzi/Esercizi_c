#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define STR_DIM 50
char str[STR_DIM], str1[STR_DIM];

int lettereCheck(char *str)
{
    int n = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z') || str[i] == ' ')
        {
            n++;
        }
        else
        {
            return -1;
        }
    }
    return n;
}

void inserimento(char *str)
{
    do
    {
        printf("Inserisci una stringa: ");
        fgets(str, STR_DIM, stdin);
        str[strcspn(str, "\n")] = '\0';

    } while (lettereCheck(str) == -1);
}

int conteggio(char *str, char c)
{
    int n = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == c)
        {
            n++;
        }
    }
    return n;
}

void pariDispari(char *str)
{
    char str1[STR_DIM], str2[STR_DIM];
    int j = 0, y = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (i % 2 == 0)
        {
            str1[y] = str[i];
            y++;
        }
        else
        {
            str2[j] = str[i];
            j++;
        }
    }
    str1[y] = '\0';
    str2[j] = '\0';

    printf("Pari: %s\nDispari: %s\n", str1, str2);
}

int doppie(char *str)
{
    int n = 0;

    for (int i = 0; i < strlen(str) - 1; i++)
    {
        if (str[i] == str[i + 1])
        {
            n++;
            i++;
        }
    }
    return n;
}

void comuni(char *str, char *str1)
{
    int arr[26] = {0};

    for (int i = 0; i < strlen(str); i++)
    {
        for (int j = 0; j < strlen(str1); j++)
        {
            if (str[i] == str1[j] && arr[str1[j] - 'a'] == 0)
            {
                printf("%c", str[i]);
                arr[str[i] - 'a'] = 1;
                break;
            }
        }
    }
}

int contavocali(char *str)
{
    int n = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
        {
            n++;
        }
    }
    return n;
}

int contaCons(char *str)
{
    int n = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        if (!(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u'))
        {
            n++;
        }
    }
    return n;
}

void confStringhe(char *str, char *str1)
{
    int l1 = strlen(str), l2 = strlen(str1);

    if (l1 > l2)
    {
        printf("La prima stringa è più lunga della seconda");
    }
    else if (l1 < l2)
    {
        printf("La seconda stringa è più lunga della prima");
    }
    else
    {
        printf("Le due stringhe hanno la stessa lunghezza");
    }
}

int main(int argc, char *argv[])
{
    char c;

    inserimento(str);

    printf("\nInserisci la lettera che vuoi cercare: ");
    scanf(" %c", &c);

    printf("\nil carattere %c appare %d volte\n", c, conteggio(str, c));
    pariDispari(str);

    if (doppie(str) == 0)
    {
        printf("Non sono presenti doppie\n");
    }
    else
    {
        printf("Sono presenti %d doppie\n", doppie(str));
    }

    while (getchar() != '\n');
    
    inserimento(str1);

    confStringhe(str, str1);

    printf("\nLe lettere comuni sono:");
    comuni(str, str1);

    if (contavocali(str) > contavocali(str1))
    {
        printf("\nLa prima stringa contiene più vocali\n");
    }
    else if (contavocali(str) < contavocali(str1))
    {
        printf("\nLa seconda stringa contiene più vocali\n");
    }
    else
    {
        printf("\nContengono lo stesso numero di vocali\n");
    }

    if (contaCons(str) > contaCons(str1))
    {
        printf("La prima stringa contiene più consonanti\n");
    }
    else if (contaCons(str) < contaCons(str1))
    {
        printf("La seconda stringa contiene più consonanti\n");
    }
    else
    {
        printf("Contengono lo stesso numero di consonanti\n");
    }
    return 0;
}
