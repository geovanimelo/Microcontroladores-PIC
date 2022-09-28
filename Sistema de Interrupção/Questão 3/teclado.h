/*
 Created by Rodrigo Alonso Caldas on 18/09/2020.
 Arquivo responsavel pelas Funções do teclado
*/

//funções
void Varre_Teclado(int linha);
void Delay_Teclado();

void Varre_Teclado(int linha){
    if((editaAlarme == 1) || (editaRelogio == 1)) {
        if (linha == 1) {
            if (PORTCbits.RC7 == 0) {
                Envia_Dado_Lcd('1');
                Seta_Numero(1);
            } else if (PORTCbits.RC6 == 0) {
                Envia_Dado_Lcd('2');
                Seta_Numero(2);
            } else if (PORTCbits.RC5 == 0) {
                Envia_Dado_Lcd('3');
                Seta_Numero(3);
            }
        } else if (linha == 2) {
            if (PORTCbits.RC7 == 0) {
                Envia_Dado_Lcd('4');
                Seta_Numero(4);
            } else if (PORTCbits.RC6 == 0) {
                Envia_Dado_Lcd('5');
                Seta_Numero(5);
            } else if (PORTCbits.RC5 == 0) {
                Envia_Dado_Lcd('6');
                Seta_Numero(6);
            }
        } else if (linha == 3) {
            if (PORTCbits.RC7 == 0) {
                Envia_Dado_Lcd('7');
                Seta_Numero(7);
            } else if (PORTCbits.RC6 == 0) {
                Envia_Dado_Lcd('8');
                Seta_Numero(8);
            } else if (PORTCbits.RC5 == 0) {
                Envia_Dado_Lcd('9');
                Seta_Numero(9);
            }
        } else if (linha == 4) {
            if (PORTCbits.RC6 == 0) {
                Envia_Dado_Lcd('0');
                Seta_Numero(0);
            }
        }
    } else {
        if (linha == 4) {
            if (PORTCbits.RC7 == 0) {
                Edita_Relogio();
            } else if (PORTCbits.RC5 == 0) {
                if (alarmando == 1){
                    Desliga_Alarme();
                } else {
                    Edita_Alarme();
                }
            }
        }
    }
}

void Delay_Teclado()
{
    int i;
    for (i=0;i<8000;i++) {}
}

void my_keypad()
{
    //Testa coluna 1
    PORTCbits.RC7 = 0;           //Seta Coluna 1 para 1
    PORTCbits.RC6 = 1;           //Seta Coluna 2 para 0
    PORTCbits.RC5 = 1;           //Seta Coluna 3 para 0
    Delay_Teclado();

    //Testa coluna 2
    PORTCbits.RC7 = 1;           //Seta Coluna 1 para 0
    PORTCbits.RC6 = 0;           //Seta Coluna 2 para 1
    PORTCbits.RC5 = 1;           //Seta Coluna 3 para 0
    Delay_Teclado();

    //Testa coluna 3
    PORTCbits.RC7 = 1;          //Seta Coluna 1 para 0
    PORTCbits.RC6 = 1;          //Seta Coluna 2 para 0
    PORTCbits.RC5 = 0;          //Seta Coluna 3 para 1
    Delay_Teclado();
}


#ifndef QUESTAO_3_V2_TECLADO_H
#define QUESTAO_3_V2_TECLADO_H

#endif //QUESTAO_3_V2_TECLADO_H
