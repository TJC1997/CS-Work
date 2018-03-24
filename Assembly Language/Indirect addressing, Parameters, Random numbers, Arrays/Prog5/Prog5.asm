TITLE Program5    (Prog5.asm)

; Name: Yuhang	Chen
; Email: chenyuha@oregonstate.edu
; Course / Project ID: CS271(10am class)
; Assignment number:5
; Due Date:	3/4/2018
; Description: Write a program to generate random numbers and sort them in descending order
INCLUDE Irvine32.inc

; (insert constant definitions here)

upper	equ		200			;upper is max
lower	equ		10			;lower is min
lo		equ		100
hi		equ		999

.data

; (insert variable definitions here)
programmer	byte	"Sorting Random Integers by Tony Chen",0
requirement	byte	"This program generates random numbers in the range [100 .. 999],displays the original list, sorts the list, and calculates the median value. Finally, it displays the list sorted in descending order.",0
question	byte	"How many numbers should be generated?[10,200] ",0
wrong		byte	"Invalid input,please type the number again",0
bye			byte	"Results certified by Tony. Goodbye.",0
titl1		byte	"The unsorted random numbers: ",0
titl2		byte	"The sorted random numbers: ",0
titl3		byte	"The median is ",0
space		byte	"	",0

n			dword	0
list		dword	200	dup(?)
four		dword	4
range		dword	?
count		dword	0
i			dword	0
k			dword	0
j			dword	0
re			dword	0
temp1		dword	0
temp2		dword	0

.code
main PROC
	call randomize
	call	introduction	
	push	offset n						;pass by reference
	call	getdata
	
	push	n								;pass by value
	push	offset list						;pass by reference
	call	fill


	push	offset titl1				
	push	n								;pass by value
	push	offset list						;pass by reference
	call	display
	call	crlf

	push	n
	push	offset	list
	call	sort

	push	n
	push	offset	list
	call	median

	mov		eax,0
	mov		count,eax						;set count=0
	push	offset titl2				
	push	n								;pass by value
	push	offset list						;pass by reference
	call	display
	call	crlf

	call	farewell

	exit									; exit to operating system
main ENDP

;1.introduction
introduction	proc
	mov		edx,offset programmer
	call	writestring
	call	crlf
	mov		edx,offset requirement
	call	writestring
	call	crlf
	call	crlf
	ret

introduction	endp

;2.getUserData
getdata			proc
	push	ebp							;save old ebp
	mov		ebp,esp						;let ebp point to esp
top:
	mov		edx,offset question			;ask question
	call	writestring
	call	readint
	cmp		eax,upper					;check if userinput valid
	ja		wronginput
	cmp		eax,lower
	jb		wronginput

	;mov	[ebp+8],eax why i cannot do that?
	mov		ebx,[ebp+8]
	mov		[ebx],eax					;let n=user input
	mov		eax,n
	pop		ebp
	ret		4							;pop dword n

wronginput:
	mov		edx,offset wrong			;print invalid message
	call	writestring
	call	crlf
	jmp		top
getdata			endp

;3.fillarray
fill			proc
	push	ebp
	mov		ebp,esp
	mov		ecx,[ebp+12]				;ecx=n
	mov		esi,[ebp+8]					;edi points to list

	mov		eax,hi					;range=high-low+1
	inc		eax
	mov		ebx,lo
	sub		eax,ebx
	mov		range,eax					;range=eax
more:
	mov		eax,range
	call	randomrange					;generate random number [0,899]
	add		eax,lo						;add low to make it	to	[100,999]
	mov		[esi],eax
	add		esi,4
	loop	more
	
	pop		ebp
	ret		8
fill			endp

;4.sortarray
sort			proc
	push	ebp
	mov		ebp,esp
	mov		edi,[ebp+8]					;edi point to array
	mov		esi,[ebp+8]					;esi point to array
	mov		ebx,[ebp+12]				;ebx=n
	mov		ecx,ebx
	sub		ecx,1						;ecx=n-1
	mov		re,ecx						;re=n-1
	mov		ebx,k
loop1:
	mov		edx,re						;ebx=n-1
	cmp		ebx,edx
	jae		over1						;jmp to over one if k>=n-1
	mov		eax,k
	mov		i,eax						;i=k
	mov		eax,k
	add		eax,1
	mov		j,eax						;j=k+1
loop2:
	mov		edx,n						;n is request
	cmp		eax,edx						;check if j<request
	jae		over2
	mul		four						;eax*4=j*4
	add		edi,eax						;edi+j*4
	mov		ebx,[edi]					;ebx=list[j]
	sub		edi,eax						;go back to list[0]
	mov		eax,i						
	mul		four
	add		edi,eax						;edi=edi+i*4
	mov		edx,[edi]					;edx=list[i]
	sub		edi,eax						;go back to list[0]
	cmp		ebx,edx						
	jbe		smaller						;check if list[j]>list[i]
	mov		eax,j						;set i=j
	mov		i,eax
smaller:
	mov		eax,j
	add		eax,1
	mov		j,eax						;j++
	jmp		loop2
over2:
	mov		eax,k					
	mul		four
	add		edi,eax						;edi=edi+k*4
	mov		edx,[edi]					;edx=list[k]
	mov		temp1,edx					;temp1=list[k]
	
	mov		eax,i
	mul		four
	add		esi,eax						;esi=esi+i*4
	mov		edx,[esi]					;edx=list[i]
	mov		temp2,edx					;temp2=list[i]

	mov		ecx,temp2
	mov		[edi],ecx
	mov		ecx,temp1
	mov		[esi],ecx					;switch

	mov		eax,k						;both go back to list[0]
	mul		four
	sub		edi,eax
	mov		eax,i					
	mul		four
	sub		esi,eax

	mov		ebx,k
	add		ebx,1
	mov		k,ebx						;k++
	jmp		loop1
over1:
	pop		ebp
	ret		8
sort		endp

;median
median			proc
	mov		edx,offset titl3
	call	writestring

	push	ebp
	mov		ebp,esp
	mov		edi,[ebp+8]					;edi points to list
	mov		eax,[ebp+12]				;eax is n

	xor		edx,edx
	mov		ecx,2
	div		ecx							;eax/2

	cmp		edx,1						;check if it is odd
	je		odd							

	mul		four
	add		edi,eax
	mov		ebx,[edi]
	sub		edi,4
	mov		eax,[edi]
	add		eax,ebx
	xor		edx,edx
	mov		ecx,2
	div		ecx							;eax/2
	call	writedec
	jmp		over
odd:
	mul		four
	add		edi,eax
	mov		eax,[edi]
	call	writedec
over:
	pop		ebp
	ret		8
median			endp
	
;6.display
display			proc
	push	ebp
	mov		ebp,esp
	mov		ecx,[ebp+12]				;ecx=n
	call	crlf
	mov		edi,[ebp+8]					;edi=list
	mov		edx,[ebp+16]				;edx=title
	call	writestring
	call	crlf
more:
	mov		eax,[edi]
	call	writedec
	mov		edx,offset	space
	call	writestring
	mov		ebx,count
	add		ebx,1
	mov		count,ebx					;count++
	cmp		ebx,10
	je		line						;if count hits 10,change to next line
back:
	add		edi,4
	loop	more
	pop		ebp
	ret		12
line:
	call	crlf
	mov		ebx,0						;reset count to 0
	mov		count,ebx
	jmp		back						;jump back to the loop
display			endp

;6.farewell
farewell		proc
	call	crlf
	mov		edx,offset bye
	call	writestring
	call	crlf
	ret

farewell		endp

END main