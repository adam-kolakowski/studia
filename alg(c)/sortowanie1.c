#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define MLDD 1000000000.0 //10**10


int Partition(int A[], int p, int r)
{
    int tym;
    int x=A[r];
    int i=p-1;
    for (int j=p; j<=r; j++)
        if (A[j]<=x)
    {
        i++;

       tym=A[i];
       A[i]=A[j];
       A[j]=tym;
    }
        if (i<r) return i;
        else return i-1;
}

void Quicksort (int A[], int p, int r)
{
    int q;
    if (p<r)
    {
        q=Partition(A, p,r);
        Quicksort(A,p,q);
        Quicksort(A, q+1, r);
    }
}

void stworzplik(char nazwa[], int ilosc, int sort, int drukuj_start)	//sort=0 -> niesortowane
{									//drukuj_start==1 -> drukuj liczby w pliku jakie są na starcie

    int losowa;

    srand(time(NULL));
    FILE *dane = fopen(nazwa, "w+");
    for (int i=0; i<ilosc; i++)
    {
	if (sort==0)
	{
	losowa=rand()%2000;
        fprintf(dane, "%d\n",losowa);
	if (drukuj_start==1)
	printf("%i:%i\n",i+1,losowa);	
	}
    	else
	{
	fprintf(dane, "%d\n",i);
	if (drukuj_start==1)
	printf("%i:%i\n",i+1,i);	
	}
    }
    fclose(dane);
}

void usunplik(char nazwa[])
{
    remove(nazwa);
}

void zapis (int tab[], char *nazwa_pliku, int wiersze)
{
FILE *dane2 = fopen(nazwa_pliku, "w+");
for (int i=0; i<wiersze; i++) fprintf(dane2, "%d\n", tab[i]);
fclose(dane2);
}

double czas(char nazwapliku[], int ilosc_wierszy)
{
FILE *dane = fopen(nazwapliku, "r+");

int tab[ilosc_wierszy];
struct timespec tp0, tp1;
double Tn,Fn,x;
int i=0;

for (int i=0; i<ilosc_wierszy;i++) fscanf(dane, "%d", &tab[i]);
clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    Quicksort(tab,0, ilosc_wierszy-1);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);

    Tn=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
fclose(dane);
zapis(tab,nazwapliku, ilosc_wierszy);
return Tn;
}
int main()
{
double czas100losowe=0;
double czas500losowe=0;
double czas1000losowe=0;
double czas2500losowe=0;
double czas100posortowane=0;
double czas500posortowane=0;
double czas1000posortowane=0;
double czas2500posortowane=0;

for (int i=0; i<100; i++){
 stworzplik("test3.txt",100,0,1);
 czas100losowe+=czas("test3.txt",100);
 //usunplik("test3.txt");
}
czas100losowe=czas100losowe/100;

printf("100 losowe done\n");

for (int i=0; i<500; i++){
 stworzplik("test2.txt",500,0,0);
 czas500losowe+=czas("test2.txt",500);
 usunplik("test2.txt");
}
czas500losowe=czas500losowe/500;

printf("500 losowe done\n");

for (int i=0; i<1000; i++){
 stworzplik("test2.txt",1000,0,0);
 czas1000losowe+=czas("test2.txt",1000);
 usunplik("test2.txt");
}
czas1000losowe=czas1000losowe/1000;

printf("1000 losowe done\n");

for (int i=0; i<2500; i++){
 stworzplik("test2.txt",2500,0,0);
 czas2500losowe+=czas("test2.txt",2500);
 usunplik("test2.txt");
}
czas2500losowe=czas2500losowe/2500;

printf("2500 losowe done\n");
//-----------------------POSORTOWANE


 stworzplik("posortowane1.txt",100,1,0);
 czas100posortowane+=czas("posortowane1.txt",100);
// usunplik("posortowane1.txt");

printf("100 sort done\n");
 stworzplik("posortowane500.txt",500,1,0);
 czas500posortowane+=czas("posortowane500.txt",500);
 //usunplik("test2.txt");


printf("500 sort done\n");
 stworzplik("posortowane1000.txt",1000,1,0);
 czas1000posortowane+=czas("posortowane1000.txt",1000);
 //usunplik("test2.txt");


printf("1000 sort done\n");
 stworzplik("posortowane2500.txt",2500,1,0);
 czas2500posortowane+=czas("posortowane2500.txt",2500);
// usunplik("test2.txt");


printf("Losowe:\n100: %lf\n500: %lf\n1000: %lf\n2500:%lf\n",czas100losowe,czas500losowe,czas1000losowe,czas2500losowe);

printf("Posortowane:\n100: %lf\n500: %lf\n1000: %lf\n2500:%lf\n",czas100posortowane,czas500posortowane,czas1000posortowane,czas2500posortowane);
return 0;
}
