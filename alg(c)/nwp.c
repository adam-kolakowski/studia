#include <stdio.h>
#include <string.h>
 
int i, j, m, n, a;
int c[40][40];
char x[30], y[30], b[40][40];
 
int printuj(int i,int j)
{
    if(i==0 || j==0)
        return 0;
    if(b[i][j] == '/')
    {
        printuj(i-1,j-1);
        printf("%c",x[i-1]);
    }
    else if(b[i][j]=='|')
        printuj(i-1,j);
    else
        printuj(i,j-1);
}
 
void len()
{
    m=strlen(x);
    n=strlen(y);
    for(i = 0; i <= m; i++)
        c[i][0]=0;
    for(i = 0; i<= n; i++)
        c[0][i]=0;
    for(i = 1; i <= m; i++)
        for(j = 1; j <= n; j++)
        {
            if(x[i-1] == y[j-1])
            {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = '/';
            } 
            else if(c[i-1][j] >= c[i][j-1]) 
            {
                c[i][j] = c[i-1][j];
                b[i][j] = '|';
            } 
            else
            {
                c[i][j] = c[i][j-1];
                b[i][j] = '-';
            }
        }
    printuj(m,n);
}
  
int main(void){
    printf("Podaj 1 slowo:\n");
    scanf("%s",x);
    printf("Podaj 2 slowo:\n");
    scanf("%s",y);
    printf("NWP:\n");
len();
    printf("\n");
    return 0;
}