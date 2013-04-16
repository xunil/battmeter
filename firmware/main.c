/* Name: main.c
 * Author: Robert Liesenfeld
 * License: MIT
 */

#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
  int x, y;
  char c;
  char custom_char[] = {0x01, 0x03, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x1F};

  lcd_init();
  lcd_on();
  c = 0x1F;

  lcd_custom_char(0, custom_char);
  while(1){
    for(y = 0; y < 2; y++) {
      c++;
      if(c > 0xFE)
        c = 0x1F;
      for(x = 0; x < 16; x++) {
        lcd_moveto(x,y);
        //lcd_write(c);
        lcd_write(0x00);
      }
    }
    //lcd_clear();
    _delay_ms(500);
  }
  return 0;   /* never reached */
}
