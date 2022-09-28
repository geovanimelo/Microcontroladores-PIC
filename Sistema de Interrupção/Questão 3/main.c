#include <p18f4520.h>
#include "lcd.h"
#include "relogio.h"
#include "teclado.h"
#include "interupcao.h"

void main()
{
    Inicializa_Lcd();
    Inicializa_Relogio();
    Inicializa_Interupcao();

    Escreve_Hora_Atual();
    while(1)
    {
        my_keypad();
    }
}
