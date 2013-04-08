#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
/* HD44780 LCD routine protoypes */
// PORTB is data and control lines
// PB0:3 -> LCD D4-7
// PB4   -> LCD RS
// PB5   -> LCD E

void lcd_clock_nibble(char cmd, int cmd_or_data) {
  if (cmd_or_data == RS_COMMAND) {
    PORTB &= ~(1 << 4);  // Bring RS low
  } else {
    PORTB |= (1 << 4);  // Bring RS low
  }
  PORTB = (PORTB & 0x30) | (cmd & 0x0F);  // Leave control lines as-is, load low nibble of command byte
  _delay_ms(1);
  PORTB |= (1 << 5);  // Bring E high
  _delay_ms(1);
  PORTB &= ~(1 << 5);  // Bring E low
  _delay_ms(1);
}

void lcd_cmd(char cmd) {
  lcd_clock_nibble((cmd >> 4) & 0x0F, RS_COMMAND);
  lcd_clock_nibble(cmd & 0x0F, RS_COMMAND);
}

void lcd_data(char data) {
  lcd_clock_nibble((data >> 4) & 0x0F, RS_DATA);
  lcd_clock_nibble(data & 0x0F, RS_DATA);
}

void lcd_home() {
  lcd_cmd(CMD_CURSOR_HOME);
}

void lcd_clear() {
  lcd_cmd(CMD_CLEAR_DISPLAY);
}

void lcd_on() {
  lcd_cmd(CMD_DISPLAY_CTRL | DISPLAY_ON | CURSOR_ON | BLINK_ON);
}

void lcd_init() {
  // Set up the port
  DDRB = 0xFF;

  // Delay 30ms to wait for LCD powerup
  _delay_ms(30);
  
  PORTB = 0;          // Bring all control lines low

  lcd_cmd(CMD_FUNCTION_SET | INTERFACE_4BIT | LINES_2 | FONT_5X8); // 4 bits, 2 lines
  _delay_ms(5);

  lcd_cmd(CMD_DISPLAY_SHIFT | MOVE_CURSOR | RIGHT);    // cursor move, right
  _delay_ms(5);
  lcd_cmd(CMD_ENTRY_MODE | INCREMENT | NO_SHIFT);    // don't shift display
  _delay_ms(5);
  lcd_clear();
  _delay_ms(5);
  lcd_on();
}

void lcd_write(char c) {
  lcd_data(c);
}

void lcd_moveto(int x, int y) {
  char addr = 0x80;
  addr += (y > 0 ? 0x40 : 0);
  addr += x;

  lcd_cmd(addr);
}
