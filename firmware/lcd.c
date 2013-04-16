#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
/* HD44780 LCD routine protoypes */
// PORTB is data and control lines
// PB0:3 -> LCD D4-7
// PB4   -> LCD RS
// PB5   -> LCD E

#define CLOCK_DELAY_US 200

void lcd_clock_nibble(char cmd, int cmd_or_data) {
  if (cmd_or_data == RS_COMMAND) {
    PORTB &= ~(1 << 4);  // Bring RS low
  } else {
    PORTB |= (1 << 4);  // Bring RS high
  }
  PORTB = (PORTB & 0x30) | (cmd & 0x0F);  // Leave control lines as-is, load low nibble of command byte
  _delay_us(CLOCK_DELAY_US);
  PORTB |= (1 << 5);  // Bring E high
  _delay_us(CLOCK_DELAY_US);
  PORTB &= ~(1 << 5);  // Bring E low
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
  lcd_cmd(CMD_DISPLAY_CTRL | DISPLAY_ON | CURSOR_OFF | BLINK_OFF);
}

void lcd_init() {
  DDRB = 0xFF;
  _delay_ms(30);      // Delay 30ms to wait for LCD powerup
  PORTB = 0;          // Bring all control lines low
  lcd_cmd(CMD_FUNCTION_SET | INTERFACE_4BIT | LINES_2 | FONT_5X8);
  _delay_us(350);     // Give the HD44780 a moment to settle

  lcd_cmd(CMD_DISPLAY_SHIFT | MOVE_CURSOR | RIGHT);
  lcd_cmd(CMD_ENTRY_MODE | INCREMENT | NO_SHIFT);
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

void lcd_custom_char(int n, char *pattern) {
  int i;
  lcd_cmd(0x40+n);
  for(i=0; i<8; i++) {
    lcd_data(pattern[i]);
  }
}
