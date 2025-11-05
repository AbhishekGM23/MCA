/********************************************************
 * Program       : LED Counter Display on LCD
 * Description   : Counts LED blinks on Port 1 (P1.24–P1.31) 
 *                 and simultaneously displays the count value
 *                 on an LCD using a 4-bit interface.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 Evaluation Board
 * Processor     : LPC2148
 * Notes         : Demonstrates GPIO output control, LCD interfacing,
 *                 and timer-based delay for visible counting.
 ********************************************************/

#include <LPC214x.h>
#include <stdio.h>

// Bit mask for LEDs connected to P1.24 - P1.31
#define LED_MASK 0xFF000000  

// LCD pin connections on PORT0
#define RS (1 << 8) // Register Select
#define EN (1 << 9) // Enable
#define D4 (1 << 4) // Data pin 4
#define D5 (1 << 5) // Data pin 5
#define D6 (1 << 6) // Data pin 6
#define D7 (1 << 7) // Data pin 7

// Function declarations
void pll_init(void);
void delay_ms(unsigned int);
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_init(void);
void lcd_string(char *);
void lcd_nibble_write(unsigned char);

// PLL (Phase Locked Loop) Initialization for system clock
void pll_init(void) {
    PLL0CON = 1; // Enable PLL
    PLL0CFG = 0x24; // Multiplier and divider values
    PLL0FEED = 0xAA; PLL0FEED = 0x55;
    PLL0CON = 3; // Connect PLL
    PLL0FEED = 0xAA; PLL0FEED = 0x55;
    VPBDIV = 0x02; // Set peripheral clock (PCLK = 15 MHz)
}

// Millisecond delay using Timer0
void delay_ms(unsigned int ms) {
    T0TCR = 0x02; // Reset timer
    T0PR = 15000 - 1; // Prescaler for 1 ms tick (15 MHz PCLK)
    T0TC = 0; // Clear timer counter
    T0TCR = 0x01; // Start timer
    while (T0TC < ms); // Wait until desired time elapsed
    T0TCR = 0; // Stop timer
}

// Low-level LCD nibble write function (4-bit mode)
void lcd_nibble_write(unsigned char nibble) {
    IOCLR0 = (D4 | D5 | D6 | D7); // Clear all data bits
    if (nibble & 1) IOSET0 |= D4; // Set corresponding bits
    if (nibble & 2) IOSET0 |= D5;
    if (nibble & 4) IOSET0 |= D6;
    if (nibble & 8) IOSET0 |= D7;

    IOSET0 = EN; // Pulse enable pin
    delay_ms(2);
    IOCLR0 = EN;
}

// Send command to LCD
void lcd_command(unsigned char cmd) {
    IOCLR0 = RS; // RS = 0 for command mode
    lcd_nibble_write(cmd >> 4); // Send high nibble
    lcd_nibble_write(cmd & 0x0F); // Send low nibble
}

// Send data (character) to LCD
void lcd_data(unsigned char data) {
    IOSET0 = RS; // RS = 1 for data mode
    lcd_nibble_write(data >> 4); // High nibble
    lcd_nibble_write(data & 0x0F); // Low nibble
}

// Initialize LCD in 4-bit mode
void lcd_init(void) {
    IODIR0 |= RS | EN | D4 | D5 | D6 | D7; // LCD pins as outputs
    delay_ms(20); // Allow LCD power-on delay

    lcd_command(0x02); // 4-bit mode initialization
    lcd_command(0x28); // 2 lines, 5x8 font
    lcd_command(0x0C); // Display ON, cursor OFF
    lcd_command(0x01); // Clear display
}

// Display string on LCD
void lcd_string(char *str) {
    while (*str) lcd_data(*str++); // Send each character
}

// Main program
int main(void) {
    int j;
    unsigned int count = 0;
    char buffer[16];

    pll_init(); // Initialize PLL and clocks
    lcd_init(); // Initialize LCD

    PINSEL2 = 0;                    // Configure P1.24–P1.31 as GPIO
    IODIR1 |= LED_MASK; // Set LED pins as outputs

    lcd_string("LED Counter:"); // Display title on first LCD line

    while (1) {
        for (j = 24; j < 32; j++) { // Loop through 8 LED pins
            IOSET1 = (1 << j); // Turn ON LED
            delay_ms(300); // Wait 300 ms
            IOCLR1 = (1 << j); // Turn OFF LED
            delay_ms(300); // Wait 300 ms

            count++; // Increment count variable

            lcd_command(0xC0); // Move cursor to 2nd line
            sprintf(buffer, "Count: %u   ", count); // Convert to string
            lcd_string(buffer); // Display count on LCD
        }
    }
}
