//Displays a countdown from 20

#include <LPC214x.h> // LPC214x register definitions

// Pin definitions for LCD connections
#define RS (1<<16) // Register Select
#define RW (1<<17) // Read/Write
#define EN (1<<18) // Enable
#define LCD_DATA_MASK (0xFFu << 24) // Data lines D0–D7 on P1.24–P1.31

void pll_init(void);
void delay_ms(unsigned int ms);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_str(const char *str);
void lcd_num(int num);

// Initialize PLL for 60 MHz CPU clock
void pll_init(void) {
    PLL0CON = 0x01; // Enable PLL
    PLL0CFG = 0x24; // M=5, P=2 (12 MHz * 5 = 60 MHz)
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;
    while (!(PLL0STAT & (1<<10))); // Wait for lock
    PLL0CON = 0x03; // Connect PLL
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;
}

// Software delay in milliseconds (approximate)
void delay_ms(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms * 1000; i++);
}

// Send command byte to LCD
void lcd_cmd(unsigned char cmd) {
    IO1CLR = RS | RW | EN | LCD_DATA_MASK; // Clear LCD pins
    IO1SET = ((cmd << 24) & LCD_DATA_MASK); // Send command bits
    IO1CLR = RS; // RS=0 for command
    IO1CLR = RW; // RW=0 for write
    IO1SET = EN; // EN=1 to latch
    delay_ms(2);
    IO1CLR = EN; // EN=0 to complete cycle
}

// Send single data character to LCD
void lcd_data(unsigned char data) {
    IO1CLR = RS | RW | EN | LCD_DATA_MASK; // Clear lines
    IO1SET = ((data << 24) & LCD_DATA_MASK); // Put data on bus
    IO1SET = RS; // RS=1 for data mode
    IO1CLR = RW; // RW=0 for write
    IO1SET = EN; // EN=1 to latch
    delay_ms(2);
    IO1CLR = EN; // Disable EN
}

// Initialize LCD in 8-bit, 2-line mode
void lcd_init(void) {
    IO1DIR |= RS | RW | EN | LCD_DATA_MASK; // Set control + data pins as output
    delay_ms(20);
    lcd_cmd(0x38); // 8-bit, 2-line, 5x7 format
    lcd_cmd(0x0C); // Display ON, cursor OFF
    lcd_cmd(0x06); // Auto-increment cursor
    lcd_cmd(0x01); // Clear display
    delay_ms(2);
}

// Display a string on LCD
void lcd_str(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

// Display a decimal integer on LCD
void lcd_num(int num) {
    char buf[5];
    int i = 0, j;
    if (num == 0) {
        lcd_data('0');
        return;
    }
    if (num < 0) {
        lcd_data('-');
        num = -num;
    }
    while (num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }
    for (j = i - 1; j >= 0; j--) {
        lcd_data(buf[j]); // Print digits in reverse order
    }
}

int main(void) {
    int count;

    pll_init(); // Configure system clock
    lcd_init(); // Initialize LCD

    // Infinite countdown loop
    while (1) {
        for (count = 20; count >= 0; count--) {
            lcd_cmd(0x01); // Clear the LCD display
            lcd_str("Count: "); // Display label
            lcd_num(count); // Display current count value
            delay_ms(1000); // Wait for ~1 second
        }
    }
}
