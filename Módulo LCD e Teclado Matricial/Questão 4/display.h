/*
 Created by Rodrigo Alonso Caldas on 13/09/2020.
 Arquivo responsavel pelas Funções do Display
*/

//variaveis
char numeros[11]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x40};
char freqStr[4];
int n1,n2,n3,n4;

//Definição das funções
void Delay();
void Escolhe_Display(int x);
void Liga_Display();
void Escreve_Numero(int x);
void Mostra_Frequencia();
void Inicializa_Display();

void Delay()
{
    int i;
    for (i=0;i<500;i++) {}
}

void Escolhe_Display(int x){
    if (x == 1){
        LATCbits.LATC4 = 0;
        LATCbits.LATC5 = 1;
        LATCbits.LATC6 = 1;
        LATCbits.LATC7 = 1;
    } else if (x == 2){
        LATCbits.LATC4 = 1;
        LATCbits.LATC5 = 0;
        LATCbits.LATC6 = 1;
        LATCbits.LATC7 = 1;
    } else if (x == 3){
        LATCbits.LATC4 = 1;
        LATCbits.LATC5 = 1;
        LATCbits.LATC6 = 0;
        LATCbits.LATC7 = 1;
    } else if (x == 4){
        LATCbits.LATC4= 1;
        LATCbits.LATC5= 1;
        LATCbits.LATC6= 1;
        LATCbits.LATC7= 0;
    }
    Delay();
}

void Liga_Display(){
    LATCbits.LATC4 = 1;
    LATCbits.LATC5 = 1;
    LATCbits.LATC6 = 1;
    LATCbits.LATC7 = 1;
}

void Escreve_Numero(int x){
        LATD = numeros[x];
}

void Mosta_Frequencia(){
    if (freq > 9999){
        Escreve_Numero(10);
        Escolhe_Display(1);
        Liga_Display();

        Escreve_Numero(10);
        Escolhe_Display(2);
        Liga_Display();

        Escreve_Numero(10);
        Escolhe_Display(3);
        Liga_Display();

        Escreve_Numero(10);
        Escolhe_Display(4);
        Liga_Display();
    } else {
        itoa(freq, freqStr, 10);
        n1 = freqStr[0] - 48; //O char é em asc e o 0 é 48....9 é 57
        n2 = freqStr[1] - 48;
        n3 = freqStr[2] - 48;
        n4 = freqStr[3] - 48;

        Escreve_Numero(n1);
        Escolhe_Display(1);
        Liga_Display();

        Escreve_Numero(n2);
        Escolhe_Display(2);
        Liga_Display();

        Escreve_Numero(n3);
        Escolhe_Display(3);
        Liga_Display();

        Escreve_Numero(n4);
        Escolhe_Display(4);
        Liga_Display();

    }
}

void Inicializa_Display() {

    TRISCbits.RC2 =	1;			// colocar o RC2 como entrada clock

    TRISCbits.RC4 = 0;			// colocar o RC4 pino como saida ESCOLHE DISPLAY
    TRISCbits.RC5 = 0;			// colocar o RC5 pino como saida ESCOLHE DISPLAY
    TRISCbits.RC6 = 0;			// colocar o RC6 pino como saida ESCOLHE DISPLAY
    TRISCbits.RC7 = 0;			// colocar o RC7 pino como saida ESCOLHE DISPLAY

    TRISD = 0B00000000;         // coloca todas as portas d para saida

}

#ifndef QUESTAO_4_DISPLAY_H
#define QUESTAO_4_DISPLAY_H

#endif //QUESTAO_4_DISPLAY_H
