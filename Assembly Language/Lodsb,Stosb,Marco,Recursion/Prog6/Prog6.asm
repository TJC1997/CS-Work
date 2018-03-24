TITLE Program6    (Prog6.asm)

; Name: Yuhang	Chen
; Email: chenyuha@oregonstate.edu
; Course / Project ID: CS271(10am class)
; Assignment number:6A
; Due Date:	3/18/2018
; Description: Write a program to getstring,displaystring,readval and writeval
INCLUDE Irvine32.inc

; (insert constant definitions here)


.data

; (insert variable definitions here)
programmer	byte	"PROGRAMMING ASSIGNMENT 6A: Designing low-level I/O procedures by Tony Chen",0
requirement	byte	"Please provide 10 unsigned decimal integers.Each number needs to be small enough to fit inside a 32 bit register.After you have finished inputting the raw numbers I will display a list of the integers, their sum, and their average value.",0
question	byte	"Please enter an signed number: ",0
wrong		byte	"Invalid input,please type the number again",0
bye			byte	"Results certified by Tony. Goodbye.",0
total		byte	"The sum of these numbers is: ",0
averge		byte	"The average is: ",0
space		byte	" ",0
allnum		byte	"You enter the following numbers: ",0
subtotal	byte	"You current subtotal is: ",0
ec1			byte	"*****EC:1 point: number each line of user input and display a running subtotal of the user¡¯s numbers.",0
ec2			byte	"*****EC:2 points: Handle signed integers. ",0
ec3			byte	"*****EC:3 points: make your ReadVal and WriteVal procedures recursive. ",0

count		dword	0
address		dword	0
list		dword	10 dup(1)
check		dword	1
ori			dword   0
r			dword	0
result		sdword	0
ten			dword	10
index		dword	-1
sum			sdword	0
ave			sdword	0
sign		sdword	1
string		byte	101	dup(?)
num			byte	?
all			sdword	0
.code

;getstring macro
getstring	MACRO s
	pushad
	mov		eax,count
	add		eax,1
	call	writedec
	mov		edx,offset question
	call	writestring
	mov		edx,offset s
	mov		ecx,100					;read at most 100 letters
	call	readstring
	popad
ENDM

;displaystring marco
displaystring	MACRO s
	pushad
	mov		edx,offset s
	call	writestring
	mov		edx,offset space			;print spcae
	call	writestring
	popad
ENDM


main PROC
	call	introduction	
	mov		edi,offset list
read:
	push	offset list
	push	offset string
	call	readval
	call	crlf
	mov		edx,offset	subtotal
	call	writestring
	mov		eax,all
	mov		ebx,result
	add		eax,ebx
	mov		all,eax
	call	writeint						;print subtotal
	call	crlf
	add		edi,4
	call	crlf
	mov		eax,count
	add		eax,1
	mov		count,eax
	cmp		eax,9							;0-9,ten times 
	jbe		read
	
	mov		eax,0
	mov		count,eax						;set count=0

	mov		edx,offset	allnum
	call	writestring
	mov		esi,offset list					;esi points to the list
output:	
	mov		al,0
	mov		string,al						;clean the string
	mov		eax,[esi]						;result=list[i]
	mov		result,eax

	push	result
	push	offset string
	call	writeval
	mov		eax,count
	inc		eax
	add		esi,4
	mov		count,eax
	cmp		eax,9
	jbe		output


	call	crlf
	push	offset list
	call	calculate

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
	mov		edx,offset ec1
	call	writestring
	call	crlf
	mov		edx,offset ec2
	call	writestring
	call	crlf
	mov		edx,offset ec3
	call	writestring
	call	crlf
	call	crlf
	ret
introduction	endp

;2.readval
readval			proc
	push	ebp
	mov		ebp,esp
	pushad
inputagain:
	mov		eax,1
	mov		check,eax
	mov		eax,0
	mov		result,eax				;set result to 0
	mov		eax,[ebp+8]				;eax=string
	getstring string
	mov		esi,[ebp+8]				;esi=string
	cld
	mov		eax,-1
	mov		index,eax				;set index to -1
	
	call	convert
	mov		eax,check
	cmp		check,1
	jne		inputagain
	
	mov		eax,result
	mov		ebx,sign				;sign*result
	mul		ebx
	
	mov		result,eax				;get the final result
	mov		edx,1
	mov		sign,edx				;set sign back to 1

	mov		eax,result
	mov		[edi],eax

	popad	
	pop		ebp
	ret		8
readval			endp


;4.convert string to int
convert			proc
	mov		eax,index
	add		eax,1
	mov		index,eax
	pushad
	xor		eax,eax
	lodsb
	cmp		eax,0					;check if it is null char
	je		over
	
	mov		ebx,index
	cmp		ebx,0
	jne		skip
	cmp		eax,45
	je		negative				;check if it is negative number
skip:
	sub		eax,48					;change to 0-9
	cmp		eax,0
	jb		wronginput
	cmp		eax,9
	ja		wronginput
	mov		ebx,eax
	mov		eax,result
	mul		ten						;result*10
	add		eax,ebx					;result+s[i]
	mov		result,eax
	cmp		edx,0
	jne		wronginput
	call	convert
	jmp		over
negative:
	mov		eax,-1
	mov		sign,eax
	call	convert
	jmp		over
wronginput:
	mov		edx,offset wrong
	call	writestring
	call	crlf
	mov		eax,0
	mov		check,eax				;set check=0 if it's a bad string
	mov		eax,1
	mov		sign,eax
	popad	
	ret
over:
	popad	
	ret
convert			endp

;5.calculate
calculate		proc
	push	ebp
	mov		ebp,esp
	pushad
	mov		esi,[ebp+8]
	mov		ecx,10
again:
	mov		eax,[esi]
	mov		ebx,sum
	add		eax,ebx
	mov		sum,eax
	add		esi,4
	loop	again

	mov		edx,offset	total
	call	writestring
	mov		al,0
	mov		string,al				;clean the string
	mov		eax,sum
	mov		result,eax
	push	sum
	push	offset string
	call	writeval				;print string sum
	call	crlf
	
	cdq
	mov		ebx,10
	idiv	ebx						;eax=eax/10
	mov		result,eax
	mov		edx,offset	averge
	call	writestring
	mov		al,0
	mov		string,al
	push	result
	push	offset string	
	call	writeval				;print string averge

	popad
	pop		ebp
	ret		4
calculate		endp


;6.writeval
writeval		proc
	push	ebp
	mov		ebp,esp
	pushad
	mov		eax,[ebp+12]		;eax=result
	mov		edi,[ebp+8]			;edi points to string
	
	mov		ebx,0
	cmp		eax,ebx				;compare result and 0
	jge		positive
	mov		ebx,-1				;change result to positive
	mul		ebx
	mov		result,eax
	mov		al,45
	cld	
	stosb						;set string[0]='-'
positive:
	mov		eax,result
	mov		ori,eax				;set ori = result
	call	transform
	mov		al,0
	stosb
	displaystring string
	popad
	pop		ebp
	ret		8
writeval		endp

;7.transform
transform		proc
	cdq
	mov		eax,ori
	mov		ebx,10
	div		ebx
	mov		result,edx			;result=ori%10
	mov		ori,eax				;ori=ori/10

	cmp		eax,0
	ja		go
	mov		al,byte ptr result
	add		al,48
	stosb
	ret
go:
	push	result
	call	transform
	pop		result
	mov		al,byte ptr result
	add		al,48
	stosb
	ret
transform		endp

;6.farewell
farewell		proc
	call	crlf
	mov		edx,offset bye
	call	writestring
	call	crlf
	ret
farewell		endp
END main