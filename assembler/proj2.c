#include <stdio.h>
#include <stdlib.h>
//[ab][^r]+r
int main()
{

   //char *s="fqr  b qabxx xryc pqr";

   char *s="abr";
   int x,y;
asm volatile
(
".intel_syntax noprefix;"
"xor ebx, ebx;"
"xor edx, edx;"
"CLD;"
  "mov edi, %2;"
  "mov ebx, %2;"

"petla:"
"mov eax, 'a';"
"scasb;"
"je znalezione;"
"sub edi, 1;"
"mov eax, 'b';"
"scasb;"
"je znalezione;"

"mov eax, 0;"
"scasb;"
"je zero;"
"sub edi, 1;"

"jmp petla;"

"znalezione:"
"mov eax, 0;"
"scasb;"
"je zero;"
"sub edi, 1;"

"mov ecx, 1;"
//"add edi, 1;"
"mov eax, 'r';"
"repne scasb;"
"je petla;"
"mov edx, edi;"
"jmp dalej;"

"dalej:"
"mov eax, 0;"
"scasb;"
"je zero;"
"sub edi, 1;"

"mov eax, 'r';"
"scasb;"
"je kuniec;"



"jmp dalej;"



"kuniec:"
"sub edx, ebx;"
"sub edx, 1;"
"sub edi, ebx;"
"sub edi, edx;"
"mov eax, edi;"
"sub edx, 1;"
"inc eax;"
"jmp koniec;"

"zero:"
"mov edx, 0;"
"mov eax, 0;"

"koniec:"
"mov %0,edx;"
"mov %1, eax;"

".att_syntax prefix;"
  : "=r" (x), "=r" (y)
  : "r" (s)
  : "eax", "ebx", "ecx", "edx"

);
printf("%hd, %hd\n",x,y);
}
