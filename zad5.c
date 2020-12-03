#include <stdio.h>
#include <stdlib.h>

typedef struct _clan Clan;
typedef Clan *Pozicija;

#define MAX 100
#define ERR -1

struct _clan
{
    int el;
    Pozicija next;
};

Pozicija StvoriPoziciju();
Pozicija UnosListe();
int Ispisi(Pozicija);
int DodajClan(int, Pozicija);
Pozicija Unija(Pozicija, Pozicija);
Pozicija Presjek(Pozicija, Pozicija);

Pozicija UnesiListuIzDatoteke(FILE *);

int main()
{
	Pozicija L1, L2, unija, presjek;
	printf("Unesite elemente 1.liste\n");
	L1 = UnosListe();
	getchar();
	printf("\nUnesite elemente 2.liste\n");
	L2 = UnosListe();
	printf("Unija: ");
	unija = Unija(L1->next, L2->next);
	Ispisi(unija);
	printf("\n ");

	printf("Presjek: ");
	presjek = Presjek(L1->next, L2->next);
	Ispisi(presjek);
}

Pozicija Unija(Pozicija p, Pozicija q)
{
    //u_poc pokazuje na pocetak od u
    Pozicija u = StvoriPoziciju(), u_poc = NULL;
    if (u == NULL)
        return NULL;
    u->next = NULL;
    u_poc = u;
    while (p != NULL && q != NULL)
    {	
        if (p->el > q->el)
        {
            DodajClan(q->el, u);
            q = q->next;
            u = u->next;
        }
        else if (p->el < q->el)
        {
            DodajClan(p->el, u);
            p = p->next;
            u = u->next;
        }
        else
        {
            DodajClan(p->el, u);
            p = p->next;
            q = q->next;
            u = u->next;
        }
    }
    if (p == NULL)
    {
        while (q != NULL)
        {
            DodajClan(q->el, u);
            q = q->next;
            u = u->next;
        }
    }
    else if (q == NULL)
    {
        while (p != NULL)
        {
            DodajClan(p->el, u);
            p = p->next;
            u = u->next;
        }
    }
    
    return u_poc->next;
}

Pozicija Presjek(Pozicija p, Pozicija q)
{
 
    Pozicija pre = StvoriPoziciju(), pre_poc = NULL;
    if (pre == NULL)
        return NULL;
    pre->next = NULL;
    pre_poc = pre;
    while (p != NULL && q != NULL)
    {	
        if (p->el > q->el)
        {
            q = q->next;
        }
        else if (p->el < q->el)
        {
            p = p->next;
        }
        else
        {
            DodajClan(p->el, pre);
            p = p->next;
            q = q->next;
            pre = pre->next;
        }
    }
    
    return pre_poc->next;
}


int Ispisi(Pozicija p){
	while (p != NULL){
		printf("%d ",p->el);
		p = p->next;
	}
}

int DodajClan(int el, Pozicija p)
{
	if (p == NULL) return -1;
	while (p->next != NULL){
		p = p->next;
	}	
    Pozicija q = StvoriPoziciju();
    if (q == NULL)
        return -1;
    q->el = el;
    q->next = p->next;
    p->next = q;
}

Pozicija StvoriPoziciju()
{
    Pozicija q = (Pozicija)malloc(sizeof(Clan));
    if (q == NULL)
    {
        printf("Greska - nema dovoljno prostora\n");
        return NULL;
    }
    return q;
}

Pozicija UnosListe(){
	Pozicija p = StvoriPoziciju(), p_poc;
	if (p == NULL) return NULL;
	p_poc = p;
	int el = 0; 
	char tmp;
	printf("Unesite prvi element liste (za prekid unesite bilo koji znak koji nije broj)\n");
	while(scanf("%d%c", &el, &tmp)){
		printf("Unesite sljedeći element liste\n");
		if (!p->el || el >= p->el){
			DodajClan(el, p);
			p = p->next;
		} 
		else{
			printf("Brojevi moraju biti uzlazno sortirani! Unesite novi element\n");
		} 
	}
	return p_poc;
}
