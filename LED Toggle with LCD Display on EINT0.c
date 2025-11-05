/********************************************************
 * Program       : LED Toggle with LCD Display on EINT0
 * Description   : Toggles LED connected to P0.10 when the
 *                 push button connected to P0.14 (EINT0) 
 *                 is pressed. Displays LED ON/OFF status 
 *                 on a 16x2 LCD.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 LPC2148
 * Processor     : LPC2148
 * Notes         : Demonstrates interrupt-driven I/O with 
 *                 real-time LCD updates.
 ********************************************************/

#include <LPC214x.h>

// Define LCD pin connections
#define RS (1<<0) // Register select connected to P0.0
#define EN (1<<1) // Enable pin connected to P0.1
#define LCD_DATA (0xF<<4) // Data pins D4–D7 connected to P0.4–P0.7

volatile int led_state = 0; // Variable to track LED ON/OFF status

// Function prototypes
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void lcd_string(char *ptr);
void delay(unsigned int t);
void lcd_display_status(void);

// External Interrupt Service Routine for EINT0
void EINT0_ISR(void) __irq {
    led_state ^= 1; // Toggle LED state

    if (led_state)
        IOSET0 = (1<<10); // Turn ON LED connected to P0.10
    else
        IOCLR0 = (1<<10); // Turn OFF LED

    lcd_display_status(); // Update LED status message on LCD

    EXTINT = 0x01; // Clear EINT0 interrupt flag
    VICVectAddr = 0; // End of interrupt
}

// Provide short enable pulse to LCD
void lcd_pulse() {
    IOSET0 = EN;
    delay(1000);
    IOCLR0 = EN;
}

// Send command to LCD
void lcd_cmd(unsigned char cmd) {
    IOCLR0 = RS; // RS = 0 for command mode
    IOCLR0 = LCD_DATA;
    IOSET0 = ((cmd >> 4) & 0x0F) << 4; // Send high nibble
    lcd_pulse();

    IOCLR0 = LCD_DATA;
    IOSET0 = (cmd & 0x0F) << 4; // Send low nibble
    lcd_pulse();

    delay(5000);
}

// Send data character to LCD
void lcd_data(unsigned char data) {
    IOSET0 = RS; // RS = 1 for data mode
    IOCLR0 = LCD_DATA;
    IOSET0 = ((data >> 4) & 0x0F) << 4; // Send high nibble
    lcd_pulse();

    IOCLR0 = LCD_DATA;
    IOSET0 = (data & 0x0F) << 4; // Send low nibble
    lcd_pulse();

    delay(5000);
}

// Initialize the LCD display
void lcd_init() {
    delay(15000);
    lcd_cmd(0x02); // Initialize LCD in 4-bit mode
    lcd_cmd(0x28); // 2-line, 5x7 matrix
    lcd_cmd(0x0C); // Display ON, cursor OFF
    lcd_cmd(0x06); // Entry mode - cursor moves right
    lcd_cmd(0x01); // Clear display
}

// Display a full string on LCD
void lcd_string(char *ptr) {
    while (*ptr)
        lcd_data(*ptr++);
}

// Show LED ON/OFF status on LCD
void lcd_display_status() {
    lcd_cmd(0x01); // Clear screen
    lcd_cmd(0x80); // Position to first line
    lcd_string("LED Status:");

    lcd_cmd(0xC0); // Move to second line
    if (led_state)
        lcd_string("LED ON ");
    else
        lcd_string("LED OFF");
}

// Simple software delay
unsigned int i;
void delay(unsigned int t) {
    for (i = 0; i < t; i++);
}

// Main function
int main(void) {

    // Set LCD pins and LED pin as output
    IODIR0 |= RS | EN | LCD_DATA | (1<<10);

    lcd_init(); // Initialize LCD
    lcd_display_status(); // Show initial LED status

    // Configure P0.14 as external interrupt (EINT0)
    PINSEL0 |= (1<<29); // Select EINT0 function for P0.14

    EXTMODE = 0x01; // Edge-sensitive mode
    EXTPOLAR = 0x00; // Falling edge trigger

    // Configure Vectored Interrupt Controller (VIC)
    VICIntSelect &= ~(1<<14); // Configure as IRQ
    VICVectAddr0 = (unsigned)EINT0_ISR; // Set ISR address
    VICVectCntl0 = (1<<5) | 14; // Enable slot and assign EINT0
    VICIntEnable = (1<<14); // Enable EINT0 interrupt

    while (1); // Infinite loop; waiting for interrupts
}
