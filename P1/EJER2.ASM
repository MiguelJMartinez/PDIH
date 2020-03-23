pila segment stack 'stack'
	dw 100h dup (?)
pila ends
datos segment 'data'
datos ends
codigo segment 'code'
	assume cs:codigo, ds:datos, ss:pila
	main PROC
		mov ax,datos
		mov ds,ax

		mov al,4
		mov ah,0
		int 10h

		mov cx,20
		mov dx,20
		mov al,3
		mov ah,0Ch
		bucle:
					int 10h
					inc cx
					cmp cx,290
					jl bucle

		bucle2:
					int 10h
					inc dx
					cmp dx,180
					jl bucle2


		mov cx,20
		mov dx,20

		bucle3:
					int 10h
					inc dx
					cmp dx,180
					jl bucle3

		bucle4:
				 int 10h
				 inc cx
				 cmp cx,290
				 jl bucle4

		mov cx,100
		mov dx,100
		mov al,2
		mov ah,0Ch
		int 10h

		mov cx,200
		mov dx,150
		mov al,1
		mov ah,0Ch
		int 10h

		mov cx,220
		mov dx,50
		mov al,5
		mov ah,0Ch
		int 10h

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
