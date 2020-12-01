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
//TODO: unos listi
Pozicija StvoriPoziciju();
int Ispisi(Pozicija);
int DodajClan(int, Pozicija);
Pozicija Unija(Pozicija, Pozicija);
Pozicija Presjek(Pozicija, Pozicija);

Pozicija UnesiListuIzDatoteke(FILE *);

int main()
{
	Pozicija L1, L2, unija, presjek;
	L1 = StvoriPoziciju();
	L1->next = NULL;
	DodajClan(3, L1);
	DodajClan(5, L1);
	DodajClan(6, L1);
	DodajClan(9, L1);

	
	L2 = StvoriPoziciju();
	L2->next = NULL;
	DodajClan(2, L2);
	DodajClan(3, L2);
	DodajClan(5, L2);
	DodajClan(8, L2);
	DodajClan(10, L2);

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

/*	

		else if(p->pot > q->pot){		
			if (q->el != 0){
				DodajClanNaKraj(q->el, q->pot, pol_zbr);		
			}
			q = q->next;
		}
		else if(p->pot < q->pot){
			if (p->el != 0){
				DodajClanNaKraj(p->el, p->pot, pol_zbr);
			}
			p = p->next;
		}
	}
	return pol_zbr;
}
*()

/*
int UcitajBrojeveIzLinijeUNiz(FILE *fp, int *p_niz, char *buff){	
	int offset = 0, tmp = 0, i = 0;
	fgets(buff, MAX, fp);
	while(sscanf(buff, "%d%n", &tmp, &offset)==1){
		//pomiče pointer za broj procitanih znakova
		buff += offset;
		p_niz[i] = tmp;
		i++;
	}	
	return i;
}


*/

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
/*
Pozicija UnesiListuIzDatoteke(FILE *fp)
{
    char *buff = NULL;
    fread(buff, );
}*/
