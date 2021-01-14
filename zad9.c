#include <stdio.h>
#include <stdlib.h>

typedef struct _cvor Cvor;
typedef Cvor *Stablo;
struct _cvor
{
    int el;
    Stablo L;
    Stablo D;
};

Stablo StvoriStablo(int);
Stablo Unos(Stablo, int);
int Ispis(Stablo);
Stablo Trazi(Stablo, int);
Stablo Brisi(Stablo, int);
Stablo TraziMin(Stablo);
Stablo TraziMax(Stablo);

int main()
{
    Stablo root = NULL;
    root = Unos(root, 3);
    root = Unos(root, 1);
    root = Unos(root, 46);
    root = Unos(root, 7); 
    root = Unos(root, 4);
    root = Unos(root, 26); 
    Ispis(root); 
    printf("\n");
    root = Brisi(root, 7);
    root = Brisi(root, 1);
    root = Brisi(root, 26);
    Ispis(root);
}

Stablo StvoriStablo(int el)
{
    Stablo s = malloc(sizeof(Cvor));
    if (s == NULL)
        return NULL;
    s->el = el;
    s->L = NULL;
    s->D = NULL;
    return s;
}

Stablo Unos(Stablo s, int el)
{
    if (s == NULL)
        s = StvoriStablo(el);
    else
    {
        if (el > s->el)
            s->D = Unos(s->D, el);
        if (el < s->el)
            s->L = Unos(s->L, el);
    }
    return s;
}

int Ispis(Stablo s)
{
    if (s == NULL)
        return 0;
    Ispis(s->L);
    printf("%d ", s->el);
    Ispis(s->D);
}

Stablo Trazi(Stablo s, int el)
{
    if (s == NULL)
    {
        return NULL;
    }
    if (el < s->el)
    {
        return Trazi(s->L, el);
    }
    if (el > s->el)
    {
        return Trazi(s->D, el);
    }
    return s;
}

Stablo Brisi(Stablo s, int el)
{
    Stablo tmp;
    if(s == NULL){
	return NULL;
    }
    if (el > s->el) s->D = Brisi(s->D, el);
    else if (el < s->el) s->L = Brisi(s->L, el);
    else{ 
    	if (s->L == NULL && s->D == NULL){
	   free(s);
	   return NULL;
    	}
	else if (s->L != NULL && s->D != NULL){
	   tmp = TraziMin(s->D);
	   s->el = tmp->el;
	   s->D = Brisi(s->D, s->el);
	}
	else if (s->L != NULL){
	   tmp = s;
           s = s->L;
	   free(tmp);	   
	}
	else if (s->D != NULL){
	   tmp = s;
	   s = s->D;
           free(tmp); 
	}
    }
    return s;
}

Stablo TraziMax(Stablo s)
{
    if (s == NULL)
        return NULL;
    while(s->D != NULL){
	s = s->D;
    }
    return s;
}

Stablo TraziMin(Stablo s)
{
    if (s == NULL)
        return NULL;
    while(s->L != NULL){
	s = s->L;
    }
    return s;
}
