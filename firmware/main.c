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

  while(1){
    lcd_init();
    c = 65;
    for(y = 0; y < 2; y++) {
      for(x = 0; x < 16; x++) {
        c++;
        if(c > 90)
          c = 65;
        lcd_moveto(x,y);
        lcd_write(c);
        _delay_ms(100);
      }
    }
    _delay_ms(5000);
  }
  return 0;   /* never reached */
}
