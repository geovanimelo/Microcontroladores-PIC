#include <p18f4520.h>

//definindo variaveis globais
#define Porta_Lcd PORTD
#define RS PORTCbits.RC0
#define E PORTCbits.RC1

//funcoes
void Delay_Lcd()
{
	int i;
	for (i=0;i<400;i++) {}	
}
	
void Delay_Inicializacao_Lcd()
{
	int i;
	for (i=0;i<4000;i++) {}	
}

void Envia_Comando_Lcd(char comando)
{
	E=0;  //LCD desabilitado
	RS=0; //Seleciona o envio de intrucoes

	E=1;
	Porta_Lcd=comando; //envia metade alta D4-D7
	E=0; //habilita o LCD a receber a informacao

	E=1;
	comando=comando<<4;
	Porta_Lcd=comando; //envia metade alta D0-D4
	E=0; //habilita o LCD a receber a informacao

	Delay_Lcd();
}

void Envia_Dado_Lcd(char dado)
{
	E = 0;  //LCD desabilitado
	RS = 1; //Seleciona o envio de dado

	E = 1;
	Porta_Lcd=dado; //envia metade alta D4-D7
	E=0; //habilita o LCD a receber a informacao

	E=1;
	dado=dado<<4;
	Porta_Lcd=dado; //envia metade alta D0-D4
	E=0; //habilita o LCD a receber a informacao
	
	Delay_Lcd();		
}

void Escreve_Msg_Lcd(char *mensagem)
{
	int i=0;
	while (mensagem[i])
	{
		Envia_Dado_Lcd (mensagem[i]);
		i++;
	}	
}	
void Inicializa_Lcd()
{
	TRISC = 0b00011100; //Pinos de controle do LCD e das colunas do teclado
	TRISD = 0b00000000; //Conf porta LCD como saida
	
	Delay_Inicializacao_Lcd();
	Envia_Comando_Lcd (0b00000010); //configura LCD para 4 bits
	Envia_Comando_Lcd (0b00101000); //configura como vai ser a tela do LCD 
	Envia_Comando_Lcd (0b00001110); 
	Envia_Comando_Lcd (0b00000001);
}