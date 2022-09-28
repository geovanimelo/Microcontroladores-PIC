/*
 Created by Rodrigo Alonso Caldas on 12/09/2020.
 Arquivo responsavel pelas Funções do sistema de interupções
*/

int count = 0;

//Definição das funções
void ISR_alta_prioridade();
void ISR_baixa_prioridade();
void Inicializa_Interupcao();


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
    //Interupção dos sensores
    if (INTCONbits.RBIF) {

        if (statusAlarme == 1) {
            if (setor1 == 1 || setor2 == 1 || setor3 == 1 || setor4 == 1) {
                Liga_Alarme();
                if (setor1 == 1 && statusSetor1 == 0){
                    statusSetor1 = 1;
                    Log_Alarme(1, 1);
                }
                if (setor2 == 1 && statusSetor2 == 0){
                    statusSetor2 = 1;
                    Log_Alarme(2, 1);
                }
                if (setor3 == 1 && statusSetor3 == 0){
                    statusSetor3 = 1;
                    Log_Alarme(3, 1);
                }
                if (setor4 == 1 && statusSetor4 == 0){
                    statusSetor4 = 1;
                    Log_Alarme(4, 1);
                }
            }

            if (setor1 == 0 && statusSetor1 == 1){
                statusSetor1 = 0;
                Log_Alarme(1, 0);
            }
            if (setor2 == 0 && statusSetor2 == 1){
                statusSetor2 = 0;
                Log_Alarme(2, 0);
            }
            if (setor3 == 0 && statusSetor3 == 1){
                statusSetor3 = 0;
                Log_Alarme(3, 0);
            }
            if (setor4 == 0 && statusSetor4 == 1){
                statusSetor4 = 0;
                Log_Alarme(4, 0);
            }

        }

        INTCONbits.RBIF = 0;
    }

    //Interupção do timer0 seg do relógio
    if (INTCONbits.TMR0IF) {
        TMR0H = 0xC2;
        TMR0L = 0xF7;
        Add_Relogio();
        INTCONbits.TMR0IF = 0;
    }

    //Interupção do timer1 speaker
    if(PIR1bits.TMR1IF)
    {
        if (speakerStatus == 1){
            speaker = ~speaker;   // altera valor para ativar o speaker
        }

        TMR1L=0x00;   //recarrega o TMR1L;
        TMR1H=0x00;   //recarrega o TMR1H;
        PIR1bits.TMR1IF = 0;  //limpa o overflow.
    }

}

#pragma interrupt ISR_baixa_prioridade //especificar para o compilador que essa função é de tratamento de interupção
void ISR_baixa_prioridade()
{

}


void Inicializa_Interupcao()
{
    //configuração pra conf do botão de teste
    ADCON1 = 0b00001111;		// desabilitar as entradas analógicas
    INTCON2bits.INTEDG0 = 0;	// INTERRUPCAO NA BORDA DE DESCIDA
    INTCONbits.INT0IF = 0;		// desativou o IF

    //configuração da interrupção externa 0
    INTCONbits.RBIE = 1; //Liga a interupção na porta RBIE
    INTCONbits.RBIF = 0; //Uma das portas RB<7-4> mudou de estado
    INTCON2bits.RBIP = 1;
    INTCON2bits.RBPU =  0; //prepara para gerar interrupção

    INTCONbits.GIE  = 1;		// habilita o sistema de interrupção

}

#ifndef Q3_INTERUPCAO_H
#define Q3_INTERUPCAO_H

#endif //Q3_INTERUPCAO_H
