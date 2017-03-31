// ebx-dl. obecnego; ecx - pozycja; edx-dl najdluzszego
#include <stdio.h>

int main()
{
int x, x2;
printf("Liczba: ");
scanf("%d",&x);
asm volatile
(
".intel_syntax noprefix;"
"mov eax,%0;"
"xor ebx,ebx;"
"xor ecx,ecx;"  
"xor edx,edx;"

"start:"
"shl eax;"   
"jnc a0;"
"inc ebx;"          
"cmp ebx, edx;"       
"jg a2;"
"jmp liczenie;"

"a0:"
"xor ebx,ebx;"
"jmp liczenie;"

"a2:"
"inc edx;"

"liczenie:"
"cmp ecx,31;"
"jz koniec;"
"inc ecx;"
"jmp start;"

"koniec:"
"mov %0,edx;"
".att_syntax prefix;"
:"=r" (x2)
:"r" (x)
:"eax","ebx","ecx","edx"
);
printf("\nSprawdzona liczba = %d\nMaksymalna liczba jedynek obok: %d\n",x,x2);
return 0;

}