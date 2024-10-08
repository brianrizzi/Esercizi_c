#include <stdio.h>
#include <stdlib.h>
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

void stampaLibreria(Libreria libreria, char *categoriaFiltrata)
{
    for (int i = 0; i < libreria.nCategorie; i++)
    {
        if (categoriaFiltrata == NULL || strcasecmp(libreria.categorie[i].nome, categoriaFiltrata) == 0)
        {
            for (int j = 0; j < libreria.categorie[i].nLibri; j++)
            {
                Libro libro = libreria.categorie[i].libri[j];
                printf("TITOLO: %s << AUTORE: %s << ANNO: %d << PREZZO: %.2f << CATEGORIA: %s\n",
                       libro.titolo, libro.autore, libro.anno, libro.prezzo, libreria.categorie[i].nome);
            }
        }
    }
}

Libro *cercaPerNome(Libreria *libreria, char *titolo, int *categoriaIndice)
{
    for (int i = 0; i < libreria->nCategorie; i++)
    {
        for (int j = 0; j < libreria->categorie[i].nLibri; j++)
        {
            if (strcasecmp(libreria->categorie[i].libri[j].titolo, titolo) == 0)
            {
                *categoriaIndice = i;
                return &libreria->categorie[i].libri[j];
            }
        }
    }
    return NULL;
}

void menuEsecuzione(Libreria *libreria, int scelta)
{
    switch (scelta)
    {
    case 1:
        importaCSV(libreria);
        break;

    case 2:
        stampaLibreria(*libreria, NULL);
        break;

    case 3:
    {
        char titolo[SIZE];
        int categoriaIndice = -1;

        printf("Inserisci il titolo del libro da cercare: ");

        getchar();
        fgets(titolo, SIZE, stdin);

        titolo[strcspn(titolo, "\n")] = '\0';

        Libro *libro = cercaPerNome(libreria, titolo, &categoriaIndice);

        if (libro == NULL)
        {
            printf("Nessun libro trovato con questo nome\n");
        }
        else
        {
            printf("TITOLO: %s << AUTORE: %s << ANNO: %d << PREZZO: %.2f << CATEGORIA: %s\n",
                   libro->titolo, libro->autore, libro->anno, libro->prezzo, libreria->categorie[categoriaIndice].nome);
        }
    }
    break;

    case 4:
    {
        char categoria[SIZE];

        printf("Inserisci il nome della categoria di libri da cercare: ");

        getchar();
        fgets(categoria, SIZE, stdin);

        categoria[strcspn(categoria, "\n")] = '\0';

        stampaLibreria(*libreria, categoria);
    }
    break;
    }
}

int main(int argc, char *argv[])
{
    Libreria libreria = {0};
    Categoria categoria = {0};
    char *funz[FUNCTIONS] = {"Importa CSV", "Stampa libri", "Cerca libro dato nome", "Cerca libri data categoria", "Esci"};
    int scelta;

    while (1)
    {
        scelta = menu(funz);

        if (scelta == FUNCTIONS)
        {
            printf("\nProgramma terminato\n");
            break;
        }
        else
        {
            menuEsecuzione(&libreria, scelta);
        }
    }
    return 0;
}
