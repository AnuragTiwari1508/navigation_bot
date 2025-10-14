#include "lcd.h"

// Enable pulse for LCD
static void lcd_enable_pulse(void) {
    LCD_EN_PORT |= (1 << LCD_EN_PIN);   // Set EN high
    _delay_us(1);                       // Minimum enable pulse width
    LCD_EN_PORT &= ~(1 << LCD_EN_PIN);  // Set EN low
    _delay_us(50);                      // Command execution time
}

// Send 4 bits to LCD
static void lcd_send_nibble(uint8_t nibble) {
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (nibble & 0xF0);
    lcd_enable_pulse();
}

// Send command to LCD
void lcd_command(uint8_t cmd) {
    LCD_RS_PORT &= ~(1 << LCD_RS_PIN);  // RS = 0 for command
    
    lcd_send_nibble(cmd);               // Send upper nibble
    lcd_send_nibble(cmd << 4);          // Send lower nibble
    
    if (cmd == LCD_CLEAR || cmd == LCD_HOME) {
        _delay_ms(2);                   // Clear and home need more time
    } else {
        _delay_us(50);
    }
}

// Send data to LCD
void lcd_data(uint8_t data) {
    LCD_RS_PORT |= (1 << LCD_RS_PIN);   // RS = 1 for data
    
    lcd_send_nibble(data);              // Send upper nibble
    lcd_send_nibble(data << 4);         // Send lower nibble
    
    _delay_us(50);
}

// Initialize LCD in 4-bit mode
void lcd_init(void) {
    // Set pins as output
    LCD_RS_DDR |= (1 << LCD_RS_PIN);
    LCD_EN_DDR |= (1 << LCD_EN_PIN);
    LCD_DATA_DDR |= LCD_DATA_PINS;
    
    // Initialize pins to low
    LCD_RS_PORT &= ~(1 << LCD_RS_PIN);
    LCD_EN_PORT &= ~(1 << LCD_EN_PIN);
    LCD_DATA_PORT &= ~LCD_DATA_PINS;
    
    _delay_ms(50);  // Wait for LCD to power up
    
    // Initialize LCD in 4-bit mode (special sequence)
    lcd_send_nibble(0x30);
    _delay_ms(5);
    
    lcd_send_nibble(0x30);
    _delay_us(150);
    
    lcd_send_nibble(0x30);
    _delay_us(150);
    
    lcd_send_nibble(0x20);  // Set 4-bit mode
    _delay_us(150);
    
    // Function set: 4-bit mode, 2 lines, 5x8 font
    lcd_command(LCD_FUNCTION_SET);
    
    // Display off
    lcd_command(LCD_DISPLAY_OFF);
    
    // Clear display
    lcd_command(LCD_CLEAR);
    
    // Entry mode: increment cursor, no shift
    lcd_command(LCD_ENTRY_MODE);
    
    // Display on, cursor off, blink off
    lcd_command(LCD_CURSOR_OFF);
}

// Send string to LCD
void lcd_string(char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

// Clear LCD
void lcd_clear(void) {
    lcd_command(LCD_CLEAR);
    _delay_ms(2);
}

// Set cursor position (x: 0-15, y: 0-1)
void lcd_gotoxy(uint8_t x, uint8_t y) {
    uint8_t address;
    
    if (y == 0) {
        address = LCD_SET_DDRAM + x;
    } else {
        address = LCD_SET_DDRAM + 0x40 + x;
    }
    
    lcd_command(address);
}

// Create custom character (loc: 0-7, msg: 8 bytes pattern)
void lcd_custom_char(uint8_t loc, uint8_t *msg) {
    uint8_t i;
    
    if (loc < 8) {
        lcd_command(LCD_SET_CGRAM + (loc * 8));
        for (i = 0; i < 8; i++) {
            lcd_data(msg[i]);
        }
        lcd_command(LCD_SET_DDRAM);  // Return to DDRAM
    }
}