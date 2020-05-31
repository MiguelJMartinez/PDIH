#include <stdio.h>
#include <dos.h>

unsigned char MODOTEXTO = 3;
unsigned char MODOGRAFICO = 4;

void pausa(){
    union REGS inregs, outregs;
    inregs.h.ah = 8;
    int86(0x21, &inregs, &outregs);
}

void modovideo(unsigned char modo){
    union REGS inregs, outregs;

    inregs.h.ah = 0x00;
    inregs.h.al = modo;

    int86(0x10, &inregs, &outregs);
}

int main(){
    //Cambiar el modo de video
    modovideo(MODOGRAFICO);
    printf("\nModo grafico: ");
    pausa();

    modovideo(MODOTEXTO);
    printf("\nModo Texto: ");
    pausa();

    return 0;
}