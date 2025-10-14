#ifndef LCD_H_
#define LCD_H_

#include <avr/io.h>
#include <util/delay.h>

// LCD Connection Pins (adjust according to your wiring)
#define LCD_RS_PORT    PORTB
#define LCD_RS_DDR     DDRB  
#define LCD_RS_PIN     PB0

#define LCD_EN_PORT    PORTB
#define LCD_EN_DDR     DDRB
#define LCD_EN_PIN     PB1

#define LCD_DATA_PORT  PORTD
#define LCD_DATA_DDR   DDRD
#define LCD_DATA_PINS  0xF0  // PD4-PD7 for 4-bit mode

// LCD Commands
#define LCD_CLEAR           0x01
#define LCD_HOME            0x02
#define LCD_ENTRY_MODE      0x06
#define LCD_DISPLAY_ON      0x0E
#define LCD_DISPLAY_OFF     0x08
#define LCD_CURSOR_ON       0x0E
#define LCD_CURSOR_OFF      0x0C
#define LCD_CURSOR_BLINK    0x0F
#define LCD_FUNCTION_SET    0x28  // 4-bit mode, 2 lines, 5x8 font
#define LCD_SET_CGRAM       0x40
#define LCD_SET_DDRAM       0x80

// Function prototypes
void lcd_init(void);
void lcd_command(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_string(char *str);
void lcd_clear(void);
void lcd_gotoxy(uint8_t x, uint8_t y);
void lcd_custom_char(uint8_t loc, uint8_t *msg);

#endif /* LCD_H_ */