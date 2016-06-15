/*
 * Author: Borislav Sapundzhiev 
 * Adapted from code by Jim Lindblom, Nathan Seidle and mish-mashed with
 * code from the ColorLCDShield.
 * License: Officially, the MIT License. Review the included License.md file
 * Unofficially, Beerware. Feel free to use, reuse, and modify this
 * code as you see fit. If you find it useful, and we meet someday,
 * you can buy me a beer.
 */

/*
Hardware: (Note most of these pins can be swapped)
    Graphic LCD Pin ---------- Arduino Pin
       1-VCC       ----------------  5V
       2-GND       ----------------  GND
       3-SCE       ----------------  7
       4-RST       ----------------  6
       5-D/C       ----------------  5
       6-DN(MOSI)  ----------------  11
       7-SCLK      ----------------  13
       8-LED       - 330 Ohm res --  9
*/

#include <Arduino.h>
#include "PCD8544.h"
//#include "PCD8544_fb.h"

#define PIN_SCE     7  // LCD CS  .... Pin 3
#define PIN_RESET   6  // LCD RST .... Pin 1
#define PIN_DC      5  // LCD Dat/Com. Pin 5
#define PIN_SDIN    11 //4  // LCD SPIDat . Pin 6
#define PIN_SCLK    13 //3  // LCD SPIClk . Pin 4
#define PIN_BLIGHT  9  //Back light


PCD8544 lcd(PIN_SCE, PIN_RESET,PIN_DC,PIN_SDIN,PIN_SCLK,PIN_BLIGHT);
//PCD8544_fb lcd(PIN_SCE, PIN_RESET,PIN_DC,PIN_SDIN,PIN_SCLK,PIN_BLIGHT);
int count;
void setup(void)
{
  lcd.begin();
}

#if 0
void testLineFrameBuff() {

   int x0 = LCD_WIDTH / 2;
   int y0 = LCD_HEIGHT / 2;

   lcd.updateDisplay();
   delay(1000);
   lcd.clearDisplay(WHITE);
  
  for (float i=0; i<2*PI; i+=PI/8)
  {
    // Time to whip out some maths:
    const int lineLength = 24;
    int x1 = x0 + lineLength * sin(i);
    int y1 = y0 + lineLength * cos(i);
    
    // setLine(x0, y0, x1, y1, bw) takes five variables. The
    // first four are coordinates for the start and end of the 
    // line. The last variable is the color (1=black, 0=white).
    lcd.setLine(x0, y0, x1, y1, BLACK);
    lcd.updateDisplay();
    delay(100);
  }
}
#endif

void loop(void)
{
  /*for(int x =0; x < LCD_WIDTH; x++)
  {
    lcd.drawPX(x,0);
  } */
  count++;
  lcd.plotRect(0,0, LCD_WIDTH-1, LCD_HEIGHT-1);
  
  //testLineFrameBuff();
  lcd.gotoXY(4,1);
  lcd.print("Hello world");
  //lcd.LcdWrite(LCD_D,0xff);
  lcd.charToXY('e', 4, 2 , (count %2) ? WHITE : BLACK);
  delay(5000);
}

