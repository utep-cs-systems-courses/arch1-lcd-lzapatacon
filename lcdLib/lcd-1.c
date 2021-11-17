/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;
  clearScreen(COLOR_BLUE);

  short col = 30, row = 30;
  short startc = SHORT_EDGE_PIXELS/2, startr = LONG_EDGE_PIXELS/2, lc = SHORT_EDGE_PIXELS/4;
  int i = 0;
  for(int c = 0; c <= 45; c++)
    {
      drawPixel(startc, startr+c, COLOR_RED);
      drawPixel(startc, startr-c, COLOR_RED);
      drawPixel(startc+c, startr, COLOR_RED);
      drawPixel(startc-c, startr, COLOR_RED);
      drawPixel(startc+c, startr-c, COLOR_RED);
      drawPixel(startc-c, startr+c, COLOR_RED);
      drawPixel(startc-c, startr-c, COLOR_RED);
      drawPixel(startc+c, startr+c, COLOR_RED);
      drawPixel(startc+c, startr-i, COLOR_RED);
    }
  int c = 0;
  for(int k = 0; k <= 45; k+=2)
    {
      drawPixel(startc+c, startr-k, COLOR_RED);
      drawPixel(startc-c, startr+k, COLOR_RED);
      drawPixel(startc-c, startr-k, COLOR_RED);
      drawPixel(startc+c, startr+k, COLOR_RED);
      drawPixel(startc+k, startr-c, COLOR_RED);
      drawPixel(startc-k, startr+c, COLOR_RED);
      drawPixel(startc-k, startr-c, COLOR_RED);
      drawPixel(startc+k, startr+c, COLOR_RED);
      c+=1;
    }
  //Makes a filled in diamond
  /*
  for(int append = 0; append <= 30; append++)
    {
      for(int j = 0;j <= 30-append; j++)
	{
	  drawPixel(startc-j, startr-append,COLOR_RED);
	  drawPixel(startc+j, startr-append,COLOR_RED);
	  drawPixel(startc-j, startr+append,COLOR_RED);
	  drawPixel(startc+j, startr+append,COLOR_RED);
	}
	}*/
  /*For loop to make filled hourglass
  for(int c = 0; c <= 60; c++)
    {
      for(int j = c; j <= 30;j++)
	{
	  drawPixel(startc+j, startr-c, COLOR_RED);
	  drawPixel(startc+j, startr+c, COLOR_RED);
	  drawPixel(startc-j, startr+c, COLOR_RED);
	  drawPixel(startc-j, startr-c, COLOR_RED);
	 
	}
      drawPixel(lc2, startr+30, COLOR_RED);
      }*/
    /*  for(col = 0; col < 30;)
    {
      row = col;
      short LE = -col;
      short RE = col;
      for (short c = LE; c <= RE; c++)
	drawPixel(startc+c, startr+row, COLOR_PINK);
      //    drawPixel(startc+RE, startr+row, COLOR_PINK);
      col += 1;
      }*/

  //drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  
}
