/*
 * File:   main.c
 * Author: user
 * Created on 2014. február 26., 9:24
 */

#include <p30Fxxxx.h>      /* Device header file                              */
#include <stdio.h>
#include <stdlib.h>
#include "picture.h"
//#include "main.h"

//__psv__ const unsigned int* SPR;
unsigned int cVariable;
extern void w1usec(void);
extern void w250nsec(void);
extern void outline(void);
extern void outframe(void);
extern void wait32usec(void);

/* Enables HS oscillator div 2, and PLL 16 (80Mhz)
 TCY (instruction cycle = FOSC / 4
 FOSC = 20MHz  TOSC = 50nsec  */
_FOSC(HS2_PLL16 & CSW_FSCM_OFF);
_FBORPOR(PWRT_OFF & BORV27 & PBOR_OFF & MCLR_EN & RST_IOPIN); /* Ext MCLR, no
                                                               * brownout */
_FWDT(WDT_OFF); /* Turns off watchdog timer */

void InitIOPorts()
{
  /* ADPCFG: A/D Port Configuration Register *
    * PCFG<15:0>: Analog Input Pin Configuration Control bits
    * 1 = Analog input pin in Digital mode, port read input enabled, A/D input multiplexer input connected to AVSS
    * 0 = Analog input pin in Analog mode, port read input disabled, A/D samples pin voltage */

  ADPCFG = 0b0000000000011110;  // AD 1,2,3,4 leaves digital port
  TRISB = 0b11100001; // B1-2-3-4 outputs.

}

__psv__ unsigned int* SCREEN_POINTER = &SCREEN_BUFFER_02[0];

/*
 * 
 */
int main()
{

  int frame_counter = 0;
  int frame_sec = 0;

  InitIOPorts();
  
  while (1)
    {
    outframe();
    frame_sec = (frame_counter++ / 4);
    if (frame_sec >= 12)
    {
      frame_sec = 0;
      frame_counter = 0;      
    }
      SCREEN_POINTER = &SCREEN_BUFFER_02[305 * frame_sec];
    }
  
  return (EXIT_SUCCESS);
}

