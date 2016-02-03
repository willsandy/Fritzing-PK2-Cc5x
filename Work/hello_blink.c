
/*  Compile with  PK2CC5X Tool chain
https://github.com/willsandy/Fritzing-PK2-Cc5x  */ 

/* hello_blink.c  PICkit 2 breadboard LED + bitbanging com    */
/* Program for testing components on breadboard               */ 
/* Blink with LED, serial menu LED on/off blink +/- Sw status */

/* B Knudsen Cc5x C-compiler - not ANSI-C */
#include <16F690.h>
#include <int16Cxx.h>
#pragma config |= 0x00D4 

/* FUNCTION PROTOTYPES */
void delay10( char );
void init_serial( void );
void putchar( char);
void printf(const char *string, char variable);

/* GLOBAL VARIABLES */
bit receiver_flag;   /* Signal-flag used by interrupt routine   */
char receiver_byte;  /* Transfer Byte used by interrupt routine */


/* INTERRUPT ROUTINE */
/* Interrupt routine - receiving chars at need */ 
#pragma origin 4
interrupt int_server( void ) /* the place for the interrupt routine */
{
  int_save_registers
  /* New interrupts are automaticaly disabled            */
  /* "Interrupt on change" at pin RA1 from PK2 UART-tool */
  
  if( PORTA.1 == 0 )  /* Interpret this as the startbit  */
    {  /* Receive one full character   */
      char bitCount, ti;
      /* delay 1,5 bit 156 usec at 4 MHz         */
      /* 5+28*5-1+1+2+9=156 without optimization */
      ti = 28; do ; while( --ti > 0); nop(); nop2();
      for( bitCount = 8; bitCount > 0 ; bitCount--)
       {
         Carry = PORTA.1;
         receiver_byte = rr( receiver_byte);  /* rotate carry */
         /* delay one bit 104 usec at 4 MHz       */
         /* 5+18*5-1+1+9=104 without optimization */ 
         ti = 18; do ; while( --ti > 0); nop(); 
        }
      receiver_flag = 1; /* A full character is now received */
    }
  RABIF = 0;    /* Reset the RABIF-flag before leaving   */
  int_restore_registers
  /* New interrupts are now enabled */
}



 /* MAIN PROGRAM */

void main( void)
{
    /* Initialisations */

  TRISC.0 = 0;   /* PORTC pin 0 output to LED     */
  TRISC.7 = 1;   /* PORTC pin 7 input from Button */
  ANSELH.1 = 0;  /* PORTC pin 7 not analog        */

  init_serial();
  char speed = 100;
  char period;
  char choice;
  bit blink=1;
  receiver_flag=0;
  
  IOCA.1 = 1; /* PORTA.1 interrupt on change */
  RABIE =1;   /* interrupt on change         */
  GIE = 1;    /* interrupt enable            */
    
    /* Main loop  */

while(1)
   {
     if( receiver_flag ) /* Character received? */ 
      {
        choice = receiver_byte;
        receiver_flag = 0; /* Character now taken */
		/* menu alternatives */
        switch (choice)
         {
          case 'l':
          case 'L':
            printf("\r\n%c LED ON\r\n", choice);
            PORTC.0 = 1; /* PORTC pin 0 "1" */
            blink=0;
            break;
          case 'o':
          case 'O':
            printf("\r\n%c LED OFF\r\n", choice);
            PORTC.0 = 0; /* PORTC pin 0 "0" */
            blink=0;
            break;
          case 'b':
          case 'B':
            blink=1;
            printf("\r\n%c LED BLINK\r\n", choice);
            break;
          case 'S':
          case 's':
            if(!PORTC.7) printf("\r\n%c Switch is ON/pressed\r\n", choice);
            else printf("\r\n%c Switch is OFF/unpressed\r\n", choice);
            break;
          case '-':
            if(period > 20) period -=10;
            else period = 10;
            printf("\r\n%c ", choice);
            printf("Dec delay %u\r\n", period);
            blink = 1;
            break;
          case '+':
            if(period < 240) period +=10;
            else period = 250;
            printf("\r\n%c ", choice);
            printf("Inc delay %u\r\n", period);
            blink = 1;
            break;
          default:
            printf("\r\n%c (L)ed On, led (O)ff, led (B)link, ",choice);
            printf("(S)witch, delay (+),(-)\r\n",0);
         }
      }

      /* Button action fast blink */
 	  if(PORTC.7) speed = period; else speed = 10;
	  
      /* blink the led with different period */
      if( blink )
        {  
          delay10(speed);
          PORTC.0 = 1; /* PORTC pin 0 "1" */
          delay10(speed);
          PORTC.0 = 0; /* PORTC pin 0 "0" */
        }

   }

}




/* *********************************** */
/*            FUNCTIONS                */
/* *********************************** */

void delay10( char n)
/*
  Delays a multiple of 10 milliseconds using the TMR0 timer
  Clock : 4 MHz   => period T = 0.25 microseconds
  1 IS = 1 Instruction Cycle = 1 microsecond
  error: 0.16 percent
*/
{
    char i;

    OPTION = 7;
    do  {
          i = TMR0 + 39; /* 256 microsec * 39 = 10 ms */
          while ( i != TMR0)
            ;
        } while ( --n > 0);
}


void init_serial( void )  /* initialise PIC16F690 bitbang serialcom */
{
   ANSEL.0 = 0; /* No AD on RA0             */
   ANSEL.1 = 0; /* No AD on RA1             */
   PORTA.0 = 1; /* marking line             */
   TRISA.0 = 0; /* output to PK2 UART-tool  */
   TRISA.1 = 1; /* input from PK2 UART-tool */
   return;      
}



void putchar( char ch )  /* sends one char */
{
  char bitCount, ti;
  PORTA.0 = 0; /* set startbit */
  for ( bitCount = 10; bitCount > 0 ; bitCount-- )
   {
     /* delay one bit 104 usec at 4 MHz       */
     /* 5+18*5-1+1+9=104 without optimization */ 
     ti = 18; do ; while( --ti > 0); nop(); 
     Carry = 1;     /* stopbit                    */
     ch = rr( ch ); /* Rotate Right through Carry */
     PORTA.0 = Carry;
   }
  return;
}



void printf(const char *string, char variable) // printf look-alike
{
  char i, k, m, a, b;
  for(i = 0 ; ; i++)
   {
     k = string[i];
     if( k == '\0') break;   // at end of string

     if( k == '%')           // insert variable in string
      {
        i++;
        k = string[i];
        switch(k)
         {
           case 'd':         // %d  signed 8bit
             if( variable.7 ==1) putchar('-');
             else putchar(' ');
             if( variable > 127) variable = -variable;  // no break!
           case 'u':         // %u unsigned 8bit
             a = variable/100;
             putchar('0'+a); // print 100's
             b = variable%100;
             a = b/10;
             putchar('0'+a); // print 10's
             a = b%10;
             putchar('0'+a); // print 1's
             break;
           case 'x':         // %x HEX 8 bit
             static const char Hex_table[16] = "0123456789ABCDEF" ;
             a = swap(variable);
             a = a & 0b0000.1111;
             b = Hex_table[a];
             putchar(b);
             a = variable & 0b0000.1111;
             b = Hex_table[a];
             putchar(b);
             break;
           case 'b':         // %b BINARY 8bit
             for( m = 0 ; m < 8 ; m++ )
              {
                if (variable.7 == 1) putchar('1');
                else putchar('0');
                variable = rl(variable);
              }
             break;
           case 'c':         // %c  'char'
             putchar(variable);
             break;
           case '%':
             putchar('%');
             break;
           default:          // not implemented
             putchar('!');
         }
       }
      else putchar(k);
   }

}







/* *********************************** */
/*            HARDWARE                 */
/* *********************************** */

/*
  Serial communication with PK2 UART-tool
  or used with TTL to USB Serial Converter
             _____________  _____________ 
            |             \/             |
      +5V---|Vdd        16F690        Vss|---Gnd
            |RA5            RA0/AN0/(PGD)|bbTx->- PK2 UART-tool
            |RA4/AN3            RA1/(PGC)|bbRx-<- PK2 UART-tool
            |RA3/!MCLR/(Vpp)  RA2/AN2/INT|
            |RC5/CCP                  RC0|->-LED0
            |RC4                      RC1|
            |RC3/AN7                  RC2|
   PullUp   |RC6/AN8             AN10/RB4|
   Butt_n->-|RC7/AN9               RB5/Rx|
            |RB7/Tx                   RB6|
            |____________________________|
			
  UART RB7, RB6 not used by this program		
 
  TTL to USB Serial Converter if used with Frizing serial monitor: 
                 FTDI TTL_232R-5V
          unconnected --- 6 RTS# green
  bbTx->- 1k resistor ->- 5 rxd  yellow TTL_232R-5V
  bbRx-<- 1k resistor -<- 4 txd  orange TTL_232R-5V		
          unconnected --- 3 VCC  red
          unconnected --- 2 CTS# brown
                  Gnd --- 1 GND  black					
*/
