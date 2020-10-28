#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define ERR -1


struct _osoba{
	char ime[MAX];
	char prez[MAX];
	int god;
};
typedef struct _osoba Osoba;

typedef struct _cvor Cvor;
typedef Cvor* Pozicija;
struct _cvor{
	Osoba osoba;
	Pozicija next;
};


Pozicija StvoriCvor();
int DodajNaPoc(Osoba, Pozicija);
int Ispisi(Pozicija);
int DodajNaKraj(Osoba, Pozicija);
Pozicija Trazi(char[MAX], Pozicija);
int Obrisi(char[MAX], Pozicija);

int main()
{
	
	Pozicija head = StvoriCvor();
	head->next = NULL;
/*	Osoba os1, os2, os3;
	Pozicija pozB;
	strcpy(os1.ime, "A");
	strcpy(os1.prez, "B");
	os1.god = 20;
	
	strcpy(os2.ime, "C");
	strcpy(os2.prez, "D");
	os2.god = 20;
	
	strcpy(os3.ime, "X");
	strcpy(os3.prez, "Y");
	os3.god = 100;

	DodajNaPoc(os1, head);
	DodajNaPoc(os2, head);
	DodajNaKraj(os3, head);
	Ispisi(head);
	Obrisi("B", head);
	Ispisi(head);*/
}


Pozicija StvoriCvor()
{
	Pozicija p = malloc(sizeof(Cvor));
	if (p == NULL){
		printf("Greska, nedovoljno memorije\n");
		return NULL;
	}
	return p;
}


int DodajNaPoc(Osoba osoba, Pozicija p)
{
	Pozicija q = StvoriCvor();
	if (q == NULL) return ERR;
	q->osoba = osoba;
	q->next = p->next;
	p->next = q;
}


int Ispisi(Pozicija p)
{
	while (p != NULL){
		printf("%s %s %d\n", p->osoba.ime, p->osoba.prez, p->osoba.god);
		p = p->next;
	}
}

int DodajNaKraj(Osoba osoba, Pozicija p)
{	
	Pozicija q = StvoriCvor();
	if (q == NULL) return ERR;
	q->osoba = osoba;
	while (p->next != NULL){
		p = p->next;
	};
	p->next = q;
	
}

Pozicija Trazi(char prez[MAX], Pozicija p)
{
	while(p->next != NULL && strcmp(p->osoba.prez, prez)){
		p = p->next;
	}
	return p;
}


int Obrisi(char prez[MAX], Pozicija p)
{
	Pozicija prev = p;
	while (prev->next != NULL && strcmp(prev->next->osoba.prez, prez)){
		prev = prev->next;
	}
	prev->next = prev->next->next;
	free(p);
}




