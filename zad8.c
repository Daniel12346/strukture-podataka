#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30
#define ERR -1

typedef struct _dir Dir;
typedef Dir *P_dir;

typedef struct _cvor Cvor;
typedef Cvor *Pozicija;

struct _dir
{
    char ime[MAX];
    P_dir child;
    P_dir sibling;
};

struct _cvor
{
    P_dir p_parent;
    Pozicija next;
};

Pozicija StvoriPoziciju();
P_dir Pop(Pozicija);
int Push(Pozicija, P_dir);
P_dir StvoriDirektorij(char*);
int SortiraniUnos(P_dir, P_dir);
int BrisiListu(Pozicija);
int BrisiDirektorij(P_dir);

P_dir md(Pozicija, P_dir, char*);
int dir(P_dir);
P_dir cd(Pozicija, P_dir, char*);
P_dir cd_natrag(Pozicija, P_dir);
int izlaz(Pozicija, P_dir);

int main()
{
    int izbor = 0;
    char ime[MAX], opcije[] = "Odaberite opciju: \n1 - md \n2 - cd dir \n3 - cd.. \n4 - dir \n5 - izlaz\n\n";
    Pozicija stog = NULL;
    P_dir root = NULL, curr = NULL, rez = NULL;
    stog = StvoriPoziciju();
    if (stog == NULL)  return ERR;
    root = StvoriDirektorij("C:");
    if (root == NULL) return ERR;
    curr = root;
    printf("%s", opcije);
    while(izbor != 5){
	//izbor je postavljen na 5 prije nego što korisnik unese svoj izbor da se izbjegne beskonačna petlju ako vrijednost koju korisnik upiše nije jedna od dozvoljenih  (1, 2, 3, 4, 5)	
	izbor = 5;
        scanf("%d", &izbor);
        printf("\n");
        switch(izbor){
           case 1: 
               printf("\nOdabrano: md\n");
               printf("Upisite ime nove datoteke:\n");
               scanf("%s", ime);
               rez = md(stog, curr, ime);
               if (rez == NULL){
                   printf("Dogodila se greska, datoteka se nije mogla stvoriti\n");
               }
               printf("%s", opcije);
	       break;
           case 2: 
               printf("\nOdabrano: cd dir\n");
               printf("Upisite ime datoteke (dir):\n");
               scanf("%s", ime);
               rez = cd(stog, curr, ime);
               if (rez == NULL){
                   printf("Dogodila se greska\n");
               }
               else{
		   //ako nije bilo gresaka, trenutni direktorij postaje onaj koji cd vrati
                   curr = rez;
               }
    	       printf("%s", opcije);
	       break;
           case 3: 
               printf("\nOdabrano: cd..\n");
               rez = cd_natrag(stog, curr);
               if (rez == NULL){
                   printf("Dogodila se greska\n");
               }else{
                   curr = rez;
               }
               printf("%s", opcije);
	       break;
           case 4:
               printf("\nOdabrano: dir\n");
               if (dir(curr) == ERR) printf("Dogodila se greska\n");
	       printf("\n%s", opcije);
	       break;   

           //bez case 5 jer se cijela while petlja prekida ako je izbor 5
           default: 
		break; 
        }
    }
        printf("\nOdabrano: izlaz\n");
        //TODO: oslobađanje memorije
}

Pozicija StvoriPoziciju()
{
    Pozicija q = malloc(sizeof(Cvor));
    if (q == NULL)
    {
        printf("Greska - nema dovoljno memorije");
        return NULL;
    }
    q->next = NULL;
    return q;
}

P_dir Pop(Pozicija stog)
{
    Pozicija tmp = NULL;
    P_dir p = NULL;
    if (stog == NULL || stog->next == NULL)
        return NULL;
    tmp = stog->next;
    p = tmp->p_parent;
    stog->next = tmp->next;
    free(tmp);
    return p;
}

int Push(Pozicija stog, P_dir p)
{
    Pozicija q = NULL;
    if (stog == NULL)
        return ERR;
    q = StvoriPoziciju();
    if (q == NULL)
        return ERR;
    q->p_parent = p;
    q->next = stog->next;
    stog->next = q;
}

P_dir StvoriDirektorij(char *ime)
{
    P_dir q = malloc(sizeof(Dir));
    if (q == NULL)
    {
        printf("Greska - nema dovoljno memorije");
        return NULL;
    }
    q->sibling = NULL;
    q->child = NULL;
    strcpy(q->ime, ime);
    return q;
}

int SortiraniUnos(P_dir p, P_dir q){
    //TODO: dealocirat privremene varijable
    P_dir tmp = p, head = NULL, r = NULL;
    /* head je početak vezane liste sastavljene od child elementa trenutnog direktorija i svih siblinga tog elementa,
    ovako je sortiranje jednostavnije jer je dobivena struktura obična vezana lista pa u nijednoj iteraciji pretraživanja ne treba provjeravati ni mijenjati child element od p  */
    head = StvoriDirektorij(" ");
    if (head == NULL) return ERR;    
    r = head;
    if (p == NULL || q == NULL) return ERR;
    if (p->child == NULL){
	p->child = q;
	return 0;	
    }
    head->sibling = p->child;
    while(r->sibling != NULL && strcmp(r->sibling->ime, q->ime) < 0){
	r = r->sibling;
    }
    q->sibling = r->sibling;
    r->sibling = q;
    //postavljamo prvi element sortirane liste za child trenutnog direktorija (p)
    p->child = head->sibling;
}

int BrisiListu(Pozicija lista){
    Pozicija tmp = NULL;
    P_dir tmp_dir = NULL;
    while(lista->next != NULL){
        tmp = lista;
        lista = lista->next;
        free(lista);
    }
}

//TODO: provjerit
int BrisiDirektorij(P_dir p){
    P_dir tmp = NULL;
    //tmp = StvoriDirektorij(" ");
    if(p == NULL) return ERR;
    if(p->child == NULL){
        free(p);
    }
    while(p->sibling != NULL){
        tmp = p;
        BrisiDirektorij(p);
        p = p->sibling;
    } 
}

P_dir md(Pozicija stog, P_dir p, char *ime){
    if (p == NULL) return NULL;
    P_dir q = NULL, tmp = NULL;
    q = StvoriDirektorij(ime);
    if (q == NULL) return NULL;
    if (p->child == NULL){
	p->child = q;
    }
    else{
	SortiraniUnos(p, q);
    }
    return q;
}

int dir(P_dir p){
    P_dir tmp = NULL;
    if (p == NULL) return ERR;
    if (p->child != NULL){
	tmp = p->child;
	while (tmp != NULL){
	     printf("     %s\n", tmp->ime);
	     tmp = tmp->sibling;
	}
    }
}

//jedino cd i cd_natrag (cd..) mijenjaju stog
P_dir cd(Pozicija stog, P_dir p, char *ime){
    //q je direktorij koji trazimo
    P_dir q = NULL, tmp = NULL;
    if (p->child == NULL) return NULL;
    tmp = p->child;
    if (strcmp(ime, tmp->ime) == 0){
	q = tmp;
    }else{
        while (tmp != NULL){
    	    if (strcmp(ime, tmp->ime) == 0){
                q = tmp;
            } 
            tmp = tmp->sibling;
        }
    }
    if (q == NULL) return NULL;
    Push(stog, p);
    return q;
}

P_dir cd_natrag(Pozicija stog, P_dir p){
    return Pop(stog);
}


int izlaz(Pozicija stog, P_dir p){
    P_dir tmp = NULL, poc = p, head = NULL;  
    if (BrisiListu(stog) == ERR || BrisiDirektorij(p) == ERR) return ERR;
}
