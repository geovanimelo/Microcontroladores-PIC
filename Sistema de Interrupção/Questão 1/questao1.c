#include <p18f4520.h>

void ISR_baixa_prioridade();
void ISR_alta_prioridade();

#pragma code int_alta = 0x0008 //coloca esse codigo nessa posição especifica da memória

void int_alta(void)
{
	_asm //come�o trecho em asembly
		GOTO ISR_alta_prioridade	// Desvia o programa para a função ISR_alta_prioridade.
	_endasm //final trecho em asembly
}
#pragma code


#pragma code int_baixa = 0x0018 //coloca esse codigo nessa posição especifica da memória

void int_baixa()
{
	_asm //come�o trecho em asembly
		GOTO ISR_baixa_prioridade // Desvia o programa para a função ISR_alta_prioridade.
	_endasm	//final trecho em asembly
}
#pragma code


#pragma interrupt ISR_alta_prioridade //especificar para o compilador que essa função é de tratamento de interupção

void ISR_alta_prioridade()
{
	if (INTCONbits.INT0IF)
	{
		LATCbits.LATC0=~LATCbits.LATC0;
		INTCON2bits.INTEDG0 = ~INTCON2bits.INTEDG0;
		INTCONbits.INT0IF = 0;		// sinaliza que a int0 foi atendida - Somente no final
	} 
	if (INTCON3bits.INT1IF) 
	{
		LATCbits.LATC0=~LATCbits.LATC0;
		INTCON2bits.INTEDG1 = ~INTCON2bits.INTEDG1;
		INTCON3bits.INT1IF = 0;		// sinaliza que a int0 foi atendida - Somente no final
	}
	if (INTCON3bits.INT2IF) 
	{
		LATCbits.LATC0=~LATCbits.LATC0;
		INTCON2bits.INTEDG2 = ~INTCON2bits.INTEDG2;
		INTCON3bits.INT2IF = 0;		// sinaliza que a int0 foi atendida - Somente no final
	}	
	
	
}


#pragma interrupt ISR_baixa_prioridade //especificar para o compilador que essa função é de tratamento de interupção

void ISR_baixa_prioridade()
{
}


void main()
{
	// configura��o da interrup��o externa 0
	
	TRISBbits.RB0 =	1;			// colocar o RB0 pino como entrada
	TRISBbits.RB1 =	1;			// colocar o RB1 pino como entrada
	TRISBbits.RB2 =	1;			// colocar o RB2 pino como entrada
	TRISCbits.RC0 = 0;			// configura LED

	ADCON1 = 0b00001111;		// desabilitar as entradas analógicas

	INTCON2bits.INTEDG0 = 0;	// INTERRUPCAO NA BORDA DE DESCIDA
	INTCONbits.INT0IF = 0;		// desativou o IF
	INTCONbits.INT0IE  = 1;		// habilita interrup��o externa 0 (INT0)
	
	INTCON3bits.INT1IF = 0;		// desativou o IF
	INTCON2bits.INTEDG1 = 0;	// INTERRUPCAO NA BORDA DE DESCIDA
	INTCON3bits.INT1IP  = 0;		// Seta bit com alta prioridade
	INTCON3bits.INT1IE  = 1;		// habilita interrupção externa 0 (INT1)
	
	INTCON2bits.INTEDG2 = 0;	// INTERRUPCAO NA BORDA DE DESCIDA
	INTCON3bits.INT2IF = 0;		// desativou o IF
	INTCON3bits.INT2IE  = 1;		// habilita interrupção externa 0 (INT2)
	INTCON3bits.INT2IP  = 0;		// Seta bit com alta prioridade
	
	INTCONbits.GIE  = 1;		// habilita o sistema de interrupção
	

	
	while(1)
	{	
//		alarme ();
//		irrigacao ();
//		controle_acesso ();
	}
}

 