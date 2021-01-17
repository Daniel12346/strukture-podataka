#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERR -1
#define MAX 100

typedef struct _stablo_cvor StabloCvor;
typedef StabloCvor *Stablo;
struct _stablo_cvor
{
    char* el;
    Stablo L;
    Stablo D;
};


typedef struct _cvor Cvor;
typedef Cvor *Pozicija;
struct _cvor
{
    Stablo stablo;
    Pozicija next;
};



Pozicija StvoriPoziciju(Stablo s)
{
    Pozicija p = malloc(sizeof(Cvor));
    if (p == NULL)
        return NULL;
    p->next = NULL;
    p->stablo = s;
}

int Push(Pozicija stog, Stablo s){
    if (stog == NULL) return ERR;
    Pozicija p = StvoriPoziciju(s);
    if (p == NULL) return ERR;
    p->next = stog->next;
    stog->next = p;
}

Stablo Pop(Pozicija stog){
    Pozicija tmp = NULL;
    if (stog == NULL) return NULL;
    tmp = stog->next;
    stog->next = tmp->next;
    free(tmp);
}



Pozicija StvoriStablo(char* el)
{
    Stablo s = malloc(sizeof(StabloCvor));
    if (s == NULL)
        return NULL;
    s->L = NULL;
    s->D = NULL;
    strcpy(s->el, el);
}

int main()
{
    FILE *fp = fopen("postfiks.txt", "r");
    Pozicija stog = NULL;
    Stablo stablo = NULL;
    char buff[100];
    int count = 0, fsize = 0;
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    rewind(fp);
    fread(buff, 1, fsize, fp);
    while(){}
}
