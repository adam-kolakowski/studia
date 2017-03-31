#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
 
#define MAX 99

int tab[MAX];
int zera[MAX];
int z=0;
int ile=11;
int maxp=0;





int wstaw2(int a)
{
    int i=0;

    while (tab[i]!=0)
        {
            if (a<=tab[i])
                i=(i*2)+1;
            else if (a>tab[i])
                i=(i+1)*2;
        }


    tab[i]=a;
    if (maxp<i) maxp=i;
printf("%d na %d pozycji\n",a,i);
    return 0;
}




 

int szukaj2(int a)
{
    int i=0;

    if (a==tab[0])
        return MAX+1;
    while (tab[i]!=a)
        {
        if (i<maxp){
            if (a<=tab[i])
                i=(i*2)+1;
            else if (a>tab[i])
                i=(i+1)*2;
        }
        else return 0;
        }


    return i;
   
}
 
void drukuj()
{
    int i=0;
    int temp=ile;
    int tz=z;
    int j,jest;
    int kopia[MAX];
    for(i=0;i<MAX;i++)
        kopia[i]=tab[i];
    i=0;
    printf("\n:IN ORDER:\n");
    while(temp>0)
    {
        if(kopia[i*2+1]==0)
        {
           
                if(kopia[i]==0)
                    i=(i+1)*2;
                else
                {
                    printf("%d ",kopia[i]);
                    temp--;
                    kopia[i]=0;
                    if(kopia[(i+1)*2]==0)
                        i=0;
                    else
                        i=(i+1)*2;
                }
           
        }
        else
        {
            i=i*2+1;
        }
    }
}
 


void usun(int n)
{
    int i=szukaj2(n);
    if(i!=0)
    {
        if(i==MAX+1)
            i=0;
        //if(z==0)
        {
            if(tab[(i*2)+1]==0 && tab[(i+1)*2]==0) //brak synow
            {
                tab[i]=0;
            }
            else if(tab[(i*2)+1]==0 && tab[(i+1)*2]!=0) //prawy syn tylko
            {
                tab[i]=tab[(i+1)*2];
                tab[(i+1)*2]=0;
            }
            else if(tab[(i*2)+1]!=0 && tab[(i+1)*2]==0) //lewy syn tylko
            {
                tab[i]=tab[(i*2)+1];
                tab[(i*2)+1]=0;
            }
            else //2 syny
            {
                int z;
                int j=0;
                int t=i;
                i=(i+1)*2;
                int max=i;
                while(z!=1)
                {
                    if(tab[(i*2)+1]!=0 && tab[(i+1)*2]!=0)
                        j++;
                    else if(tab[(i*2)+1]!=0 && tab[(i+1)*2]==0)
                        j++;
                    else if(tab[(i*2)+1]==0 && tab[(i+1)*2]!=0)
                        j++;
                    if(j==0)
                        z=1;
                    else
                    {
                        if(tab[(i+1)*2]>tab[(i*2)+1])
                        {
                            if(tab[max]<tab[(i+1)*2])
                                max=(i+1)*2;
                            i=(i+1)*2;
                        }
                        else
                        {
                            if(tab[max]<tab[(i*2)+1])
                            max=(i*2)+1;
                            i=(i*2)+1;
                        }
                        j--;
                    }
                }
                //printf("%d",tab[max]);
                tab[t]=tab[max];
                tab[max]=0;
            }
        }//else{}
        ile--;
        printf("Usunieto %d",n);
    }
    else
        printf("Nie znaleziono %d\n",n);
}

 
int main()
{
    int i,jest;
int dane[] = {18, 11, 6, 30 ,4 ,19, 22, 2, 23, 5, 17};
    for(i=0;i<MAX;i++)
        tab[i]=0;

    for(i=0;i<ile;i++)
    {
        wstaw2(dane[i]);
    }
    printf("\nWyszukaj:\n");
    scanf("%d",&i);
    jest=szukaj2(i);
    if(jest==0)
        printf("Nie znaleziono %d\n",i);
    else
    {
        if(jest==MAX+1)
            jest=0;
        printf("Znaleziono %d na %d pozycji",i,jest);
    }
    drukuj();
    printf("\n\nUsun:\n");
    scanf("%d",&i);
    usun(i);
    drukuj();
    return 0;
}