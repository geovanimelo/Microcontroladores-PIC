/*
 Created by Rodrigo Alonso Caldas on 12/09/2020.
 Arquivo responsavel pelas Funções do Auto Falante
*/

#define speaker PORTDbits.RD7

//Definição das funções
void Inicializa_Speaker();


void Inicializa_Speaker() {

    INTCONbits.PEIE=1; //habilita interrupção dos perifericos;
    PIE1bits.TMR1IE=1; //habilita interrupção do TIMER1;

// TMR1 recebe o valor 53026(65536 - 12500), que em Hexadecimal vale 0xCF2C
    TMR1L=0x00; // byte menos significativo
    TMR1H=0x00; // byte mais significativo
    T1CON=0b00100001; // Modo Temporizador, prescaler 1:4, clock interno;

    speaker = 0;
}

#ifndef Q3_SPEAKER_H
#define Q3_SPEAKER_H

#endif //Q3_SPEAKER_H
