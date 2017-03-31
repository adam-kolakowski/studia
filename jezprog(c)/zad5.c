#include<stdio.h>

int main() {
  int  n1, n2, n, i1, i2, i;
  printf("\nDlugosc pierwszego ciagu niemalejacego: "); scanf("%i", &n1);
  double  ciag1[n1];
  printf("wyrazy pierwszego ciagu:\n  "); 
  for (i1=0; i1<n1; i1=i1+1)  scanf("%lf", &ciag1[i1]);
  printf("\nDlugosc drugiego ciagu niemalejacego: "); scanf("%i", &n2);
  double  ciag2[n2];
  printf("wyrazy drugiego ciagu:\n  "); 
  for (i2=0; i2<n2; i2=i2+1)  scanf("%lf", &ciag2[i2]);

  n = n1+n2;  i1=0; i2=0; i=0;
  double  ciag[n];
  while (i1<n1 && i2<n2) {
    if (ciag1[i1] < ciag2[i2]) {
      ciag[i] = ciag1[i1]; i1=i1+1;
    }
    else {
      ciag[i] = ciag2[i2]; i2=i2+1;
    }
    i=i+1;
  }
  
  
  while (i1<n1)  { ciag[i] = ciag1[i1]; i1=i1+1; i=i+1; }

  while (i2<n2)  { ciag[i] = ciag2[i2]; i2=i2+1; i=i+1; }

  printf("\nCiag scalony:\n");
  for (i=0; i<n; i=i+1)  printf("  %lf", ciag[i]);
  printf("\n\n");

  return 0;
}
