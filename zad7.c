#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ERR -1

typedef struct _clan Clan;
typedef Clan *Pozicija;

struct _clan
{
    int el;
    Pozicija next;
};

Pozicija StvoriPoziciju();
int Push(Pozicija, int el);
int Pop(Pozicija);
int UcitajIzDatoteke(FILE *, char **);
int RacunajPrefiks(char *, int);

int main()
{
    char *buff = NULL;
    int n = 0, rez = 0;
    buff = malloc(sizeof(char));
    FILE *fp = fopen("postfix.txt", "r");
    n = UcitajIzDatoteke(fp, &buff);
    //zatvaramo datoteku čim tekst iz nje upišemo u buffer
    fclose(fp);
    rez = RacunajPrefiks(buff, n);
    if (rez != ERR){
	printf("Rez: %d", rez);
    }else{ 
        printf("Greska - neispravan postfiks izraz\n");
    }
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

int Push(Pozicija p, int el)
{
    Pozicija q = StvoriPoziciju();
    if (q == NULL)
        return ERR;
    q->el = el;
    q->next = p->next;
    p->next = q;
}

int Pop(Pozicija p)
{
    Pozicija tmp = p->next;
    if (tmp == NULL) return ERR;
    int el = tmp->el;
    p->next = tmp->next;
    free(tmp);
    return el;
}

int UcitajIzDatoteke(FILE *fp, char **p_buff)
{

    int fsize;
    if (fp == NULL){
	printf("Greska - datoteka se ne moze otvoriti\n");
	return ERR;	
    } 
    fseek(fp, 0, SEEK_END);
    //duljina teksta u datoteci
    fsize = ftell(fp) + 1;
    rewind(fp);
    *p_buff = realloc(*p_buff, fsize  * sizeof(char));
    //učitava cijeli tekst iz datoteke u buffer
    fread(*p_buff, fsize, 1, fp);
    return fsize;
}

int RacunajPrefiks(char *tekst, int n)
{
    Pozicija stog = StvoriPoziciju();
    stog->next = NULL;
    int tmp1 = 0, tmp2 = 0, rez = 0;
    if (stog == NULL)
        return ERR;
    
    for (int i = 0; i < n; i++)
    {
         switch (tekst[i])
        {	
        case ('0'):
        case ('1'):
        case ('2'):
        case ('3'):
        case ('4'):
        case ('5'):
        case ('6'):
        case ('7'):
        case ('8'):
        case ('9'):
	    tmp1 = tekst[i] - '0';
            Push(stog, (int) tmp1);
	    break;
        case ('+'):
	    tmp1 = Pop(stog); 
	    tmp2 = Pop(stog);
            if (tmp1 == ERR || tmp2 == ERR) return ERR;
	    Push(stog, tmp2 + tmp1); 
	    break;

        case ('-'):
	    tmp1 = Pop(stog);
	    tmp2 = Pop(stog);
	    Push(stog, tmp2 - tmp1);
            if (tmp1 == ERR || tmp2 == ERR) return ERR;
	    break;
	//prihvaća i '*' i 'x' kao oznaku za množenje
        case ('*'):
	case ('x'):
	    tmp1 = Pop(stog);
	    tmp2 = Pop(stog);
	    //ako je bar jedna od vrijednosti koje popamo sa stoga ERR, nema dovoljno operanada za operaciju koju treba obaviti
            if (tmp1 == ERR || tmp2 == ERR) return ERR;
	    Push(stog, tmp2 * tmp1);
            break;
        case ('/'):
	    tmp1 = Pop(stog);
	    tmp2 = Pop(stog);
            if (tmp1 == ERR || tmp2 == ERR) return ERR;
            /*da bi bilo moguće djeljenje čiji rezultat nije cijeli broj, trebalo bi koristiti float umjesto int u strukturi i svim funkcijama jer bi i konacni rezultat mogao biti decimalni broj, umjesto toga program tretira necjelobrojno djelenje kao grešku*/ 
            if ((float) tmp2/tmp1 != tmp2/tmp1){
            	printf("Greska u izrazu - dozvoljeno je jedino cjelobrojno djeljenje\n");
            }; 
	    Push(stog, tmp2 / tmp1);
	    break;	
        //preskače sve pročitane znakove koji nisu ni brojevi ni operatori
	default:
	   break;
	}	
    }
    rez = Pop(stog); 
    /*ako je rez == ERR na stogu se nije nalazila konačna vrijednost, a ako stog->next nije null iza tražene vrijednosti slijedi još elemenata što je greška jer stog na kraju mora biti prazan*/
    if (rez == ERR || stog->next != NULL){		
	return ERR;		
    }else{
        return rez;
   }
}

