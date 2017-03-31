#include <stdio.h>
#include <stdlib.h>

typedef struct wezel
{
char* slowo;
struct wezel * next;
struct wezel * prev;
} wezel;



typedef struct lista
{
int wielkosc;
wezel * first;
} lista;


void Lista_init(lista* list)
{
list->wielkosc=0;
list->first=NULL;
}


int wstaw(lista* list, char* slowo)
{
wezel* tmp = list->first;
wezel* New = NULL;
New=(wezel*)malloc(sizeof(wezel));

New->slowo=slowo;
New->prev=NULL;
New->next=tmp;
if(tmp) tmp->prev=New;
list->first=New;


}

void drukuj(lista* list)
{
wezel* tmp = list->first;
while(tmp){
printf("%s | ",tmp->slowo);
tmp=tmp->next;
}
}

wezel* Szukaj(char* s, lista* list)
{
wezel* tmp=list->first;
wezel* szukany=NULL;
while(tmp)
	{
		if (tmp->slowo==s) return tmp;
		tmp=tmp->next;
	}
return NULL;
}


int usun(char* s, lista* list)
{
	wezel* tmp=Szukaj(s,list);
	if(tmp)
	{	
		if(!(tmp->next))
		{
			tmp->prev->next=NULL;
			free(tmp);	
			return 0;
		}
		
		if(!(tmp->prev))
		{
			list->first=tmp->next;
			tmp->next->prev=NULL;
			free(tmp);
			return 0;		
		}
		tmp->prev->next=tmp->next;
		tmp->next->prev=tmp->prev;
		free(tmp);
		return 0;
	}
}


int kasuj(lista* list)
{
wezel* tmp=list->first;
wezel* tmp2;
while(tmp)
{
	tmp2=tmp;
	tmp=tmp->next;
	free(tmp2);
}
list->first=NULL;
return 0;
}


lista* bezpowtorzen(lista* list)
{
	wezel* tmp=list->first;
	lista* lista2;
	lista2=(lista*)malloc(sizeof(lista*));
	
	Lista_init(lista2);
	while(tmp)
	{
		if(!(Szukaj(tmp->slowo,lista2))) wstaw(lista2,tmp->slowo);
		tmp=tmp->next;	
	}
	return lista2;
}



lista* scal(lista* list1, lista* list2)
{
  	lista* listapom;
	listapom=(lista*)malloc(sizeof(lista*));
	wezel* tmp=list1->first;
	wezel* tmp2=list2->first;

	Lista_init(listapom);	
	while(tmp)
	{
			wstaw(listapom, tmp->slowo);
			tmp=tmp->next;	
	}

	while(tmp2)
	{
			wstaw(listapom, tmp2->slowo);
			tmp2=tmp2->next;
	}

kasuj(list1);
kasuj(list2);
	return bezpowtorzen(listapom);
}





int main()
{
lista Lista12;
lista Lista1;
Lista_init(&Lista1);
Lista_init(&Lista12);
wstaw(&Lista1, "RCE");
wstaw(&Lista1,"BCD");
wstaw(&Lista1,"CDE");
wstaw(&Lista1,"DEF");
wstaw(&Lista1,"EFG");
wstaw(&Lista1,"HGDFL");
wstaw(&Lista1,"FGH");
wstaw(&Lista12,"BCD");
wstaw(&Lista12,"6");
wstaw(&Lista12,"7");
wstaw(&Lista12,"8");
wstaw(&Lista12,"9");
wstaw(&Lista12,"10");
//usun("3",&Lista1);
//kasuj(&Lista1);
system("clear");
printf("\nLista 1:\n");
drukuj(&Lista1);
printf("\n\n");

printf("Lista 12:\n");
drukuj(&Lista12);
printf("\n\n");
//bezpowtorzen(&Lista1);

printf("Po dzialaniu funkcji scal(Lista1, Lista12):\n");
drukuj(scal(&Lista1,&Lista12));
printf("\n");
drukuj(&Lista12);
return 0;
}
