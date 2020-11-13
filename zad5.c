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
int DodajClan(int, Pozicija);
Pozicija Unija(Pozicija, Pozicija);

Pozicija UnesiListuIzDatoteke(FILE *);

int main()
{
}

Pozicija Unija(Pozicija p, Pozicija q)
{
    Pozicija unija = StvoriPoziciju();
    if (unija == NULL)
        return NULL;
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
    return unija;
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

int DodajClan(int el, Pozicija p)
{
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

Pozicija UnesiListuIzDatoteke(FILE *fp)
{
    char *buff = NULL;
    fread(buff, );
}
