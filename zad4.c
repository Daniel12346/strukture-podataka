#include <stdio.h>
#include <stdlib.h>

#define ERR -1

typedef struct _clan Clan;
typedef Clan* Pozicija;

Pozicija StvoriPoziciju();
int DodajClanNaKraj(int, int, Pozicija);
int SortDodajClan(int, int, Pozicija);
Pozicija ZbrojiPolinome(Pozicija, Pozicija);
int Ispisi(Pozicija p);

struct _clan {
	int koef;
	int pot;
	Pozicija next; 
};

int main(){
	Pozicija p1 = NULL, p2 = NULL, zbr = NULL;
	//npr. 4x^0 + 2x^1 + 2x^4 + 5x^5 + 6x^6 +7x^7 
	p1 = StvoriPoziciju();
	p1->next = NULL;

	//npr. 2x^0 + 8x^2 + 7x^3  + 5x^5 + 6x^6 +7x^7 
	p2 = StvoriPoziciju();
	p2->next = NULL;

	SortDodajClan(2, 1, p1);
	SortDodajClan(4, 0, p1);
	SortDodajClan(2, 4, p1);
	SortDodajClan(12, 2, p1);
	SortDodajClan(7, 7 ,p1);
	SortDodajClan(6,  6,p1);
	SortDodajClan(5, 5 ,p1);

	SortDodajClan(5, 5 ,p2);
	SortDodajClan(6,  6,p2);
	SortDodajClan(7, 7 ,p2);
	SortDodajClan(7, 3, p2);
	SortDodajClan(8, 2, p2);
	SortDodajClan(2, 0, p2);

	Ispisi(p1);
	printf("\n");
	Ispisi(p2);

	zbr = ZbrojiPolinome(p1, p2);
	printf("\n");
	Ispisi(zbr);
	
}

int DodajClanNaKraj(int koef, int pot, Pozicija p){
	Pozicija q = StvoriPoziciju();
	if (q == NULL) return ERR;
	while(p->next != NULL){
		p = p->next;
	}
	q->koef = koef;
	q->pot = pot;
	q->next = p->next;
	p->next = q;
}

int SortDodajClan(int koef, int pot, Pozicija p){
	Pozicija q = StvoriPoziciju();
	if (q == NULL) return ERR;
	while(p->next != NULL && (p->next->pot < pot)){
		p = p->next;
	};
	q->koef = koef;
	q->pot = pot;
	q->next = p->next;
	p->next = q;
}

Pozicija StvoriPoziciju(){
	Pozicija q = (Pozicija) malloc(sizeof(Clan));
	if (q == NULL){
	    printf("Greska - nema dovoljno prostora\n");
	    return NULL;
	}
	return q;
}

int Ispisi(Pozicija p){
	while(p != NULL){
		printf("%dx^%d +", p->koef, p->pot);
		p = p->next;
	}
}


Pozicija ZbrojiPolinome(Pozicija pol1, Pozicija pol2){
	Pozicija pol_zbr = StvoriPoziciju();
	if (pol_zbr == NULL) return NULL;
	pol_zbr->next = NULL;
	//iteriramo dok ne dodemo do kraja oba polinoma
	while(!(pol1 == NULL && pol2 == NULL)){	
		if(pol1 == NULL){
			//ne dodajemo clan ako je koeficijent uz x jednak 0
			if (pol2->koef != 0){
				DodajClanNaKraj(pol2->koef, pol2->pot, pol_zbr);
			}
			pol2 = pol2->next;
		}
		else if(pol2 == NULL){
			if (pol1->koef != 0){
				DodajClanNaKraj(pol1->koef, pol1->pot, pol_zbr);
			}
			pol1 = pol1->next;
		}
		else if (pol1->pot == pol2->pot){
			//ne dodajemo clan ako je zbroj koeficijenata uz clanove iste potencije oba polinoma jednak nuli (npr. -3x^3 + 3x^3 ili 0x^3 + 0x^3)
			if ((pol1->koef + pol2->koef) != 0){ 
				DodajClanNaKraj(pol1->koef + pol2->koef, pol1->pot, pol_zbr);
			}
			pol1 = pol1->next; 
			pol2 = pol2->next;	
		}
		else if(pol1->pot > pol2->pot){		
			if (pol2->koef != 0){
				DodajClanNaKraj(pol2->koef, pol2->pot, pol_zbr);		
			}
			pol2 = pol2->next;
		}
		else if(pol1->pot < pol2->pot){
			if (pol1->koef != 0){
				DodajClanNaKraj(pol1->koef, pol1->pot, pol_zbr);
			}
			pol1 = pol1->next;
		}
	}
	return pol_zbr;
}
