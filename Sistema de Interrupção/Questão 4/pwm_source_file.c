
void main()
{
   TRISC  = 0xBF;
   PORTC  = 0xBF;
   ADCON0 = 0x01;
   ADCON1 = 0x10;
   ANSEL  = 0x01;

   PWM1_Init(3000);
   PWM1_Start();
   PWM1_Set_Duty(128);

   while(1)
   {
      PWM1_Set_Duty(ADC_Read(0)>>2);

   } //end while

} //end main
