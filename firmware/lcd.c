#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
/* HD44780 LCD routine protoypes */
// PORTB is data and control lines
// PB0:3 -> LCD D4-7
// PB4   -> LCD RS
// PB5   -> LCD E

#define DELAY_MULT 1

void lcd_clock_byte(char cmd, int cmd_or_data) {
  PORTB &= ~(1 << 5);  // Bring E low
  if (cmd_or_data == RS_COMMAND) {
    PORTB &= ~(1 << 6);  // Bring RS low
  } else {
    PORTB |= (1 << 6);  // Bring RS low
  }
  PORTB = (PORTB & 0b00110000) | (cmd & 0x0F);  // Leave control lines as-is, load low nibble of command byte
  PORTB |= (1 << 5);  // Bring E high
}

void lcd_raw_cmd(char cmd) {
  lcd_clock_byte(cmd, RS_COMMAND);
  _delay_us(300*DELAY_MULT);
}

void lcd_cmd(char cmd) {
  lcd_clock_byte((cmd >> 4) & 0x0F, RS_COMMAND);
  _delay_us(300*DELAY_MULT);
  lcd_clock_byte(cmd & 0x0F, RS_COMMAND);
  _delay_us(300*DELAY_MULT);
}

void lcd_data(char data) {
  lcd_clock_byte(data, RS_DATA);
  _delay_us(300*DELAY_MULT);
}


void lcd_clear() {
  lcd_cmd(0x01);
}

void lcd_on() {
  lcd_cmd(0x0C);
}

void lcd_init() {
  // Set up the port
  DDRB |= 0b00111111;

  // Delay 20ms to wait for LCD powerup
  _delay_ms(20*DELAY_MULT);   // 20ms
  
  PORTB = 0;          // Bring all control lines low

  lcd_raw_cmd(0x03);
  _delay_us(4800*DELAY_MULT);

  lcd_raw_cmd(0x03);
  lcd_raw_cmd(0x03);
  lcd_raw_cmd(0x02);
  _delay_us(4800*DELAY_MULT);


  lcd_cmd(0x28);    // 4 bits, 2 lines
  lcd_cmd(0x08);    // Don't shift display, hide cursor
  
  lcd_clear();

  lcd_cmd(0x06);    // Move cursor right
  
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
