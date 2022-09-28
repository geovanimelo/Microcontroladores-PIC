#ifndef LCD_H_   /* Include guard */

#define LCD_H_

extern void Delay_Lcd();
extern void Delay_Inicializacao_Lcd();
extern void Envia_Comando_Lcd(char comando);
extern void Envia_Dado_Lcd(char dado);
extern void Escreve_Msg_Lcd(char *mensagem);
extern void Inicializa_Lcd();

#endif // LCD_H_
