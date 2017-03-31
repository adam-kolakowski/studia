#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#define MLDD 1000000000.0 //10**10
char **tab1;
char **tabsort;
int najdluzsze;




void usunplik(char nazwa[])
{
    remove(nazwa);
}

void stworzplik2(char nazwa[], char tekst[])	
{

	static int i=1;

    FILE *dane2 = fopen(nazwa, "a");

	fprintf(dane2,"%s\n",tekst);
		i++;

	fclose(dane2);
}



void stworzplik(char nazwa[])	
{									
	int ii=1;
	char symbol[30];
    char strumien[3000000];
    char add_name[]="bez_cyfr_";

	FILE *in = fopen(nazwa, "r");

	while (fscanf(in, "%s", symbol) != EOF) 
	{
	    fgets(symbol, 30, in);
	    symbol[1]=tolower(symbol[1]);
	    strcat(strumien,symbol+1);
	}

    fclose(in);
    strcat(add_name,nazwa);
    usunplik(add_name);
	stworzplik2(add_name,strumien);    

}


void clear_pl(char *name)
{
	char nana1[]="./";
	FILE *plik=fopen("delete","w+");

	fprintf(plik,"#!/bin/bash\n \
		sed 's/ą/a/g' \"$@\" -i\n \
		sed 's/ę/e/g' \"$@\" -i\n \
		sed 's/ż/z/g' \"$@\" -i\n \
		sed 's/ź/z/g' \"$@\" -i\n \
		sed 's/ł/l/g' \"$@\" -i\n \
		sed 's/ó/o/g' \"$@\" -i\n \
		sed 's/ą/a/g' \"$@\" -i\n \
		sed 's/ś/s/g' \"$@\" -i\n \
		sed 's/ć/c/g' \"$@\" -i\n \
		sed 's/ń/n/g' \"$@\" -i\n \
		sed 's/ö/o/g' \"$@\" -i\n \
		sed 's/ü/u/g' \"$@\" -i\n \
		sed 's/Ą/A/g' \"$@\" -i\n \
		sed 's/Ę/E/g' \"$@\" -i\n \
		sed 's/Ż/Z/g' \"$@\" -i\n \
		sed 's/Ź/Z/g' \"$@\" -i\n \
		sed 's/Ł/L/g' \"$@\" -i\n \
		sed 's/Ó/O/g' \"$@\" -i\n \
		sed 's/Ą/A/g' \"$@\" -i\n \
		sed 's/Ś/S/g' \"$@\" -i\n \
		sed 's/Ć/C/g' \"$@\" -i\n \
		sed 's/Ń/N/g' \"$@\" -i\n");

	fclose(plik);
	system("chmod 777 ./delete");

system("./delete nazwiska.txt");
usunplik("delete");
}





void zapis (char *nazwa_pliku, int wiersze)
{
	FILE *dane2 = fopen(nazwa_pliku, "w+");

	for (int i=0; i<wiersze; i++) 
		fprintf(dane2, "%s\n", tabsort[i]);

	fclose(dane2);
}




int ilelini(char *nazwapliku)
{
	char smiec[30];
	int i=0;

	FILE *plik1 = fopen(nazwapliku,"r");

	while (fscanf(plik1,"%s",smiec)!=EOF) 
		i++;

	fclose(plik1);
	return i; 
}





void wczytaj(char *plikzr, int ilosclinijek)
{
	int i = 0;
	char tmp[30];
	int len;

	tab1=malloc(sizeof(*tab1)*ilosclinijek);
	tabsort=malloc(sizeof(*tabsort)*ilosclinijek);

		FILE *plik2 = fopen(plikzr,"r");

			for (int i=0; i<ilosclinijek;i++)
			{
				fscanf(plik2,"%s",tmp);
				len=strlen(tmp);
				if(len>najdluzsze) najdluzsze=len;
				tab1[i]=(char*)malloc(sizeof(char)*len);
				tabsort[i]=(char*)malloc(sizeof(char)*len);
				strcpy(tab1[i],tmp);
				strcpy(tabsort[i],tmp);

			}

		fclose(plik2);
}





void csort(int ilelinij, int p)
{
	int total, oldCount;
	int tabpom[123];
		for (int i=0; i<123; i++) tabpom[i]=0;

			for (int i=0; i<ilelinij; i++)
			{

				tabpom[(int)tab1[i][p]]++;
			}

			for (int i=1; i<123; i++) tabpom[i]=tabpom[i]+tabpom[i-1];

				for(int i=ilelinij-1;i>=0; i--)
				{
					tabsort[tabpom[tab1[i][p]]-1]=tab1[i];
					tabpom[tab1[i][p]]--;
				}
}



void rsort(char *nazwapliku)
{
	for(int i=najdluzsze-1;i>=0;i--) 
	{
		csort(ilelini(nazwapliku), i);
		memcpy(tab1, tabsort, sizeof(*tab1) * ilelini(nazwapliku));
	}
}


//QUICKSORT


int Partition(int p, int r)
{
    char tym[30];
    char x[30];

    for (int i=0;i<30;i++) 
    {
    	tym[i]=0;
    	x[i]=0;
    }

    strcpy(x,tabsort[r]);
    int i=p-1;
    for (int j=p; j<=r; j++)
        if (strcmp(tabsort[j],x)<=0)
    {
        i++;

       //tym=tabsort[i];
       strcpy(tym, tabsort[i]);
       //tabsort[i]=tabsort[j];
       strcpy(tabsort[i],tabsort[j]);
       //tabsort[j]=tym;
       strcpy(tabsort[j],tym);
    }
        if (i<r) return i;
        else return i-1;
}

void Quicksort (int p, int r)
{
    int q;
    if (p<r)
    {
        q=Partition(p,r);
        Quicksort(p,q);
        Quicksort(q+1, r);
    }
}


//QUICKSORT




void main()
{
	struct timespec tp0, tp1, tp3, tp4;
	double Tn,Fn,x, Tn2;
	char zrodlo[]="nazwiska.txt";
	char zrodlo2[]="bez_cyfr_nazwiska.txt";
	clear_pl(zrodlo2);
	stworzplik(zrodlo);

	
	int ilosclini=ilelini(zrodlo2);
	wczytaj(zrodlo2,ilosclini);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp0);
    	Quicksort(0, ilosclini-1);
    	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp1);


    	Tn=(tp1.tv_sec+tp1.tv_nsec/MLDD)-(tp0.tv_sec+tp0.tv_nsec/MLDD);
	zapis("SortedByQuicksort.txt",ilosclini);
 	//printf("Quicksort: %lf",Tn);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp3);
    	rsort(zrodlo2);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID,&tp4);

	
	Tn2=(tp4.tv_sec+tp4.tv_nsec/MLDD)-(tp3.tv_sec+tp3.tv_nsec/MLDD);
	zapis("SortedByRSORT.txt",ilosclini);
 	//printf("\nRSort:: %lf",Tn2);
 	usunplik("bez_cyfr_nazwiska.txt");

printf("\n\n---------------------\n|QuickSort|  RSort  |\n---------------------\n|%9lf|%9lf|\n---------------------\n\nQuickSort jest %lfx szybszy przy %d slowach.\n\n",Tn,Tn2,(Tn2/Tn),ilosclini);

 	
}