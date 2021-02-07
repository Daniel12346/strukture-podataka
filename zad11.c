#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define ERR -1
#define VEL_TAB 11
#define MAX 100


typedef struct _student Student;
struct _student{
    int mbroj;
    char ime[MAX];
    char prez[MAX];
};

typedef struct _cvor Cvor;
typedef Cvor* Pozicija;
struct _cvor {
    Student student;
    Pozicija next;
};

Student* StvoriStudenta(int mbroj, char ime[MAX], char prez[MAX]){
    Student *ps = malloc(sizeof(Student));
    if (ps == NULL) return NULL;
    ps->mbroj = mbroj;
    strcpy(ps->ime, ime);
    strcpy(ps->prez, prez);
    return ps;
};

Pozicija StvoriPoziciju(Student *ps){
    Pozicija q = malloc(sizeof(Cvor));
    if (q == NULL) return NULL;
    if (ps != NULL) q->student = *ps;
    q->next = NULL;
    return q;
};


int RacunajKljuc(char prez[MAX]){
    int count = 0;
    //TODO: č, ć, ž...?
    for (int i = 0; i < 5 && ((prez[i] >= 'a' && prez[i] <= 'z')||(prez[i] >= 'A' && prez[i] <= 'Z')); i++){
        count += prez[i];
    }
    return count%VEL_TAB;
}

int SortDodajUListu(Pozicija l, Student *ps){
    Pozicija q = StvoriPoziciju(ps);
    if (q == NULL || l == NULL) return ERR;

    while(l->next != NULL && strcmp(l->next->student.prez, ps->prez) < 0){
            l = l->next;
    }
    
    while(l->next != NULL && strcmp(l->next->student.ime, ps->ime) < 0){
            l = l->next;
    }

    q->next = l->next;
    l->next = q;
}

int DodajStudentaUTablicu(Pozicija tab[VEL_TAB], Student *ps){
    int kljuc = RacunajKljuc(ps->prez);
    SortDodajUListu(tab[kljuc], ps);
}

int IspisiListu(Pozicija l){
    while(l != NULL){
        printf("\nmb: %d  ime:%s prezime:%s ", l->student.mbroj, l->student.ime, l->student.prez);
        l = l->next;
    }
}

Student* TraziStudentaUListi(Pozicija l,  char ime[MAX], char prez[MAX]){
    while (l != NULL){
        if (&(l->student) != NULL && !(strcmp(l->student.ime, ime) || strcmp(l->student.prez, prez))){
            return &(l->student);       
        }
        l = l->next;
    }
    return NULL;
}

Student* TraziStudentaUTablici(Pozicija tab[VEL_TAB], char ime[MAX], char prez[MAX]){
    int kljuc = RacunajKljuc(prez);
    return TraziStudentaUListi(tab[kljuc], ime, prez);
}

int main(){
    FILE *fp = fopen("studenti.txt", "r");
    if (fp == NULL){
        printf("Datoteka se nije mogla otvoriti.");
        return ERR;
    }
    Pozicija tab[VEL_TAB];
    for (int i = 0; i < VEL_TAB; i++){
        //postavljanje  head el. svih listi u tablici
        tab[i] = StvoriPoziciju(NULL);
    }
    int tmp_mbroj = 0;
    char tmp_prez[MAX], tmp_ime[MAX];
    while (fscanf(fp, "%d %s %s", &tmp_mbroj, tmp_ime, tmp_prez) != EOF){
        Student* ps = StvoriStudenta(tmp_mbroj, tmp_ime, tmp_prez);
        if (ps != NULL) DodajStudentaUTablicu(tab, ps);
    }
    fclose(fp);

    for (int i = 0; i < VEL_TAB; i++){
       printf("\n");
       printf("Kljuc: %d", i);
       IspisiListu(tab[i]->next);
       printf("\n");

    }

    printf("\nUpisite ime i prezime studenta: ");
    scanf("%s %s", tmp_ime, tmp_prez);
  
    Student *trazeni = TraziStudentaUTablici(tab, tmp_ime, tmp_prez);
    if (trazeni != NULL){
        printf("\nMat. br. : %d", trazeni->mbroj);
    }else{
        printf("\nStudent nije pronaden.");
    }
}
