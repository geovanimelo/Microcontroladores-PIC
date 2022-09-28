#include <p18f4520.h>

#define coluna_1 = PORTCbits.RC7
#define coluna_2 = PORTCbits.RC6
#define coluna_3 = PORTCbits.RC5
#define linha_a = PORTBbits.RB4
#define linha_b = PORTBbits.RB5
#define linha_c = PORTBbits.RB6
#define linha_d = PORTBbits.RB7

void ISR_baixa_prioridade();
void ISR_alta_prioridade();
void Varre_Teclado(int linha);
void Delay_Teclado();
void my_keypad();

//coloca esse codigo nessa posi��o especifica da mem�ria
#pragma code int_alta = 0x0008
void int_alta()
{
	_asm //come�o trecho em asembly
		GOTO ISR_alta_prioridade	// Desvia o programa para a fun��o ISR_alta_prioridade.
	_endasm //final trecho em asembly
}
#pragma code

//coloca esse codigo nessa posi��o especifica da mem�ria
#pragma code int_baixa = 0x0018
void int_baixa()
{
	_asm //come�o trecho em asembly
		GOTO ISR_baixa_prioridade // Desvia o programa para a fun��o ISR_alta_prioridade.
	_endasm	//final trecho em asembly
}
#pragma code

#pragma interrupt ISR_alta_prioridade //especificar para o compilador que essa fun��o � de tratamento de interup��o
void ISR_alta_prioridade()
{
    if (INTCONbits.INT0IF)
    {
        Envia_Dado_Lcd ('X');
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
}

#pragma interrupt ISR_baixa_prioridade //especificar para o compilador que essa fun��o � de tratamento de interup��o
void ISR_baixa_prioridade()
{
}

void Inicializa_Interupcao()
{
    //configura��o pra conf do bot�o de teste
    TRISBbits.RB0 =	1;			// colocar o RB0 pino como entrada
    ADCON1 = 0b00001111;		// desabilitar as entradas anal�gicas
    INTCON2bits.INTEDG0 = 0;	// INTERRUPCAO NA BORDA DE DESCIDA
    INTCONbits.INT0IF = 0;		// desativou o IF
    INTCONbits.INT0IE  = 1;		// habilita interrup??o externa 0 (INT0)

	//configura��o da interrup��o externa 0
    INTCONbits.RBIE = 1; //Liga a interup��o na porta RBIE
    INTCONbits.RBIF = 0; //Uma das portas RB<7-4> mudou de estado
    INTCON2bits.RBIP = 1;
    INTCON2bits.RBPU =  0; //prepara o teclado para gerar interrup��o

    //TRISB = 0b00001111;            //Set RB4-RB7 as inputs to mcu

	INTCONbits.GIE  = 1;		// habilita o sistema de interrup��o

}

void Varre_Teclado(int linha){
    if (linha == 1){
        if (PORTCbits.RC7 == 0){
            Envia_Dado_Lcd ('1');
        } else if (PORTCbits.RC6 == 0){
            Envia_Dado_Lcd ('2');
        } else if (PORTCbits.RC5 == 0){
            Envia_Dado_Lcd ('3');
        }
    } else if (linha == 2){
        if (PORTCbits.RC7 == 0){
            Envia_Dado_Lcd ('4');
        } else if (PORTCbits.RC6 == 0){
            Envia_Dado_Lcd ('5');
        } else if (PORTCbits.RC5 == 0){
            Envia_Dado_Lcd ('6');
        }
    } else if (linha == 3){
        if (PORTCbits.RC7 == 0){
            Envia_Dado_Lcd ('7');
        } else if (PORTCbits.RC6 == 0){
            Envia_Dado_Lcd ('8');
        } else if (PORTCbits.RC5 == 0){
            Envia_Dado_Lcd ('9');
        }
    } else if (linha == 4){
        if (PORTCbits.RC7 == 0){
            Envia_Dado_Lcd ('*');
        } else if (PORTCbits.RC6 == 0){
            Envia_Dado_Lcd ('0');
        } else if (PORTCbits.RC5 == 0){
            Envia_Dado_Lcd ('#');
        }
    }
}
void Delay_Teclado()
{
    int i;
    for (i=0;i<5000;i++) {}
}

void my_keypad()
{
    //Test column 1
    PORTCbits.RC7 = 0;           //Set Column 1 to 1
    PORTCbits.RC6 = 1;           //Set Column 2 to 0
    PORTCbits.RC5 = 1;           //Set Column 3 to 0
    Delay_Teclado();

    //Test column 2
    PORTCbits.RC7 = 1;           //Set Column 1 to 0
    PORTCbits.RC6 = 0;           //Set Column 2 to 1
    PORTCbits.RC5 = 1;           //Set Column 3 to 0
    Delay_Teclado();
    //Test column 3
    PORTCbits.RC7 = 1;          //Set Column 1 to 0
    PORTCbits.RC6 = 1;          //Set Column 2 to 0
    PORTCbits.RC5 = 0;          //Set Column 3 to 1
    Delay_Teclado();
}