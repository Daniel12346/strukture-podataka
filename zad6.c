#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ERR -1

typedef struct _clan Clan;
typedef Clan *Pozicija;

struct _clan
{
    int el;
    Pozicija next;
};
Pozicija StvoriPoziciju();
int Push(Pozicija);
int PopStog(Pozicija);
int PopRed(Pozicija, Pozicija*);
int Ispisi(Pozicija);
int main()
{
    srand(time(NULL));
    Pozicija stog = StvoriPoziciju(), red = StvoriPoziciju(), red_kraj = NULL;
    Push(stog); 
    Push(stog); 
    Push(stog);
    Ispisi(stog);
    printf("\npop stog: %d\n", PopStog(stog));
    Ispisi(stog);
    
    printf("\n\n");
    Push(red); 
    Push(red); 
    Push(red);
    Ispisi(red);
    printf("\npop Red: %d\n", PopRed(red, &red_kraj));
    printf("\npop Red: %d\n", PopRed(red, &red_kraj));
    Ispisi(red);
    
}

Pozicija StvoriPoziciju()
{
    Pozicija q = malloc(sizeof(Clan));
    if (q == NULL)
    {
        printf("Greska - nema dovoljno prostora\n");
        return NULL;
    }
    return q;
}

int Push(Pozicija p)
{
    Pozicija q = StvoriPoziciju();
    int rnd = 10 + rand() % (101 - 10);
    if (q == NULL)
        return ERR;
    q->el = rnd;
    q->next = p->next;
    p->next = q;
}

int PopStog(Pozicija p)
{
    Pozicija tmp = p->next;
    int el = tmp->el;
    p->next = tmp->next;
    free(tmp);
    return el;
}

int Ispisi(Pozicija p){
	while (p != NULL){
		printf("%d ",p->el);
		p = p->next;
	}
}

int PopRed(Pozicija p, Pozicija* p_kraj)
{
    
    int el;
    Pozicija q = p, tmp = NULL;
    if (*p_kraj == NULL){
        while(q->next && q->next->next != NULL){
            q = q->next;
        }
    }
  
    tmp = q->next;
    el = tmp->el;  
    q->next = tmp->next;
    *p_kraj = q->next;
    free(tmp);
    return el;
}
