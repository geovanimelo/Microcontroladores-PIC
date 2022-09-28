/*
 Created by Rodrigo Alonso Caldas on 13/09/2020.
 Arquivo responsavel pelas Funções do Frequencimetro
*/

// Variáveis Globais
int tempoTotal, tempoDiv ;
int freq;



//Definição das funções
void Inicializa_Frequencimetro();
void Calcula_Frequencia();
void Mosta_Frequencia();

void Calcula_Frequencia(){
    tempoTotal = (tempo2<<8)|(tempo1);

    tempoDiv = (tempoTotal) / 2;
    freq = 1 / (tempoDiv * 1E-6);                 //Converte para frequência em Hz
}


void Inicializa_Frequencimetro() {
    // configurando o modo captura
    TRISCbits.RC2 = 1;	//pino CCP1 como entrada

    CCP1CONbits.CCP1M3 = 0;	//captura a cada 4 borda de subida do sinal
    CCP1CONbits.CCP1M2 = 1;
    CCP1CONbits.CCP1M1 = 1;
    CCP1CONbits.CCP1M0 = 0;

    // configurando TMR1

    T1CON = 0b10010101;	// 16bits, prescaler 1:2, fosc/4, TMR1 ligado
    //T1CON = 0b00000001;	// 8bits, prescaler 1:1, fosc/4, TMR1 ligado
}

#ifndef QUESTAO_4_FREQUENCIMETRO_H
#define QUESTAO_4_FREQUENCIMETRO_H

#endif //QUESTAO_4_FREQUENCIMETRO_H
