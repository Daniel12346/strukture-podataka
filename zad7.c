#include <stdio.h>
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
int RacunajPrefiks(char *);

int main()
{
    char *buff = NULL;
    FILE *fp = fopen("postfix.txt");
    UcitajIzDatoteke(fp, &buff);
    fclose(fp);
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
        return -1;
    q->el = el;
    q->next = p->next;
    p->next = q;
}

int Pop(Pozicija p)
{
    Pozicija tmp = p->next;
    int el = tmp->el;
    p->next = tmp->next;
    free(tmp);
    return el;
}

int UcitajIzDatoteke(FILE *fp, char **p_buff)
{

    char *tmp = NULL;
    int fsize;
    fseek(fp, 0, SEEK_END);
    fsize = ftell(fp);
    rewind(pFile);
    tmp = realloc(p_buff, fsize * sizeof(char));
    fread(*p_buff, 1, fsize, fp);
    strcpy(tmp, p_buff);
    printf("%s", p_buff);
}

int RacunajPrefiks(char *tekst)
{
    /*Pozicija stog = StvoriPoziciju();
    if (stog == NULL)
        return -1;
    int rez = 0, n = 0, broj = 0;

    while ((rez = sscanf(tekst, "%d%n", &broj, &n)) != EOF)
    {
        if (rez == 1)
        {
            Push(stog, broj);
        }
        else
        {
            //TODO:
        }
    }*/
    for (int i = 0; tekst[i] != '\0'; i++)
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
            Push(Stog(atoi(tekst[i])));

        case ('+'):
        case ('-'):
        case ('*'):
        case ('/'):
        }
    }
}
