#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define ERR -1

typedef struct _clan Clan;
typedef Clan* Pozicija;

Pozicija StvoriPoziciju();
int DodajClanNaKraj(int, int, Pozicija);
int SortDodajClan(int, int, Pozicija);

Pozicija ZbrojiPolinome(Pozicija, Pozicija);
Pozicija MnoziPolinome(Pozicija, Pozicija);

//cita brojeve iz jedne linije iz datoteke i vraca broj ucitanih brojeva
int UcitajBrojeveIzLinijeUNiz(FILE *,int*, char*);

//pretpostavlja da se u datoteci nalazi samo jedan red koeficijenata i jedan red eksponenata (potencija)
Pozicija UcitajPolinomIzDat(FILE *fp, char*);	

int Ispisi(Pozicija p);

struct _clan {
	int koef;
	int pot;
	Pozicija next; 
};

int main(){
	Pozicija pol1 = NULL, pol2 = NULL, zbroj = NULL, umnozak = NULL; 
	FILE *fp1, *fp2 = NULL;	
	char buff1[MAX], buff2[MAX];	
	fp1 = fopen("polinom1.txt", "r");
	fp2 = fopen("polinom2.txt", "r");
	if (fp1 == NULL || fp2 == NULL){
		printf("Greska - otvaranje datoteke nije uspjelo\n");
		return -1;
	};
	
	pol1 = UcitajPolinomIzDat(fp1, buff1);	
	pol2 = UcitajPolinomIzDat(fp2, buff2);

	if (pol1 == NULL || pol2 == NULL) return ERR;

	printf("1. polinom: ");
	Ispisi(pol1);

	printf("2. polinom: ");
	Ispisi(pol2);
	
	zbroj = ZbrojiPolinome(pol1, pol2);

	printf("Zbroj polinoma: ");
	Ispisi(zbroj);

	umnozak = MnoziPolinome(pol1, pol2);
	
	printf("Umnozak polinoma: ");
	Ispisi(umnozak);
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
		printf("+ %dx^%d", p->koef, p->pot);
		p = p->next;
	}
	printf("\n");
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


Pozicija MnoziPolinome(Pozicija pol1, Pozicija pol2){
	//pol_umnoz je konacni rezultat mnozenja, pol2_poc je pocetak drugog polinoma, tmp kasnije poprima vrijednost jednoclanog polinoma  
	Pozicija pol_umnoz = NULL, pol2_poc = pol2, tmp = NULL;
	pol_umnoz = StvoriPoziciju();
	if (pol_umnoz == NULL){
		return NULL;
	}
	pol_umnoz->next = NULL;
	//prolazi kroz sve clanove prvog polinoma
	while (pol1 != NULL){	
	//za svaki clan prvog polinoma prolazi kroz sve clanove drugog polinoma, na kraju petlje vraća drugi polinom na pocetak
		while(pol2 != NULL){
			//zbrajamo tako da ukupnom rezultatu zasebno pribrajamo clanove koji nastaje pri mnozenju svakog clana prvog polinoma sa svakim clanom drugog polinoma
			tmp = StvoriPoziciju();
			if (tmp == NULL){
				return NULL;
			};
			tmp->next = NULL;
			tmp->koef = pol1->koef * pol2->koef;
			tmp->pot = pol1->pot + pol2->pot;
			pol_umnoz = ZbrojiPolinome(pol_umnoz, tmp);
			pol2 = pol2->next;
		}	
		pol1 = pol1->next;
		pol2 = pol2_poc;
	}
	return pol_umnoz;
}


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

Pozicija UcitajPolinomIzDat(FILE *fp, char *buff){	
	Pozicija head = StvoriPoziciju();
	head->next = NULL;
	int len, koeficijenti[MAX], potencije[MAX];
	
	if(head == NULL){
		printf("Nedovoljno prostora");
		return NULL;
	}
	//len je duljina niza koeficijenata (i niza potencija) tj. broj članova polinoma
	if( (len = UcitajBrojeveIzLinijeUNiz(fp, koeficijenti, buff)) != UcitajBrojeveIzLinijeUNiz(fp, potencije, buff) ){
		printf("Greska - nije jednak broj eksponenata i potencija zadan u datoteci, polinom nije valjan");
		return NULL;
	}
	
	for (int i = 0; i < len; i++){	
		SortDodajClan(koeficijenti[i], potencije[i], head);
	}
	return head;
}
