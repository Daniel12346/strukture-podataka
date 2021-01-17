#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERR -1
#define MAX 100
#define NOT_SET -2

//brojevi mogu biti višeznamenkasti pa ih se u zapisu u datoteci treba odvajati razmakom
//npr. 3+445 =>   3 445 +

typedef struct _stablo_cvor StabloCvor;
typedef StabloCvor *Stablo;
struct _stablo_cvor
{
    char el[MAX];
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



int NemaPodstabla(Stablo s){
    if (s == NULL) return ERR;
    return s->L == NULL && s->D == NULL;
}

int IspisInorder(Stablo s){
    if (s == NULL) return 0;
    if (s->L == NULL || NemaPodstabla(s->L)){ 
       IspisInorder(s->L);
    }else{
    	printf("(");
    	IspisInorder(s->L);
    	printf(")");
    }

    printf("%s", s->el);

    if (s->D == NULL || NemaPodstabla(s->D)){ 
       IspisInorder(s->D);
    }else{
    	printf("(");
    	IspisInorder(s->D);
    	printf(")");
    }
}


Pozicija StvoriPoziciju(Stablo s)
{
    Pozicija p = malloc(sizeof(Cvor));
    if (p == NULL)
        return NULL;
    p->next = NULL;
    p->stablo = s;
    return p;
}

int Push(Pozicija stog, Stablo s){
    if (stog == NULL) return ERR;
    Pozicija p = StvoriPoziciju(s);
    if (p == NULL) return ERR;
    p->next = stog->next;
    stog->next = p;
}


Stablo Pop(Pozicija stog){
    Stablo s = NULL;
    Pozicija tmp = NULL;
    if (stog == NULL) return NULL;
    tmp = stog->next;
    stog->next = tmp->next;
    s = tmp->stablo;
   // IspisInorder(s);
    free(tmp);
    return s; 
}



Stablo StvoriStablo(char* el)
{
    Stablo s = malloc(sizeof(StabloCvor));
    if (s == NULL)
        return NULL;
    s->L = NULL;
    s->D = NULL;
    strcpy(s->el, el);
    return s;
}


int main()
{
    FILE *fp = fopen("postfiks.txt", "r");
    Stablo stablo = NULL, s1 = NULL, s2 = NULL, tmp_stablo = NULL;
    Pozicija stog = StvoriPoziciju(tmp_stablo);
    char buff[MAX], str[MAX], tmp_str[2];
    int count = 0, fsize = 0, tmp = NOT_SET;
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    rewind(fp);
    fread(buff, 1, fsize, fp);
    //TODO: ovo u novu funkciju
    for (int i = 0; i < fsize; i++){
        switch(buff[i]){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		    //sastavljanje broja od vise znakova: sa svakim novim znakom koji predstavlja znamenku, broj koji se sastavlja se množi sa 10, a najnovija znamenka (novi znak) ide na zadnje mjesto
		    if (tmp == NOT_SET){
		      tmp = buff[i] - '0';
		    }else{
		      tmp = 10 * tmp + buff[i] - '0';	
		    }
		    break;
		case '+':
		case '-':
		case '*':
		case '/':

	
			//ako naiđemo na prazninu, prestaje sastavljanje broja i taj postaje element stabla koje ide na stog
	                if (tmp != NOT_SET){
		            //stvaranje stringa od int elementa
			    sprintf(str, "%d", tmp);
			    tmp_stablo = StvoriStablo(str);
			    if (tmp_stablo == NULL){
				return ERR;	
			    }
			    Push(stog, tmp_stablo);
			};
			tmp = NOT_SET;



			//sastavljanje stringa od operanda i znaka za kraj stringa
			//jer cvor stabla sadrzi char*, a ne sami char
			tmp_str[0] = buff[i];
			tmp_str[1] = '\0';
			s2 = Pop(stog);
			s1 = Pop(stog);
			if (s1 == NULL || s2 == NULL){
			    printf("Greska u datoteci\n");
			    return ERR;
			};
			tmp_stablo = StvoriStablo(tmp_str);
			if (tmp_stablo == NULL) return ERR;
			tmp_stablo->L = s1;
			tmp_stablo->D = s2;
			Push(stog, tmp_stablo);
		default:  
	                if (tmp != NOT_SET){
			    sprintf(str, "%d", tmp);
			    tmp_stablo = StvoriStablo(str);
			    if (tmp_stablo == NULL){
				return ERR;	
			    }
			    Push(stog, tmp_stablo);
			};
			tmp = NOT_SET;
			break;
	}	
    }
    stablo = Pop(stog);
    IspisInorder(stablo);
}
