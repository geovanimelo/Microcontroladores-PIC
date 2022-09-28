#include <p18f4520.h>
#include "tela.h"
#include "relogio.h"
#include "speaker.h"
#include "alarme.h"
#include "interupcao.h"

char dadoE;
char msgErro [] = {"Não existe essa opcao"};

void main()
{
	//INTERUPCAO
	Inicializa_Interupcao();

    //INTERUPCAO
    Inicializa_Relogio();

	//ALARME
    Inicializa_Speaker();
	Inicializa_Alarme();

	//TELA
	Inicializa_Tela();
    Escreve_Msg_Inicial();

	while(1)
	{

        dadoE = Recebe_Tela();
        if (dadoE == '1'){ //Arma Alarme
            Arma_Alarme();
        } else if ( dadoE == '2') { //Desarma alarme
            Desarma_Alarme();
        } else if ( dadoE == '3') {
            Altera_Hora();
        }

	}
}

