#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int heapSize;
int rozmiar=0;
void Heapify(int A[], int i)
{
    int l, r, largest;
    l=2*i+1;
    r=2*i+2;
    if ((l<=heapSize) && (A[l]>A[i]))
     largest = l;
    else largest = i;

    if (r<= heapSize && A[r]>A[largest]) largest = r;

    if (largest!=i)
    {
        A[i]=A[i]+A[largest];
        A[largest]=A[i]-A[largest];
        A[i]=A[i]-A[largest];
        Heapify(A, largest);
    }
}

void BuildHeap(int A[])
{
    int i;
    heapSize=rozmiar;
    for ( i=floor(rozmiar/2); i>=0;i--) Heapify(A,i);

}


void HeapSort(int A[])
{
    BuildHeap(A);
    int i;
    for (i=heapSize; i>=1; i--)
    {
        A[heapSize]=A[heapSize]+A[0];
        A[0]=A[heapSize]-A[0];
        A[heapSize]=A[heapSize]-A[0];
        heapSize--;
        Heapify(A,0);
    }
}

int czytanie(int tab[])
{
    int i=0;
    FILE * dane = fopen("liczby.txt", "r");
    if (dane == NULL)
    {
        printf("Nie ma liczby.txt\n");
        return 0;
    }
    while(fscanf(dane,"%d",&tab[i])==1) i++;
    fclose(dane);
    return i-1;
}


void zapis(int tab[])
{
    int i;
    FILE * dane = fopen("wynik.txt", "w+");
    for(i=0;i<=rozmiar;i++)
    {
        fprintf(dane,"%d\n",tab[i]);
    }
    printf("\nWynik znajduje sie w wynik.txt\n");
    fclose(dane);
}
int main()
{
    int i;
    int tab[100];
    rozmiar=czytanie(tab);
    heapSize=rozmiar;
    printf("Plik liczby.txt (%d cyfr):\n",rozmiar+1);

    for(i=0;i<rozmiar+1;i++)  printf("%d ",tab[i]);
    printf("\n");

    HeapSort(tab);

    printf("\nPo sortowaniu:\n");
    for(i=0;i<rozmiar+1;i++)  printf("%d ",tab[i]);

    zapis(tab);
    return 0;
}

