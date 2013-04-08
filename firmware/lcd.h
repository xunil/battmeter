/* HD44780 LCD routine protoypes */
void lcd_clock_nibble(char cmd, int cmd_or_data);
void lcd_cmd(char cmd);
void lcd_data(char data);
void lcd_delay(int us);
void lcd_clear();
void lcd_on();
void lcd_home();
void lcd_init();
void lcd_write(char c);
void lcd_moveto(int x, int y);

#define RS_COMMAND 0
#define RS_DATA 1
/* B7 B6 B5 B4 B3 B2 B1 B0 */
#define CMD_CLEAR_DISPLAY 0x01
#define CMD_CURSOR_HOME 0x02
/*  0  0  0  0  0  1 I/D S; I/D: 0=increment cursor pos, 1=decrement; S: 0=no display shift, 1=shift */
#define CMD_ENTRY_MODE 0x04
#define INCREMENT 0x02
#define DECREMENT 0x00
#define SHIFT 0x01
#define NO_SHIFT 0x00
/*  0  0  0  0  1  D  C  B; D: display on(1)/off(0); C: cursor on(1)/off(0); B: cursor blink on(1)/off(0) */
#define CMD_DISPLAY_CTRL 0x08
#define DISPLAY_ON   0x04
#define DISPLAY_OFF  0x00
#define CURSOR_ON    0x02
#define CURSOR_OFF   0x00
#define BLINK_ON     0x01
#define BLINK_OFF    0x00
/*  0  0  0  1 S/C R/L * *; S/C: 0=move cursor, 1=shift display; R/L: shift right(1)/left(0) */
#define CMD_DISPLAY_SHIFT 0x0F
#define SHIFT_DISPLAY 0x08
#define MOVE_CURSOR 0x00
#define RIGHT 0x04
#define LEFT 0x00
/*  0  0  1 DL  N  F  *  *; DL: 4-bit(0)/8-bit(1) interface; N: 1 line(0)/2 lines(1); F: 5x8(0)/5x10(1) font */
#define CMD_FUNCTION_SET 0x20
#define INTERFACE_4BIT 0x00
#define INTERFACE_8BIT 0x0F
#define LINES_1 0x00
#define LINES_2 0x08
#define FONT_5X8 0x00
#define FONT_5X10 0x04

