#include <stdio.h>
#define MAX 30
#define ERR -1

struct _cvor
{
    P_dir p_parent;
    Pozicija next;
};
typedef struct _cvor Cvor;
typedef Cvor *Pozicija;

struct _dir
{
    char ime[MAX];
    Pozicija child;
    Pozicija sibling;
};
typedef struct _dir Dir;
typedef Dir *P_dir;

Pozicija StvoriPoziciju()
{
    Pozicija q = malloc(sizeof(Cvor));
    if (q == NULL)
    {
        printf("Greska - nema dovoljno memorije");
        return NULL;
    }
    q->next = NULL;
    return q;
}

P_dir Pop(Pozicija stog)
{
    Pozicija tmp = NULL;
    P_dir p = NULL;
    if (stog == NULL || stog->next == NULL)
        return NULL;
    tmp = stog->next;
    p = tmp->p_parent;
    stog->next = tmp->next;
    free(tmp);
    return p;
}

int Push(Pozicija stog, P_dir p)
{
    Pozicija q = NULL;
    if (stog == NULL)
        return ERR;
    q = StvoriPoziciju();
    if (q == NULL)
        return ERR;
    q->p_parent = p;
    q->next = stog->next;
    stog->next = q;
}

P_dir StvoriDatoteku()
{
    P_dir q = malloc(sizeof(Dir));
    if (q == NULL)
    {
        printf("Greska - nema dovoljno memorije");
        return NULL;
    }

    return q;
}

int main()
{
    Pozicija stog = StvoriPoziciju();
    if (stog == NULL)
        return ERR;
}
