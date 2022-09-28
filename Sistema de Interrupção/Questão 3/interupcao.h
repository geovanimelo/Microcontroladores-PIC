/*
 Created by Rodrigo Alonso Caldas on 18/09/2020.
 Arquivo responsavel pelas Funções de interupções
*/

#define coluna_1 PORTCbits.RC7
#define coluna_2 PORTCbits.RC6
#define coluna_3 PORTCbits.RC5
#define linha_a PORTBbits.RB4
#define linha_b PORTBbits.RB5
#define linha_c PORTBbits.RB6
#define linha_d PORTBbits.RB7
#define SBIT_PS2  2

void ISR_baixa_prioridade();
void ISR_alta_prioridade();


//coloca esse codigo nessa posição especifica da memória
#pragma code int_alta = 0x0008
void int_alta()
{
    _asm //começo trecho em asembly
    GOTO ISR_alta_prioridade	// Desvia o programa para a função ISR_alta_prioridade.
    _endasm //final trecho em asembly
}
#pragma code

//coloca esse codigo nessa posição especifica da memória
#pragma code int_baixa = 0x0018
void int_baixa()
{
    _asm //começo trecho em asembly
    GOTO ISR_baixa_prioridade // Desvia o programa para a função ISR_alta_prioridade.
    _endasm	//final trecho em asembly
}
#pragma code

#pragma interrupt ISR_alta_prioridade //especificar para o compilador que essa função é de tratamento de interupção

void ISR_alta_prioridade()
{
    if (INTCONbits.INT0IF)
    {
        //Envia_Dado_Lcd ('X');
        INTCON2bits.INTEDG0 = ~INTCON2bits.INTEDG0;
        INTCONbits.INT0IF = 0;		// sinaliza que a int0 foi atendida - Somente no final
    }

    if (INTCONbits.RBIF)
    {
        if(PORTBbits.RB4 == 0){
            Varre_Teclado(1);
        } else if(PORTBbits.RB5 == 0){
            Varre_Teclado(2);
        } else if(PORTBbits.RB6 == 0){
            Varre_Teclado(3);
        } else if(PORTBbits.RB7 == 0){
            Varre_Teclado(4);
        }
        INTCONbits.RBIF = 0;
    }

    //Interupção do timer0 seg do relógio
    if (INTCONbits.TMR0IF) {
        TMR0H =0xF0 ;
        TMR0L =0xBD ;
        Add_Relogio();
        INTCONbits.TMR0IF = 0;
        if (editaAlarme == 0 && editaRelogio == 0){
            limpa_lcd();
            Escreve_Hora_Atual();
        }
    }
}

#pragma interrupt ISR_baixa_prioridade //especificar para o compilador que essa função é de tratamento de interupção
void ISR_baixa_prioridade()
{

}

void Inicializa_Interupcao()
{

    //configuração pra conf do botão de teste
    TRISBbits.RB0 =	1;			// colocar o RB0 pino como entrada
    ADCON1 = 0b00001111;		// desabilitar as entradas analógicas
    INTCON2bits.INTEDG0 = 0;	// INTERRUPCAO NA BORDA DE DESCIDA
    INTCONbits.INT0IF = 1;		// desativou o IF
    //INTCONbits.INT0IE  = 1;		// habilita interrup??o externa 0 (INT0)


    //configuração da interrupção externa 0
    INTCONbits.RBIE = 1; //Liga a interupção na porta RBIE
    INTCONbits.RBIF = 0; //Uma das portas RB<7-4> mudou de estado
    INTCON2bits.RBIP = 1;
    INTCON2bits.RBPU =  0; //prepara o teclado para gerar interrupção

    INTCONbits.GIE  = 1;		// habilita o sistema de interrupção
}



#ifndef QUESTAO_3_V2_INTERUPCAO_H
#define QUESTAO_3_V2_INTERUPCAO_H

#endif //QUESTAO_3_V2_INTERUPCAO_H
