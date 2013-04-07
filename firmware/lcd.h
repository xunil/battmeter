/* HD44780 LCD routine protoypes */
void lcd_clock_byte(char cmd, int cmd_or_data);
void lcd_raw_cmd(char cmd);
void lcd_cmd(char cmd);
void lcd_data(char data);
void lcd_delay(int us);
void lcd_clear();
void lcd_on();
void lcd_init();
void lcd_write(char c);
void lcd_moveto(int x, int y);

#define RS_COMMAND 0
#define RS_DATA 1
