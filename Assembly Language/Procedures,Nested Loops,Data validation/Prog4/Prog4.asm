TITLE Program4     (Prog4.asm)

; Name: Yuhang	Chen
; Email: chenyuha@oregonstate.edu
; Course / Project ID: CS271(10am class)
; Assignment number:4
; Due Date:	2/18/2018
; Description: Write a program to calculate composite numbers and then print them according to user input. [1,400] 

INCLUDE Irvine32.inc

; (insert constant definitions here)

upper	equ		4000
lower	equ		1
.data

; (insert variable definitions here)
programmer	byte	"Composite Number by Tony Chen",0
requirement	byte	"Enter the number of composite numbers you would like to see.",0
question	byte	"Enter number[1,4000](I did extra credit 2, so i allow user input at most 4000): ",0
wrong		byte	"Wrong Input,please type the number again",0
bye			byte	"Results certified by Tony. Goodbye.",0
space		byte	"	",0
key			byte	"Press any key to continue",0
ec1			byte	"*****EC1:Align the output columns",0
ec2			byte	"*****EC2:Display more composites, but show them one page at a time.  The user can ¡°Press any key to continue ¡­¡± to view the next page.",0

n			dword	0
number		dword	4	;composite number
divide		dword	2	;divide number
count		dword	0

.code
main PROC
	call	introduction	
	call	getdata
	call	crlf
	mov		edx,offset ec1
	call	writestring
	call	crlf
	call	show
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
	ret

introduction	endp

;2.getUserData
getdata			proc
	mov		edx,offset question		;ask question
	call	writestring
	call	readint
	call	validate				;validate the number between 1 to 4000
	ret

getdata			endp

;3.validate
validate		proc
top:
	cmp		eax,upper				;n should smaller than 4000
	ja		wronginput
	cmp		eax,lower					;n should bigger than 1
	jb		wronginput
	jmp		continue
wronginput:
	mov		edx,offset wrong
	call	writestring
	call	crlf
	call	getdata					;if user input wrong number,print the message and get the data again
	jmp		top						;after get the new data, jump back to top to validate again
continue:
	mov		n,eax					;set n=user input
	ret								;return to finish the procedure

validate		endp

;4.showComposites
show			proc
goon:
	call	is
	mov		eax,count
	mov		ebx,n
	cmp		eax,ebx
	je		finish					;if the count=n,stop showing composite numbers
	call	checkpage				;check if goto next page
	mov		eax,number
	add		eax,1
	mov		number,eax
	jmp		goon
finish:
	ret
show		endp

;5.isComposit
is				proc
	mov		eax,number
	mov		ebx,2
	cdq
	div		ebx						;let eax/ebx,which is number/2
	mov		ecx,eax					;set ecx=number/2
loop2:
	mov		eax,number
	cdq							
	div		ebx						;let number/divide number
	cmp		edx,0					;check if remainder is 0
	je		yes						;if it is 0,quiz this procedure
	add		ebx,1					;if it is not 0, divide number++
	loop	loop2
	jmp		no
yes:
	mov		eax,number
	call	writedec
	mov		edx,offset space		;if it is a composite number,print number and space
	call	writestring
	mov		ebx,count
	add		ebx,1
	mov		count,ebx				;count++
	mov		eax,count
	cdq
	mov		ebx,10
	div		ebx
	cmp		edx,0
	jne		over2
	call	crlf
over2:
	ret
no:
	ret
is				endp


;6.farewell
farewell		proc
	call	crlf
	mov		edx,offset bye
	call	writestring
	call	crlf
	ret

farewell		endp

;7.checkpage
checkpage	proc
	mov		eax,count
	cdq
	mov		ebx,200					;we only show 200 numbers per page
	div		ebx
	cmp		edx,0
	je		presskey
	ret
presskey:
	call	crlf
	mov		edx,offset ec2			;ec2
	call	writestring
	call	crlf
	call	crlf
	mov		edx,offset key
	call	writestring
	call	readchar				;press any key to continue
	call	crlf
	ret
checkpage	endp

END main