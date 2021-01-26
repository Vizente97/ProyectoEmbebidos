#include <16F877A.h>
#fuses hs,xt,nowdt
#use delay(clock=2M)
#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7, bits=8, parity=N)  

int8 redLed;                                                            //Ciclo de trabajo para el led rojo (0-255)
int8 greenLed;                                                          //Ciclo de trabajo para el led verde (0-255)
int8 blueLed;                                                           //Ciclo de trabajo para el led azul (0-255)
int8 counter;
int8 i;
char dato;                                                           //contador para comparar el ciclo de trabajo con el periodo del pwm

#int_TIMER2                                                             //Interrupcion cada 50us para simular el pwm
void  TIMER2_isr(void) 
{  counter+=4; 
   if(redLed>counter)                                                    //Se suman 4 para reducir la resolucion del pwm y evitar parpadeos en los
  { output_high(PIN_B0);}                                             //leds ya que la frecuencia actual del microcontrolador no es suficiente
  else                                                                   //para un pwm con resolucion de 255
  { output_low(PIN_B0);    }
  if(greenLed>counter)
  { output_high(PIN_B1);   }
  else
  { output_low(PIN_B1);    }
  if(blueLed>counter)
  { output_high(PIN_B2);   }
  else
  {  output_low(PIN_B2);   }
}

#INT_RDA                                                             //Interrupcion cada 50us para simular el pwm
void  rda_isr(void) 
{  
   dato = getc();
}

void main()
{             
   //Configuramos los timers
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DIV_BY_1,49,1);                                     //Configuracion para interrupcion cada 50us
   //setup_comparator(NC_NC_NC_NC);                                       //Deshabilitamos las entradas analógicas
   setup_vref(FALSE);
   SET_TRIS_B( 0b00000111 );                                            //Configuramos el puerto B 
   enable_interrupts(INT_TIMER2);                                       //Habilitamos las interrupciones del timer 2
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_RDA);
   counter=0;
   redLed=0;
   greenLed=0;
   blueLed=0;                                                   //Variable para el ciclo for
   while(true){
      counter=0;
      redLed=0;
      greenLed=0;
      blueLed=0;
      switch(dato){
      case '0':
         for(i=0; i<254; i++)                                              //Variamos de verde a rojo
         {  redLed=i;
            greenLed=254-i;
            delay_ms(3);
         }
         for(i=0; i<254; i++)                                             //Variamos de rojo a azul
         {  blueLed=i;
            redLed=254-i;
            delay_ms(3);
         }           
         for(i=0; i<254; i++)                                            //Variamos azul a verde
         {  greenLed=i;
            blueLed=254-i;
            delay_ms(3);
         }
         break;
      case '1':
         for(i=0; i<254; i++)                                              //Variamos de negro a rojo
         {  redLed=i;
            delay_ms(15);
         }
         redLed = 0;
         for(i=0; i<254; i++)                                             //Variamos de negro a azul
         {  greenLed=i;
            delay_ms(15);
         }       
         greenLed = 0;
         for(i=0; i<254; i++)                                            //Variamos negro a verde
         {  blueLed=i;
            delay_ms(15);
         }
         blueLed = 0;
         break;
      case '2':                                                            
         for(i=0; i<254; i++)                                              //Variamos de verde a azul
         {  blueLed=i;
            greenLed=254-i;
            delay_ms(3);
         }
         for(i=0; i<254; i++)                                             //Variamos de azul a verde
         {  greenLed=i;
            blueLed=254-i;
            delay_ms(3);
         }
         break;
      case '3':                                                            
         for(i=0; i<254; i++)                                            //Variamos verde a azul
         {  blueLed=i;
            greenLed=254-i;
            delay_ms(3);
         }
         for(i=0; i<254; i++)                                             //Variamos de azul a red
         {  redLed=i;
            blueLed=254-i;
            delay_ms(3);
         }
         for(i=0; i<254; i++)                                              //Variamos de rojo a verde
         {  greenLed=i;
            redLed=254-i;
            delay_ms(3);
         }         
         break;
      }   
   }  
}
