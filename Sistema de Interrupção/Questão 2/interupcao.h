#ifndef INTERUPCAO_H_   /* Include guard */
#define INTERUPCAO_H_

extern void int_alta();
extern void int_baixa();
extern void ISR_alta_prioridade();
extern void ISR_baixa_prioridade();
extern void Inicializa_Interupcao();
extern void Varre_Teclado(char linha);
extern void Delay_Teclado();
extern void my_keypad();

#endif // INTERUPCAO_H_