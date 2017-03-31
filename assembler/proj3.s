//       {m                              dla n=0
//f(n,m)={1                              dla n=1
//       {0                              dla n=2  
//       {f(n-1,m)+2*f(n-2,m)-f(n-3,m)   w pozostałych przypadkach


.intel_syntax noprefix


.globl main
.text

main:

  mov eax,10 
  mov ebx,4 

  xor ecx,ecx
  xor edx,edx


  push eax
  call f 
	add esp, 4



  push ecx
	push offset msg
	call printf
  add esp,8



  ret
  mov eax,0
	ret



f:
mov ecx,0          

push ebp	        
mov ebp, esp	
push eax
push ebx
push edx


mov eax, [ebp+8]



cmp ebx,0
jne a1
mov ecx,eax
jmp koniec
a1:




cmp ebx,1
jne a2
mov ecx,1
jmp koniec
a2:



cmp ebx,2
jne a3
mov ecx,0
jmp koniec
a3:


push ebx			
sub ebx,1           
push ecx           

push eax
call f
add esp, 4

pop edx				
add ecx,edx			
pop ebx				


         
push ebx            
sub ebx,2           
push ecx            

push eax
call f
add esp, 4

pop edx				
add ecx,ecx         
add ecx,edx         
pop ebx             



push ebx            
sub ebx,3           
push ecx            

push eax
call f
add esp, 4

pop edx             
sub edx,ecx         
mov ecx,edx         
pop ebx            


koniec:

pop edx
pop ebx
pop eax
pop ebp
ret



	.data
msg:	.asciz "Wynik:%d\n"

	.byte 0
