#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definisco le costanti per gestire la libreria
#define DIM_LIBRERIA 40              // Numero max iniziale di libri
#define SIZE 50                      // Dimensione massima per le stringhe
#define FUNCTIONS 5                  // Numero di funzioni del menù
#define BUFFER_SIZE 256              // Dimensione del buffer per leggere dal file
#define FILECSV "libreria_libri.csv" // Nome del file CSV

// Struct che rappresenta un libro
typedef struct
{
    char titolo[SIZE], autore[SIZE]; // Titolo e autore del libro
    int anno;                        // Anno di pubblicazione del libro
    float prezzo;                    // Prezzo del libro
} Libro;

// Struct che rappresenta una categoria di libri
typedef struct
{
    Libro *libri;          // Puntatore ad un array di libri
    char nome[SIZE];       // Nome della categoria
    int nLibri, nMaxLibri; // Numero attuale e massimo di libri
} Categoria;

// Struct che rappresenta la libreria
typedef struct
{
    Categoria *categorie;                     // Puntatore ad un array di categorie
    int nCategorie, nMaxCategorie, importato; // Numero attuale e massimo di categorie, varabile che verifica se il CSV è stato importato o meno
} Libreria;

// Funzione che permette di visualizzare il menu e restituisce la scelta dell'utente
int menu(char *arr[])
{
    int scelta;

    do
    {
        for (int i = 0; i < FUNCTIONS; i++)
        {
            printf("[%d] <<  %s\n", i + 1, arr[i]);
        }
        printf("\nInserisci la scelta: ");
        scanf("%d", &scelta);

        if (scelta < 1 || scelta > FUNCTIONS)
        {
            printf("\nErrore! Inserisci un numero compreso tra 1 e %d\n\n", FUNCTIONS);
        }
    } while (scelta < 1 || scelta > FUNCTIONS);

    return scelta;
}

// Funzione che inizializza una categoria di libri e alloca uno spazio di memoria per il suo array di libri
void initCategoria(Categoria *categoria)
{
    categoria->libri = malloc(DIM_LIBRERIA * sizeof(Libro));
    categoria->nLibri = 0;
    categoria->nMaxLibri = DIM_LIBRERIA;
}

// Funzione che inizializza la libreria e alloca uno spazio di memoria per il suo array di categorie
void initLibreria(Libreria *libreria)
{
    libreria->categorie = malloc(DIM_LIBRERIA * sizeof(Categoria));
    libreria->nCategorie = 0;
    libreria->nMaxCategorie = DIM_LIBRERIA;
    libreria->importato = 0;
}

// Funzione che libera la memoria precedentemente occupata dalla libreria
void freeLibreria(Libreria *libreria)
{
    for (int i = 0; i < libreria->nCategorie; i++)
    {
        free(libreria->categorie[i].libri);
    }
    free(libreria->categorie);
}

// Funzione che importa un libro in una categoria
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

// Funzione che importa una categoria nella libreria
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

// Funzione che cerca l'esistenza di una categoria della libreria. Se presente ne restituisce l'indice, altrimenti -1
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

// Funzione che importai dati del file CSV nella libreria
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
    libreria->importato = 1;
    fclose(f);
}

//Funzione che controlla se il file CSV è stato importato
int controlloImportazione(Libreria *libreria)
{
    if (libreria->importato == 0)
    {
        printf("Il file CSV non è ancora stato importato\n\n");
        return -1;
    }
}

//Funzione che stampa tutti i libri della libreria o solo quelli di una categoria specifica
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

//Funzione che cerca un libro nella libreria e ne restituisce un puntatore se lo trova, NULL se non lo trova
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

//Funzione che esegue le funzioni del menù a seconda della scelta dell'utente
void menuEsecuzione(Libreria *libreria, int scelta)
{
    switch (scelta)
    {
    case 1:
        importaCSV(libreria);
        break;

    case 2:
    {
        if (controlloImportazione(libreria) == -1)
        {
            return;
        }

        stampaLibreria(libreria, NULL);
    }
    break;

    case 3:
    {
        if (controlloImportazione(libreria) == -1)
        {
            return;
        }

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
        if (controlloImportazione(libreria) == -1)
        {
            return;
        }

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
    Libreria libreria; //Dichiarazione della libreria

    //Array di stringhe contenente le opzioni del menù
    char *funz[FUNCTIONS] = {"Importa CSV", "Stampa libri", "Cerca libro dato nome", "Cerca libri data categoria", "Esci"};
    int scelta;

    initLibreria(&libreria);

    //Ciclo che itera finchè l'utente non sceglie l'opzione "Esci"
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
