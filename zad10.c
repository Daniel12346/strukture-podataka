#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERR -1
#define MAX 200
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



int NemaPodstabla(Stablo);
int IspisInorderUString(Stablo, char*);
Pozicija StvoriPoziciju(Stablo);
Stablo Pop(Pozicija);
int Push(Pozicija, Stablo);
Stablo StvoriStablo(char*);



int main()
{
    FILE *fp = fopen("postfiks.txt", "r");
    FILE *fp2 = fopen("infiks.txt", "w+");
    Stablo stablo = NULL, s1 = NULL, s2 = NULL, tmp_stablo = NULL;
    Pozicija stog = StvoriPoziciju(tmp_stablo);
    //u buff se upisuje tekst iz ulazne datoteke (sa prefiks izrazom)
    //str je spremnik u koji se upisuje broj tj. služi za pretvorbu inta u string
    //u str_dat funkcija IspisInorder ispisuje sadržaj stabla (infiks izraz), koji se pomoću str_dat zapisuje u izlaznu datoteku
    char buff[MAX], str[MAX], str_dat[MAX], tmp_str[2];
    int count = 0, fsize = 0, tmp = NOT_SET;
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    rewind(fp);
    fread(buff, 1, fsize, fp);
    fclose(fp);
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
		    /*sastavljanje broja od vise znakova: sa svakim novim znakom koji predstavlja znamenku, broj koji se sastavlja se množi sa 10, a najnovija znamenka (novi znak) ide na zadnje mjesto*/
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
    if (stablo == NULL) return ERR;
    IspisInorderUString(stablo, str_dat);
    /* str_dat + 6 jer printf u rekurzivnoj funkciji preskace određeni broj mjesta u stringu pri svakom pozivu. Bez tog preskakanja bi uvijek upisivao u str[0] (na početak stringa) i funkcija ne bi radila. +6 ovdje kompenzira preskok u prvom pozivu printf u toj funkciji*/
    fputs(str_dat + 6, fp2);
    fclose(fp2);
}


int NemaPodstabla(Stablo s){
    if (s == NULL) return ERR;
    return s->L == NULL && s->D == NULL;
}

int IspisInorderUString(Stablo s, char* str){
    if (s == NULL) return 0;
    if (s->L == NULL || NemaPodstabla(s->L)){ 
       IspisInorderUString(s->L, str);
    }else{
    	sprintf(str + strlen(str), "(");
    	IspisInorderUString(s->L, str + strlen(str));
    	sprintf(str + strlen(str), ")");
    }

    sprintf(str + strlen(str), "%s", s->el);

    if (s->D == NULL || NemaPodstabla(s->D)){  
    	IspisInorderUString(s->D, str);
    }else{
    	sprintf(str + strlen(str), "(");
    	IspisInorderUString(s->D, str + strlen(str));
    	sprintf(str + strlen(str), ")");
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
    if (tmp == NULL) return NULL;
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
