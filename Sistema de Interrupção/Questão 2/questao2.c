#include <p18f4520.h>
#include "lcd.h"
#include "interupcao.h"

//definindo variaveis globais
#define Porta_Lcd PORTD
#define RS PORTCbits.RC0
#define E PORTCbits.RC1

#define linha_1 TRISBbits.RB4
#define linha_2 TRISBbits.RB5
#define linha_3 TRISBbits.RB6
#define linha_4 TRISBbits.RB7

//variaveis
char mensagem1 [] = {"Rodrigo Caldas"};

void main()
{
	//INTERUPCAO
	Inicializa_Interupcao();
	
	//LCD
	Inicializa_Lcd ();
	
	while(1)
	{
	    my_keypad();
//        Escreve_Msg_Lcd(mensagem1);
//        while (1) {
//
//        }

	}
}

 