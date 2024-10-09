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
    Libro *libri;
    char nome[SIZE];
    int nLibri, nMaxLibri;

} Categoria;

typedef struct
{
    Categoria *categorie;
    int nCategorie, nMaxCategorie;
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

void initCategoria(Categoria *categoria)
{
    categoria->libri = malloc(DIM_LIBRERIA * sizeof(Libro));
    categoria->nLibri = 0;
    categoria->nMaxLibri = DIM_LIBRERIA;
}

void initLibreria(Libreria *libreria)
{
    libreria->categorie = malloc(DIM_LIBRERIA * sizeof(Categoria));
    libreria->nCategorie = 0;
    libreria->nMaxCategorie = DIM_LIBRERIA;
}

void freeLibreria(Libreria *libreria)
{
    for (int i = 0; i < libreria->nCategorie; i++)
    {
        free(libreria->categorie[i].libri);
    }
    free(libreria->categorie);
}

void importaLibro(Categoria *categoria, Libro libro)
{
    if (categoria->nLibri >= categoria->nMaxLibri)
    {
        categoria->nMaxLibri *= 2;
        categoria->libri = realloc(categoria->libri, categoria->nMaxLibri * sizeof(Libro));
    }
    categoria->libri[categoria->nLibri] = libro;
    categoria->nLibri++;
}

void importaCategoria(Libreria *libreria, char *categoria)
{
    Categoria *ctg;

    if (libreria->nCategorie >= libreria->nMaxCategorie)
    {
        libreria->nMaxCategorie *= 2;
        libreria->categorie = realloc(libreria->categorie, libreria->nMaxCategorie * sizeof(Categoria));
    }

    ctg = &libreria->categorie[libreria->nCategorie];
    strcpy(ctg->nome, categoria);

    initCategoria(ctg);
    libreria->nCategorie++;
}

int trovaCategoria(Libreria *libreria, char *nomeCategoria)
{
    for (int i = 0; i < libreria->nCategorie; i++)
    {
        if (strcasecmp(libreria->categorie[i].nome, nomeCategoria) == 0)
        {
            return i;
        }
    }
    return -1;
}

void importaCSV(Libreria *libreria)
{
    FILE *f;
    Libro libro;
    char riga[BUFFER_SIZE], categoriaNome[SIZE];
    int categoriaIndice;

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

        sscanf(riga, "%[^,],%[^,],%d,%f,%[^\r\n]", libro.titolo, libro.autore, &libro.anno, &libro.prezzo, categoriaNome);

        categoriaIndice = trovaCategoria(libreria, categoriaNome);

        if (categoriaIndice == -1)
        {
            importaCategoria(libreria, categoriaNome);
            categoriaIndice = libreria->nCategorie - 1;
        }
        ctg = &libreria->categorie[categoriaIndice];
        importaLibro(ctg, libro);
    }
    fclose(f);
}

void stampaLibreria(Libreria *libreria, char *categoria)
{
    for (int i = 0; i < libreria->nCategorie; i++)
    {
        if (categoria == NULL || strcasecmp(libreria->categorie[i].nome, categoria) == 0)
        {
            for (int j = 0; j < libreria->categorie[i].nLibri; j++)
            {
                Libro libro = libreria->categorie[i].libri[j];
                printf("TITOLO: %s << AUTORE: %s << ANNO: %d << PREZZO: %.2f << CATEGORIA: %s\n",
                       libro.titolo, libro.autore, libro.anno, libro.prezzo, libreria->categorie[i].nome);
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
        stampaLibreria(libreria, NULL);
        break;

    case 3:
    {
        char titolo[SIZE];
        int categoriaIndice = -1;
        Libro *libro;

        printf("Inserisci il titolo del libro da cercare: ");
        getchar();
        fgets(titolo, SIZE, stdin);
        titolo[strcspn(titolo, "\n")] = '\0';

        libro = cercaPerNome(libreria, titolo, &categoriaIndice);

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
        int categoriaIndice;

        printf("Inserisci il nome della categoria di libri da cercare: ");
        getchar();
        fgets(categoria, SIZE, stdin);
        categoria[strcspn(categoria, "\n")] = '\0';

        categoriaIndice = trovaCategoria(libreria, categoria);

        if (categoriaIndice == -1)
        {
            printf("La categoria <%s> non è presente nella libreria.\n", categoria);
        }
        else
        {
            stampaLibreria(libreria, categoria);
        }
    }
    break;
    }
}

int main(int argc, char *argv[])
{
    Libreria libreria;

    char *funz[FUNCTIONS] = {"Importa CSV", "Stampa libri", "Cerca libro dato nome", "Cerca libri data categoria", "Esci"};
    int scelta;

    initLibreria(&libreria);

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
    freeLibreria(&libreria);

    return 0;
}
