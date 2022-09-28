/*
 Created by Rodrigo Alonso Caldas on 12/09/2020.
 Arquivo responsavel pelas Funções da tela
*/

//Definição das funções
void Escreve_Letra(char dado);
void Escreve_Msg(char *mensagem);
char Recebe_Tela(void);
void Delay();
void Inicializa_Tela();


void Escreve_Letra(char dado) {
    TXREG = dado; //inicia transmissão
    while (!TXSTAbits.TRMT) { } //Espera a transmissão acabar
}

void Escreve_Msg(char *mensagem) {
    int i=0;
    while (mensagem[i])
    {
        Escreve_Letra(mensagem[i]);
        i++;
    }
}

char Recebe_Tela(void) {
    if (PIR1bits.RCIF)
    {
        return RCREG;
    }
    else{
        if(RCSTAbits.FERR) {
            RCSTAbits.CREN = 0;
            RCSTAbits.CREN = 1;
        }
        return 0;		//null
    }
}


void Inicializa_Tela() {

    TRISCbits.RC7 = 1; // Configura o Pino RC7 como entrada de dados
    TRISCbits.RC6 = 0; // Configura o pino RC6 como saída de dados

    TXSTA = 0B00100100; // Modo Assincrono;
    RCSTA = 0B10010000; // Habilita RC7->RX e RC6->TX; 8 bits de recepção de dados;
    BAUDCON = 0B00000000;

    SPBRG = 207; // Configura o registrador para 2400 bps
}


#ifndef Q3_TELA_H
#define Q3_TELA_H

#endif //Q3_TELA_H
