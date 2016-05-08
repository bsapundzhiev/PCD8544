/*
 * Author: Borislav Sapundzhiev 
 * Adapted from code by Jim Lindblom, Nathan Seidle and mish-mashed with
 * code from the ColorLCDShield.
 * License: Officially, the MIT License. Review the included License.md file
 * Unofficially, Beerware. Feel free to use, reuse, and modify this
 * code as you see fit. If you find it useful, and we meet someday,
 * you can buy me a beer.
 */
#include "PCD8544.h"
#include "PCD8544_fb.h"

PCD8544_fb::PCD8544_fb(int sce, int rst, int dc, int sdin, int sclk, int bl):
PCD8544(sce, rst, dc, sdin,sclk, bl)
{}

//Frame buffer methods
void PCD8544_fb::setPixel(int x, int y, boolean bw)
{
  // First, double check that the coordinate is in range.
  if ((x >= 0) && (x < LCD_WIDTH) && (y >= 0) && (y < LCD_HEIGHT))
  {
    byte shift = y % 8;

    if (bw) // If black, set the bit.
      displayMap[x + (y/8)*LCD_WIDTH] |= 1<<shift;
    else   // If white clear the bit.
      displayMap[x + (y/8)*LCD_WIDTH] &= ~(1<<shift);
  }
}

// setLine draws a line from x0,y0 to x1,y1 with the set color.
// This function was grabbed from the SparkFun ColorLCDShield
// library.
void PCD8544_fb::setLine(int x0, int y0, int x1, int y1, boolean bw)
{
  int dy = y1 - y0; // Difference between y0 and y1
  int dx = x1 - x0; // Difference between x0 and x1
  int stepx, stepy;

  if (dy < 0)
  {
    dy = -dy;
    stepy = -1;
  }
  else
    stepy = 1;

  if (dx < 0)
  {
    dx = -dx;
    stepx = -1;
  }
  else
    stepx = 1;

  dy <<= 1; // dy is now 2*dy
  dx <<= 1; // dx is now 2*dx
  setPixel(x0, y0, bw); // Draw the first pixel.

  if (dx > dy)
  {
    int fraction = dy - (dx >> 1);
    while (x0 != x1)
    {
      if (fraction >= 0)
      {
        y0 += stepy;
        fraction -= dx;
      }
      x0 += stepx;
      fraction += dy;
      setPixel(x0, y0, bw);
    }
  }
  else
  {
    int fraction = dx - (dy >> 1);
    while (y0 != y1)
    {
      if (fraction >= 0)
      {
        x0 += stepx;
        fraction -= dy;
      }
      y0 += stepy;
      fraction += dx;
      setPixel(x0, y0, bw);
    }
  }
}

// setRect will draw a rectangle from x0,y0 top-left corner to
// a x1,y1 bottom-right corner. Can be filled with the fill
// parameter, and colored with bw.
// This function was grabbed from the SparkFun ColorLCDShield
// library.
void PCD8544_fb::setRect(int x0, int y0, int x1, int y1, boolean fill, boolean bw)
{
  // check if the rectangle is to be filled
  if (fill == 1)
  {
    int xDiff;

    if(x0 > x1)
      xDiff = x0 - x1; //Find the difference between the x vars
    else
      xDiff = x1 - x0;

    while(xDiff > 0)
    {
      setLine(x0, y0, x0, y1, bw);

      if(x0 > x1)
        x0--;
      else
        x0++;

      xDiff--;
    }
  }
  else
  {
    // best way to draw an unfilled rectangle is to draw four lines
    setLine(x0, y0, x1, y0, bw);
    setLine(x0, y1, x1, y1, bw);
    setLine(x0, y0, x0, y1, bw);
    setLine(x1, y0, x1, y1, bw);
  }
}

// This will actually draw on the display, whatever is currently
// in the displayMap array.
void PCD8544_fb::updateDisplay()
{
  gotoXY(0, 0);
  for (int i=0; i < (LCD_WIDTH * LCD_HEIGHT / 8); i++)
  {
    LcdWrite(LCD_DATA, displayMap[i]);
  }
}

// This function clears the entire display either white (0) or
// black (1).
// The screen won't actually clear until you call updateDisplay()!
void PCD8544_fb::clearDisplay(boolean bw)
{
  for (int i=0; i<(LCD_WIDTH * LCD_HEIGHT / 8); i++)
  {
    if (bw)
      displayMap[i] = 0xFF;
    else
      displayMap[i] = 0;
  }
}

