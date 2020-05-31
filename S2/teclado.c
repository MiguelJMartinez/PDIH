#include <stdio.h>
#include <dos.h>

void pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 8;
    int86(0x21, &inregs, &outregs);
}

int mi_getchar(){
    union REGS inregs, outregs;
    int caracter;
    inregs.h.ah = 1;
    int86(0x21, &inregs, &outregs);
    caracter = outregs.h.al;
    return caracter;
}

void mi_putchar(char c){
    union REGS inregs, outregs;
    inregs.h.ah = 2;
    inregs.h.dl = c;
    int86(0x21, &inregs, &outregs);
}

void cputchar(unsigned char c){
    union REGS inregs, outregs;
    inregs.h.ah = 12;
    inregs.h.al = (int)c;
    inregs.h.bh = 0x00;
    inregs.x.cx = 1;
    int86(0x10, &inregs, &outregs);
}

int main(){
    int tmp;

    //Leer un caracter por teclado
    printf("\nPulsa una tecla:  ");
    tmp = mi_getchar();

    //Mostrar el caracter por pantalla
    printf("\nHas pulsado: ");
    mi_cputchar( (char)tmp );
    pausa();
    return 0;
}