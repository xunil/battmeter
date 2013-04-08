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

  lcd_init();
  c = 0x1F;
  while(1){
    for(y = 0; y < 2; y++) {
      c++;
      if(c > 0xFE)
        c = 0x1F;
      for(x = 0; x < 16; x++) {
        lcd_moveto(x,y);
        lcd_write(c);
      }
    }
    //lcd_clear();
    _delay_ms(500);
  }
  return 0;   /* never reached */
}
