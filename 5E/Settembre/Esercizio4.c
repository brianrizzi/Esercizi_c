#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define DIM_LIBRERIA 40
#define SIZE 50
#define FUNCTIONS 5
#define BUFFER_SIZE 256
#define FILECSV "libreria_libri.csv"

typedef struct
{
    char titolo[SIZE], autore[SIZE];
    int anno;
    float prezzo;
} Libro;

typedef struct
{
    Libro libri[DIM_LIBRERIA];
    int nLibri;
    char nome[SIZE];
} Categoria;

typedef struct
{
    Categoria categorie[DIM_LIBRERIA];
    int nCategorie;
} Libreria;

int menu(char *arr[])
{
    int scelta;

    do
    {
        for (int i = 0; i < FUNCTIONS; i++)
        {
            printf("[%d] <<  %s\n", i + 1, arr[i]);
        }
        scanf("%d", &scelta);

        if (scelta < 1 || scelta > FUNCTIONS)
        {
            printf("\nErrore! Inserisci un numero compreso tra 1 e %d\n\n", FUNCTIONS);
        }
    } while (scelta < 1 || scelta > FUNCTIONS);

    return scelta;
}

void importaCSV(Libreria *libreria)
{
    FILE *f;
    Libro libro;
    char riga[BUFFER_SIZE], categoria[SIZE];

    f = fopen(FILECSV, "r");

    if (f == NULL)
    {
        printf("Errore nell'apertura del file");
        exit(-1);
    }
    fgets(riga, BUFFER_SIZE, f);

    while (fgets(riga, BUFFER_SIZE, f) != NULL)
    {
        Categoria *ctg;
        int esistente = -1;

        sscanf(riga, "%[^,],%[^,],%d,%f,%[^\r\n]", libro.titolo, libro.autore, &libro.anno, &libro.prezzo, categoria);

        for (int i = 0; i < libreria->nCategorie; i++)
        {
            if (strcasecmp(libreria->categorie[i].nome, categoria) == 0)
            {
                esistente = i;
                break;
            }
        }

        if (esistente == -1)
        {
            esistente = libreria->nCategorie;
            strcpy(libreria->categorie[libreria->nCategorie].nome, categoria);
            libreria->categorie[libreria->nCategorie].nLibri = 0;
            libreria->nCategorie++;
        }
        ctg = &libreria->categorie[esistente];
        ctg->libri[ctg->nLibri] = libro;
        ctg->nLibri++;
    }
    fclose(f);
}

void stampaPerCategoria(Libreria libreria, char *categoria)
{
    for (int i = 0; i < libreria.nCategorie; i++)
    {
        if (strcasecmp(libreria.categorie[i].nome, categoria) == 0)
        {
            for (int j = 0; j < libreria.categorie[i].nLibri; j++)
            {
                Libro libro = libreria.categorie[i].libri[j];
                printf("TITOLO: %s << AUTORE: %s << ANNO: %d << PREZZO: %.2f << CATEGORIA: %s\n", libro.titolo, libro.autore, libro.anno, libro.prezzo, libreria.categorie[i].nome);
            }
        }
    }
}

void cercaPerNome(Libreria libreria, char *titolo)
{
    for (int i = 0; i < libreria.nCategorie; i++)
    {
        for (int j = 0; j < libreria.categorie[i].nLibri; j++)
        {
            if (strcasecmp(libreria.categorie[i].libri[j].titolo, titolo) == 0)
            {
                Libro libro = libreria.categorie[i].libri[j];
                printf("TITOLO: %s << AUTORE: %s << ANNO: %d << PREZZO: %.2f << CATEGORIA: %s\n", libro.titolo, libro.autore, libro.anno, libro.prezzo, libreria.categorie[i].nome);
            }
        }
    }
}

int main()
{
    Libreria libreria = {0};
    Categoria categoria = {0};
    char *funz[FUNCTIONS] = {"Importa CSV", "Stampa libri", "Cerca libro dato nome", "Cerca libri data categoria", "Esci"};

    importaCSV(&libreria);
    stampaPerCategoria(libreria, "Narrativa storica");
    cercaPerNome(libreria, "La metamorfosi");
    return 0;
}
