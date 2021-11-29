#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buzzer.h"
#include "song.h"

// WARNING: LCD DISPLAY USES P1.0.  Do not touch!!! 

#define LED BIT6		/* note that bit zero req'd for display */

#define SW1 1
#define SW2 2
#define SW3 4
#define SW4 8

#define SWITCHES 15

#define s_state 1;
#define period 1;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
}

int switches = 0;

void
switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switches = ~p2val & SWITCHES;
}


// axis zero for col, axis 1 for row
short drawPos[2] = {10,10}, controlPos[2] = {10,10};
short velocity[2] = {3,8}, limits[2] = {screenWidth-36, screenHeight-8};

short redrawScreen = 1;
u_int controlFontColor = COLOR_GREEN;

void wdt_c_handler()
{
  static int secCount = 0;

  secCount ++;
  if (secCount >= 25) {		/* 10/sec */
    secCount = 0;
    redrawScreen = 1;
  }
}
  
void update_shape();

void main()
{
  
  P1DIR |= LED;		/**< Green led on when CPU on */
  P1OUT |= LED;
  configureClocks();
  lcd_init();
  switch_init();
  
  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */
  
  clearScreen(COLOR_RED);
  while (1) {			/* forever */
    /*if (redrawScreen) {
      redrawScreen = 0;
      
      update_shape();
      }*/
    update_shape();
    P1OUT &= ~LED;	/* led off */
    //or_sr(0x10);	/**< CPU OFF */
    P1OUT |= LED;	/* led on */
  }
}

    
    
void
update_shape()
{
  static unsigned char row = (screenHeight / 2), col = (screenWidth / 2);
  static char blue = 31, green = 0, red = 31;
  static unsigned char step = 0;
  if (step <= 30) {
    int startCol = (col - step);
    int endCol = (col + step);
    int width = 1 + endCol - startCol;
    // a color in this BGR encoding is BBBB BGGG GGGR RRRR
    
    unsigned int color = COLOR_RED;
    unsigned int color2 = COLOR_BLACK;
    if (switches & SW4)
      {
	clearScreen(COLOR_BLACK);
     
      }
    /*if(switches && SW1)
      {
	clearScreen(COLOR_RED);
	color = COLOR_BLACK;
	color2 = COLOR_RED;	
      }*/
    for (int i = 0; i < 30 - step; i++)
      {
	drawPixel(startCol-i, row-step, color);
	drawPixel(startCol+i, row-step, color);
	drawPixel(startCol-i, row+step, color);
	drawPixel(startCol+i, row+step, color);
	drawPixel(endCol-i, row-step, color);
	drawPixel(endCol+i, row-step, color);
	drawPixel(endCol-i, row+step, color);
	drawPixel(endCol+i, row+step, color);
      }
    //fillRectangle(startCol, row, width, 1, color);
    //fillRectangle(startCol, row+step, width, 1, color);
    if (switches & SW2)
      {
	drawVerString11x16(35, 20, "Black",COLOR_RED,COLOR_BLACK);
	song();
      }
    if (switches & SW3)
      {
	drawVerString11x16(35,130,"Widow",COLOR_RED,COLOR_BLACK);
      }
    step ++;
  } else {
     step = 0;
  }
}

/* Switch on S2 */
void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if (P2IFG & SWITCHES) {	      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;		      /* clear pending sw interrupts */
    switch_interrupt_handler();	/* single handler for all switches */
  }
}
