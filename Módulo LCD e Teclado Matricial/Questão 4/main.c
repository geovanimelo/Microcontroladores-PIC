#include <p18f4520.h>
#include "interupcao.h"
#include "frequencimetro.h"
#include "display.h"


void main()
{
    Inicializa_Interupcao();
    Inicializa_Frequencimetro();
    Inicializa_Display();

    while(1)
    {
        Calcula_Frequencia();
        Mosta_Frequencia();
    }
}
