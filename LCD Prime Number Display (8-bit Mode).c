/********************************************************
 * Program       : LCD Prime Number Display (8-bit Mode)
 * Description   : Displays successive prime numbers on a 16x2 LCD.
 *                 The microcontroller checks each number sequentially
 *                 and shows the next prime on the display every second.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 Development Board (LPC2148)
 * Processor     : LPC2148 (ARM7TDMI-S Core)
 * Clock         : 60 MHz (via PLL Configuration)
 * Notes         : 8-bit LCD interface using P1.24–P1.31 data pins.
 ********************************************************/

#include <LPC214x.h> // Header file for LPC214x microcontroller register definitions

#define RS (1 << 16) // Register Select pin (P1.16)
#define RW (1 << 17) // Read/Write pin (P1.17)
#define EN (1 << 18) // Enable pin (P1.18)
#define LCD_DATA_MASK (0xFFu << 24) // Data pins D0–D7 on P1.24–P1.31

//Function Prototypes
void pll_init(void);
void delay_ms(unsigned int ms);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_str(const char *str);
void lcd_num(int num);
int isPrime(int num);

// Configures PLL to generate a 60 MHz CPU clock from 12 MHz crystal.
void pll_init(void) {
    PLL0CON = 0x01; // Enable PLL
    PLL0CFG = 0x24; // M = 5, P = 2 => 12MHz * 5 = 60MHz
    PLL0FEED = 0xAA; PLL0FEED = 0x55; // Feed sequence to apply changes
    while (!(PLL0STAT & (1 << 10))); // Wait for PLL to lock
    PLL0CON = 0x03; // Connect PLL as clock source
    PLL0FEED = 0xAA; PLL0FEED = 0x55; // Finalize feed sequence
}

// Generates approximate software delay in milliseconds.
void delay_ms(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms * 1000; i++); // Simple loop delay (not accurate)
}

void lcd_cmd(unsigned char cmd) {
    IO1CLR = RS | RW | EN | LCD_DATA_MASK; // Clear control and data lines
    IO1SET = ((cmd << 24) & LCD_DATA_MASK); // Place command on data bus
    IO1CLR = RS; // RS = 0 for command
    IO1CLR = RW; // RW = 0 for write
    IO1SET = EN; // Generate enable pulse
    delay_ms(2);
    IO1CLR = EN;
}

void lcd_data(unsigned char data) {
    IO1CLR = RS | RW | EN | LCD_DATA_MASK; // Clear control and data lines
    IO1SET = ((data << 24) & LCD_DATA_MASK); // Place data on bus
    IO1SET = RS; // RS = 1 for data
    IO1CLR = RW; // RW = 0 for write
    IO1SET = EN; // Latch data to LCD
    delay_ms(2);
    IO1CLR = EN;
}

void lcd_init(void) {
    IO1DIR |= RS | RW | EN | LCD_DATA_MASK; // Configure LCD pins as output
    delay_ms(20); // Wait for LCD to stabilize
    lcd_cmd(0x38); // 8-bit mode, 2-line display
    lcd_cmd(0x0C); // Display ON, cursor OFF
    lcd_cmd(0x06); // Auto-increment cursor
    lcd_cmd(0x01); // Clear display
    delay_ms(2);
}
void lcd_str(const char *str) {
    while (*str) lcd_data(*str++); // Write characters till null terminator
}

void lcd_num(int num) {
    char buf[6];
    int i = 0, j;

    if (num == 0) { lcd_data('0'); return; } // Directly print 0 if number is 0

    if (num < 0) { // Handle negative numbers
        lcd_data('-');
        num = -num;
    }

    // Extract digits in reverse order
    while (num > 0) {
        buf[i++] = (num % 10) + '0';
        num /= 10;
    }

    // Display digits in correct order
    for (j = i - 1; j >= 0; j--) 
        lcd_data(buf[j]);
}

int isPrime(int num) {
    int i;
    if (num <= 1) return 0; // 0 and 1 are not prime
    for (i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0; // Found a divisor => not prime
    }
    return 1; // Prime number
}

int main(void) {
    int n = 2; // Start checking from 2

    pll_init(); // Initialize PLL for proper timing
    lcd_init(); // Initialize LCD display

    while (1) {
        if (isPrime(n)) { // Check if current number is prime
            lcd_cmd(0x01); // Clear LCD screen
            lcd_str("Prime: "); // Label
            lcd_num(n); // Display the prime number
            delay_ms(1000); // Hold for 1 second
        }
        n++; // Increment number and continue
    }
}
