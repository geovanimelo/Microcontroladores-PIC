/*
 Created by Rodrigo Alonso Caldas on 12/09/2020.
 Arquivo responsavel pelas Funções do Alarme
*/

//definindo variaveis globais
#define setor1 PORTBbits.RB4
#define setor2 PORTBbits.RB5
#define setor3 PORTBbits.RB6
#define setor4 PORTBbits.RB7

int statusAlarme = 0;
int statusSetor1 = 0;
int statusSetor2 = 0;
int statusSetor3 = 0;
int statusSetor4 = 0;


char mensagemArma [] = {" O alarme foi Armado"};
char mensagemDesarma [] = {" O alarme foi Desarmado"};

char mensagemSetorAcionou [] = {"Acionou o Setor "};
char mensagemSetorDesacionou [] = {"Desacionou Setor "};
char mensagemAs [] = {" as "};
int speakerStatus = 0;



void Arma_Alarme();
void Desarma_Alarme();
void Liga_Alarme();
void Desliga_Alarme();
void Inicializa_Alarme();
void Log_Alarme(int zona, int acao);

void Log_Alarme(int zona, int acao){

    if (acao == 1){
        Escreve_Msg(mensagemSetorAcionou);
    } else {
        Escreve_Msg(mensagemSetorDesacionou);
    }

    if (zona == 1){
        Escreve_Letra('1');
    } else if (zona == 2){
        Escreve_Letra('2');
    } else if (zona == 3){
        Escreve_Letra('3');
    } else if (zona == 4){
        Escreve_Letra('4');
    }
    Escreve_Msg(mensagemAs);

    //escreve a hora e pula linha
    Escreve_Hora_Atual();
    Escreve_Letra('\r\n');

}


void Arma_Alarme(){
    statusAlarme = 1;
    Escreve_Msg(mensagemArma);
    Escreve_Letra('\r\n'); //Quebra de linha
}

void Desarma_Alarme(){
    statusAlarme = 0;
    Desliga_Alarme();
    Escreve_Msg(mensagemDesarma);
    Escreve_Letra('\r\n'); //Quebra de linha
}

void Liga_Alarme(){
    speakerStatus = 1;
}

void Desliga_Alarme(){
    speakerStatus = 0;
}

void Inicializa_Alarme(){
    TRISDbits.RD7 = 0;			// configura o speaker
}

void Escreve_Msg_Inicial(){
    char mensagem1 [] = {"Digite 1 para armar"};
    char mensagem2 [] = {"Digite 2 para desarmar"};
    char mensagem3 [] = {"Digite 3 para atualizar a hora"};

    Escreve_Msg(mensagem1);
    Escreve_Letra('\r\n'); //Quebra de linha
    Escreve_Msg(mensagem2);
    Escreve_Letra('\r\n'); //Quebra de linha
    Escreve_Msg(mensagem3);
    Escreve_Letra('\r\n'); //Quebra de linha

}

#ifndef Q3_ALARME_H
#define Q3_ALARME_H

#endif //Q3_ALARME_H
