#include<stdio.h>
   #include<string.h>
   #include<stdlib.h>
   
   #define MAX_DLUG 30
   #define ILOSC 100
   #define WLK_ALFABETU 26
   
   char  slowa[ILOSC][MAX_DLUG];
   char testowe[100]="informatyka";
   
   void  inicjalizacja (char  slowa[ILOSC][MAX_DLUG]) {
     int  i, j, k;
     for (i=0; i<ILOSC; i++) {
       k = rand()%(MAX_DLUG-1);
       for (j=0; j<=k; j++)
         slowa[i][j] = (char)((int)'a' + rand()%WLK_ALFABETU);
       slowa[i][k+1] = '\0';
     }
   }
 
 void szyfrowanie (char tablica[ILOSC][MAX_DLUG]){
	int i, j;
	 for (i=0;i<MAX_DLUG;i++)
	 {
		for (j=0;j<ILOSC;j++)
		{
			if(((int)(tablica[j][i]))>96&&((int)(tablica[j][i])<121))
			tablica[j][i] = (char)((int)tablica[j][i] + 2);
			if (tablica[j][i]=='y') tablica[j][i]='a';
			if (tablica[j][i]=='z') tablica[j][i]='b';
		}
		
	}
	
	
}
	 //printf("AAAAAAAAA %c",tablica[0][0]);};      //wiersz | kolumna
int main () {
     int i;
     inicjalizacja(slowa);
     szyfrowanie(slowa);
     printf("\n  WYNIK SZYFROWANIA:\n\n");
     for (i=0; i<ILOSC; i++)
       printf("  %s\n", slowa[i]);
     printf("\n");
  
    // printf("AAAAAAAAA %s",slowa[99]);
     return 0;
   }
