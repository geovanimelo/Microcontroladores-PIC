/*
 Created by Rodrigo Alonso Caldas on 18/09/2020.
 Arquivo responsavel pelas Funções do relógio
*/

#define ledAlarme PORTCbits.RC3

//Definição das funções
void Add_Relogio();
void Edita_Relogio();
void Edita_Alarme();
void Inicializa_Relogio();
void Escreve_Hora_Atual();
void my_keypad(); //função está escrita no teclado.h
void Desliga_Alarme(); //função está escrita no teclado.h
void Liga_Alarme(); //função está escrita no teclado.h


//textos altera relogio
char mensagemEditaRelogio [] = {"Edt o relogio"};
char mensagemEditaAlarme [] = {"Edt o alarme"};
char mensagemDigiteHora [] = {"Hora: "};
char mensagemDigiteMinuto [] = {"Minuto: "};

//Variaveis do Relógio
int relogioSegundos = 00;
int relogioMinutos = 00;
int relogioHoras = 00;

//Variaveis do Alarme
int alarmeSegundos = 00;
int alarmeMinutos = 00;
int alarmeHoras = 00;

//variaveis
int editaAlarme = 0;
int editaRelogio = 0;
int aux = 0;
int aux2 = 0;
int editaHora = 0;
int editaMinuto = 0;
int alarmando = 0;


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
    //verificando alarme
    if (relogioSegundos == alarmeSegundos && relogioMinutos == alarmeMinutos && relogioHoras == alarmeHoras){
        Liga_Alarme();
    }
}

void Edita_Relogio(){
    relogioHoras = 00;
    relogioMinutos = 00;
    editaRelogio = 1;
    editaHora = 1;
    aux = 0;
    limpa_lcd();
    Escreve_Msg_Lcd(mensagemEditaRelogio);
    Segunda_Linha();
    Escreve_Msg_Lcd(mensagemDigiteHora);
}

void Edita_Alarme(){
    alarmeHoras = 00;
    alarmeMinutos = 00;
    editaAlarme = 1;
    editaHora = 1;
    aux = 0;
    limpa_lcd();
    Primeira_Linha();
    Escreve_Msg_Lcd(mensagemEditaAlarme);
    Segunda_Linha();
    Escreve_Msg_Lcd(mensagemDigiteHora);
}

void Seta_Numero(int x){
    if (aux2 == 0){
        aux = Pega_Numero1(x);
        aux2++;
    } else {
        aux2 = 0;
        if (editaRelogio == 1) { //EDIÇÃO DO RELOGIO
            if (editaHora == 1){
                relogioHoras = aux+x;
                aux = 0;
                editaHora = 0;
                editaMinuto = 1;
                //escreve no lcd
                limpa_lcd();
                Primeira_Linha();
                Escreve_Msg_Lcd(mensagemEditaRelogio);
                Segunda_Linha();
                Escreve_Msg_Lcd(mensagemDigiteMinuto);
            } else if (editaMinuto == 1){
                relogioMinutos = aux+x;
                aux = 0;
                editaMinuto = 0;
                editaRelogio = 0;
                //escreve no lcd
                limpa_lcd();
                Primeira_Linha();
                Escreve_Hora_Atual();
                editaRelogio = 0;
            }
        } else if (editaAlarme == 1){     //EDIÇÃO DO RELOGIO
            if (editaHora == 1){
                alarmeHoras = aux+x;
                aux = 0;
                editaHora = 0;
                editaMinuto = 1;
                //escreve no lcd
                limpa_lcd();
                Primeira_Linha();
                Escreve_Msg_Lcd(mensagemEditaAlarme);
                Segunda_Linha();
                Escreve_Msg_Lcd(mensagemDigiteMinuto);
            } else if (editaMinuto == 1){
                alarmeMinutos = aux+x;
                aux = 0;
                editaMinuto = 0;
                editaRelogio = 0;
                //escreve no lcd
                limpa_lcd();
                Primeira_Linha();
                Escreve_Hora_Atual();
                editaAlarme = 0;
            }
        }

    }
}

//gambiaras
int Pega_Numero1(int x){
    if (x == 0){
        return 0;
    } else if (x == 1){
        return 10;
    } else if (x == 2){
        return 20;
    } else if (x == 3){
        return 30;
    } else if (x == 4){
        return 40;
    } else if (x == 5){
        return 50;
    } else {
        return 0;
    }
}

void Liga_Alarme(){
    alarmando = 1;
    ledAlarme = 1;
}

void Desliga_Alarme(){
    alarmando = 0;
    ledAlarme = 0;
}

void Escreve_Hora_Atual() {

    itoa(relogioHoras, tempoStr, 10);
    Escreve_Msg_Lcd(tempoStr);
    Envia_Dado_Lcd(dots);

    itoa(relogioMinutos, tempoStr, 10);
    Escreve_Msg_Lcd(tempoStr);
    Envia_Dado_Lcd(dots);

    itoa(relogioSegundos, tempoStr, 10);
    Escreve_Msg_Lcd(tempoStr);
}

void Inicializa_Relogio() {

    TRISCbits.RC3 = 0; //led do alarme

    //configuracao do timer 0 por interrupção 1s
    T0CONbits.TMR0ON = 1;		// LIGA O TIMER 0
    T0CONbits.T08BIT = 0;		// 16 bits
    T0CONbits.T0CS = 0;			// função timer
    T0CONbits.PSA = 0;			// usar o prescaler
    T0CONbits.T0PS0 = 0;		// prescaler de 1:128

    TMR0H = 0xC2;
    TMR0L = 0xF7;

    INTCONbits.TMR0IE  = 1;
}


#ifndef QUESTAO_3_V2_RELOGIO_H
#define QUESTAO_3_V2_RELOGIO_H

#endif //QUESTAO_3_V2_RELOGIO_H
