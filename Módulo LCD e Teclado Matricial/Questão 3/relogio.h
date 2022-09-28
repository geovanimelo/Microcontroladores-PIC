/*
 Created by Rodrigo Alonso Caldas on 12/09/2020.
 Arquivo responsavel pelas Funções do Relógio
*/

//Definição das funções
void Altera_Hora();
void Add_Relogio();
void Inicializa_Relogio();
void Escreve_Hora_Atual();
void Altera_Hora();
int Pega_Hora1(char x);

//textos altera relogio
char mensagemRelogioAlteraInicio [] = {" Agora voce ira alterar a hora do sistema"};
char mensagemRelogioDigiteHora [] = {"Digite a hora 00 ate 23"};
char mensagemRelogioDigiteMinuto [] = {"Digite o minuto 00 ate 59"};
char mensagemRelogioDigiteFim [] = {"Relogio configurado"};
int hora1, minuto1;

//Variaveis do Relógio
int relogioSegundos = 00;
int relogioMinutos = 00;
int relogioHoras = 00;

char tempoStr[];
char dots = ':';

void Add_Relogio() {
    relogioSegundos++;                             //Incrementa os segundos
    if(relogioSegundos == 60) {                    //Se segundos igual a 60
        relogioSegundos = 00;                      //Reinicia os segundos
        relogioMinutos++;                         //Incrementa os minutos

        if(relogioMinutos == 60) {                //Se minutos igual a 60
            relogioMinutos = 00;                  //Reinicia os minutos
            relogioHoras++;                       //Incrementa as horas

            if(relogioHoras == 24) {              //Se horas igual a 24
                relogioHoras = 00;                //Reinicia as horas
            }
        }
    }
}

void Escreve_Hora_Atual() {

    itoa(relogioHoras, tempoStr, 10);
    Escreve_Msg(tempoStr);
    Escreve_Letra(dots);

    itoa(relogioMinutos, tempoStr, 10);
    Escreve_Msg(tempoStr);
    Escreve_Letra(dots);

    itoa(relogioSegundos, tempoStr, 10);
    Escreve_Msg(tempoStr);
}

//gambiaras
int Pega_Hora1(char x){
    if (x == '0'){
        return 0;
    } else if (x == '1'){
        return 10;
    } else if (x == '2'){
        return 20;
    } else {
        return 0;
    }
}
int Pega_Hora2(char x){
    if (x == '0'){
        return hora1;
    } else if (x == '1'){
        return hora1+1;
    } else if (x == '2'){
        return hora1+2;
    } else if (x == '3'){
        return hora1+3;
    } else if (x == '4'){
        return hora1+4;
    } else if (x == '5'){
        return hora1+5;
    } else if (x == '6'){
        return hora1+6;
    } else if (x == '7'){
        return hora1+7;
    } else if (x == '8'){
        return hora1+8;
    } else if (x == '9'){
        return hora1+9;
    } else {
        return hora1;
    }
}
int Pega_Minuto1(char x){
    if (x == '0'){
        return 0;
    } else if (x == '1'){
        return 10;
    } else if (x == '2'){
        return 20;
    } else if (x == '3'){
        return 30;
    } else if (x == '4'){
        return 40;
    } else if (x == '5'){
        return 50;
    } else {
        return 0;
    }
}
int Pega_Minuto2(char x){
    if (x == '0'){
        return minuto1;
    } else if (x == '1'){
        return minuto1+1;
    } else if (x == '2'){
        return minuto1+2;
    } else if (x == '3'){
        return minuto1+3;
    } else if (x == '4'){
        return minuto1+4;
    } else if (x == '5'){
        return minuto1+5;
    } else if (x == '6'){
        return minuto1+6;
    } else if (x == '7'){
        return minuto1+7;
    } else if (x == '8'){
        return minuto1+8;
    } else if (x == '9'){
        return minuto1+9;
    } else {
        return minuto1;
    }
}

void Altera_Hora(){
    Escreve_Msg(mensagemRelogioAlteraInicio);
    Escreve_Letra('\r\n');

    Escreve_Msg(mensagemRelogioDigiteHora);
    Escreve_Letra('\r\n');
    while (!PIR1bits.RCIF);
    hora1 = Pega_Hora1(RCREG);
    while (!PIR1bits.RCIF);
    relogioHoras = Pega_Hora2(RCREG);
    Escreve_Letra('\r\n');

    Escreve_Msg(mensagemRelogioDigiteMinuto);
    Escreve_Letra('\r\n');
    while (!PIR1bits.RCIF);
    minuto1 = Pega_Minuto1(RCREG);
    while (!PIR1bits.RCIF);
    relogioMinutos = Pega_Minuto2(RCREG);
    Escreve_Letra('\r\n');

    Escreve_Msg(mensagemRelogioDigiteFim);
    Escreve_Letra('\r\n');
}

void Inicializa_Relogio() {
    //configuracao do timer 0 por interrupção 1s
    T0CONbits.TMR0ON = 1;		// LIGA O TIMER 0
    T0CONbits.T08BIT = 0;		// 16 bits
    T0CONbits.T0CS = 0;			// função timer
    T0CONbits.PSA = 0;			// usar o prescaler
    T0CONbits.T0PS0 = 0;		// prescaler de 1:128

    TMR0H = 0xC2;
    TMR0L = 0xF7;			//65536-15625 = 49911

    INTCONbits.TMR0IE  = 1;
}

#ifndef Q3_RELOGIO_H
#define Q3_RELOGIO_H

#endif //Q3_RELOGIO_H
