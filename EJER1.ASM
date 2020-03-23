pila segment stack 'stack'
	dw 100h dup (?)
pila ends
datos segment 'data'
	msg db 'adios$'
datos ends
codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax

		mov al,1
		mov ah,0
		int 10h

		mov dx,OFFSET msg
		mov ah,9
		int 21h

		mov ah,8
		int 21h

		mov al,3
		mov ah,0
		int 10h

		mov ax,4C00h
		int 21h
	main ENDP
codigo ends

END main
