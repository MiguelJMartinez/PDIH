#include <stdio.h>
#include <dos.h>

unsigned int c_texto=15;  //texto blanco por defecto
unsigned int c_fondo=0;   //fondo negro por defecto

void pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 8;
	int86(0x21, &inregs, &outregs);
}

void gotoxy(unsigned int x, unsigned int y){
	union REGS inregs, outregs;
	inregs.h.dh = x;
	inregs.h.dl = y;
	inregs.h.ah = 2;
	inregs.h.bh = 0;
	int86(0x10, &inregs, &outregs);
}

void setcursortype(unsigned int tipo_cursor){
	union REGS inregs, outregs;
	inregs.h.ah = 0x01;

	switch(tipo_cursor){
		case 0: //invisible
			inregs.h.ch = 010;
			inregs.h.cl = 000;
            break;
		case 1: //normal
			inregs.h.ch = 010;
			inregs.h.cl = 010;
            break;
		case 2: //grueso
			inregs.h.ch = 000;
			inregs.h.cl = 010;
            break;
	}

	int86(0x10, &inregs, &outregs);
}

void setvideomode(unsigned char modo){
	union REGS inregs, outregs;
	inregs.h.ah = 0x00;
	inregs.h.al = modo;
	int86(0x10,&inregs,&outregs);
}

unsigned int getvideomode(){
    union REGS inregs, outregs;
    inregs.h.ah = 0xF;
    int86(0x10, &inregs, &outregs);
    return outregs.h.al;
}

void textcolor(unsigned int c){
    c_texto=c;
}

void textbackground(unsigned int c){
    c_fondo=c;
}

void clrscr(){
	union REGS inregs, outregs;
	inregs.h.ah = 6;
    inregs.h.al = 0;
    inregs.h.bh = 0;
    inregs.h.ch = 0;
    inregs.h.cl = 0;
    inregs.h.dh = 100;
    inregs.h.dl = 100;
    int86(0x10, &inregs, &outregs);
}

void cputchar(unsigned char c){
	union REGS inregs, outregs;
    inregs.h.ah = 9;
	inregs.h.al = c;
	inregs.h.bl = c_fondo<<4 | c_texto;
	inregs.h.bh = 0x00;
	inregs.x.cx = 1;
	int86(0x10, &inregs, &outregs);
}

unsigned char getche(){
    union REGS inregs, outregs;
    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    return outregs.h.al;
}

void pixel(unsigned int x, unsigned int y, unsigned char c){
    union REGS inregs, outregs;
    inregs.x.cx = x;
    inregs.x.dx = y;
    inregs.h.al = c;
    inregs.h.ah = 0x0C;
    int86(0x10, &inregs, &outregs);
}

void recuadro(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned char ct, unsigned char cf) {
    union REGS inregs, outregs;
    clrscr();
    inregs.h.ah = 0x06;
    inregs.h.al = 0;
    inregs.h.ch = x1;
    inregs.h.cl = y1;
    textcolor(ct);
    textbackground(cf);
    inregs.h.bl = (c_fondo<<4) | c_texto;  //bh
    inregs.h.dh = x2;
    inregs.h.dl = y2;
    int86(0x10, &inregs, &outregs);
}

int main(){

	printf("\nPulsa una tecla. Has pulsado: ");
    getche();

	printf("\nCursor invisible: ");
   	setcursortype(0);
   	pausa();
   	printf("\nCursor normal: ");
   	setcursortype(1);
   	pausa();
   	printf("\nCursor grueso: ");
   	setcursortype(2);
   	pausa();

   	printf("\nVamos a cambiar el modo de video\n");
   	pausa();
   	setvideomode(4);
    printf("Estamos en modo video\n");
    pausa();
    setvideomode(3);
    printf("Estamos en modo texto\n");
    pausa();

    printf("\nVamos a cambiar ahora el color de texto y de fondo\n");

    textbackground(4);
    textcolor(9);
    cputchar('Y');
    pausa();

    printf("\nVamos a cambiar la posicion del cursor\n");
    gotoxy(20,20);
    printf("\nPulsa una tecla para refrescar la pantalla\n");
    pausa();
    clrscr();
    gotoxy(0,0);
    printf("\nVamos ahora a pintar un recuadro blanco con pixeles coloreados en su interior\n");

    setvideomode(4);

    recuadro(2, 2, 22, 35, 15, 9);

    pixel(10, 20, 0);
    pixel(20, 20, 1);
    pixel(30, 30, 2);
    pixel(40, 40, 3);

    pausa();
    setvideomode(3);

	return 0;
}
