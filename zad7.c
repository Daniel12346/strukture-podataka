#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ERR -1

//TODO: greske u datoteci, floatovi?

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
    fclose(fp);
  //  printf("%s", buff);
    rez = RacunajPrefiks(buff, n);
    printf("Rez: %d", rez);
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

    char *tmp = NULL;
    int fsize;
    if (fp == NULL){
	printf("Datoteka se nije otvorila\n");
	return -1;	
    } 
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp) + 1;
    rewind(fp);
    *p_buff = realloc(*p_buff, fsize  * sizeof(char));
    fread(*p_buff, fsize, 1, fp);
   /* strcpy(tmp, *p_buff);
    printf("%s ", *p_buff);*/
    return fsize;
}

int RacunajPrefiks(char *tekst, int n)
{
    Pozicija stog = StvoriPoziciju();
    int tmp1 = 0, tmp2 = 0;
    if (stog == NULL)
        return -1;
    
    for (int i = 0; i < n; i++)
    {
	 //printf("%d", tekst[i] == '+'); 
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
	    Push(stog, tmp2 + tmp1); 
	    break;

        case ('-'):
	    tmp1 = Pop(stog);
	    tmp2 = Pop(stog);
	    Push(stog, tmp2 - tmp1);
	    break;
        case ('*'):
	    tmp1 = Pop(stog);
	    tmp2 = Pop(stog);
	    Push(stog, tmp2 * tmp1);
            break;
        case ('/'):
	    tmp1 = Pop(stog);
	    tmp2 = Pop(stog);
	    Push(stog, tmp2 / tmp1);
	    break;	

	default:
	   break;
	}	
    }
 /*   printf("POP: %d\n", Pop(stog));
    printf("POP: %d", Pop(stog));*/
   return Pop(stog);
}

