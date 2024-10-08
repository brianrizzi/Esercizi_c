#include <stdio.h>

//Creo la mia struct contente le variabili che rappresentato le coordinate del mio punto
typedef struct
{
    int x, y, z;
} punto;

//faccio una funzione che stampa le coordinate del mio primo punto
void stampa_punto(punto p)
{
    printf("x <<  %d\ny <<  %d\nz <<  %d\n", p.x, p.y, p.z);
}

//faccio una funziona che incrementa le coordinate del primo punto di 1 e che successivamente le stampa
void punto_modificato(punto p)
{
    p.x++;
    p.y++;
    p.z++;

    printf("x <<  %d\ny <<  %d\nz <<  %d\n", p.x, p.y, p.z);
}

int main(int argc, char *argv[])
{
    //dichiaro i miei punti
    punto p1, p2;

    p1.x = 10;
    p1.y = 10;
    p1.z = 10;
    p2 = p1;

    stampa_punto(p1);
    printf("==========\n");
    punto_modificato(p2);

    return 0;
}