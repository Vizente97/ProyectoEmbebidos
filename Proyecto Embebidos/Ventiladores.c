#include<16f877a.h>   //Seleccionamos el PIC
#DEVICE adc=10
#fuses hs,xt,nowdt
#include <stdio.h>
#use delay(clock=2M)
#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7, bits=8, parity=N) 

float temperatura;
int motor;
void main(){
   char dato;
   char pwmv11,pwmv12,pwmv13;
   char pwmv21,pwmv22,pwmv23;
   char temp11,temp12,temp13;
   //*******************************
   setup_ccp1(ccp_pwm); //Configura el módulo CCP1 en modo PWM
   set_pwm1_duty(0);    //Determina el ciclo de trabajo en escala de 0 a 255 (PARAMETRO DE INICIO)
   setup_ccp2(ccp_pwm); //Configura el módulo CCP1 en modo PWM
   set_pwm2_duty(0);    //Determina el ciclo de trabajo en escala de 0 a 255 (PARAMETRO DE INICIO)
   //*******************************
   
   dato = getc();
   while(true){
      switch(dato){
         case 't':temp11 = getc();
                  delay_ms(50);
                  temp12 = getc();
                  delay_ms(50);
                  temp13 = getc();
                  int numt13 = (temp11 - '0');
                  int numt12 = (temp12 - '0');
                  int numt11 = (temp13 - '0');
                  temperatura = (numt13*100)+(numt12*10)+numt11;
                  motor = (255*temperatura)/100; //obtenemos valor del ciclo de trabajo del motor
                  set_pwm1_duty(motor);  //aignamos el valor del ciclo de trabajo
                  set_pwm2_duty(motor);
                  dato = getc();
                  break;
         case 'm':pwmv11 = getc();
                  delay_ms(50);
                  pwmv12 = getc();
                  delay_ms(50);
                  pwmv13 = getc();
                  int numv13 = (pwmv11 - '0');
                  int numv12 = (pwmv12 - '0');
                  int numv11 = (pwmv13 - '0');
                  int total1 = (numv13*100)+(numv12*10)+numv11;              
                  delay_ms(50);
                  pwmv21 = getc();
                  delay_ms(50);
                  pwmv22 = getc();
                  delay_ms(50);
                  pwmv23 = getc();
                  int numv23 = (pwmv21 - '0');
                  int numv22 = (pwmv22 - '0');
                  int numv21 = (pwmv23 - '0');
                  int total2 = (numv23*100)+(numv22*10)+numv21;
                  set_pwm1_duty(total1);  //aignamos el valor del ciclo de trabajo
                  set_pwm2_duty(total2); 
                  dato = getc();
                  break;
      }
   }
}
