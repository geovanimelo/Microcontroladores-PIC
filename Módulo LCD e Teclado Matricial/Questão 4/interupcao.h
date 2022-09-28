/*
 Created by Rodrigo Alonso Caldas on 13/09/2020.
 Arquivo responsavel pelas Funções de interupções
*/

void ISR_baixa_prioridade();
void ISR_alta_prioridade();
void Inicializa_Interupcao();

unsigned tempo1, tempo2;


#pragma code int_alta = 0x0008

void int_alta(void)
{
    _asm
    GOTO ISR_alta_prioridade	// Desvia o programa para a função ISR_alta_prioridade.
    _endasm
}
#pragma code


#pragma code int_baixa = 0x0018

void int_baixa()
{
    _asm
    GOTO ISR_baixa_prioridade
    _endasm
}
#pragma code


#pragma interrupt ISR_alta_prioridade

void ISR_alta_prioridade()
{
    if (PIR1bits.CCP1IF)
    {
        TMR1H = 0;
        TMR1L = 7;			//desconta a execução do programa
        PIR1bits.CCP1IF = 0;
        tempo2 = CCPR1H ;
        tempo1 = CCPR1L ;
    }
}

#pragma interrupt ISR_baixa_prioridade

void ISR_baixa_prioridade()
{
}

void Inicializa_Interupcao(){
    //configura interrupção CCP1

    IPR1bits.CCP1IP = 1;		//alta priorida
    PIE1bits.CCP1IE = 1;		//int. habilitada
    PIR1bits.CCP1IF = 0;		//inicia flag
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;		//habilitador geral do CCP1
}

#ifndef QUESTAO_4_INTERUPCAO_H
#define QUESTAO_4_INTERUPCAO_H

#endif //QUESTAO_4_INTERUPCAO_H
