/********************************************************
 * Program       : LCD Scrolling Text on 16x2 Display
 * Description   : Demonstrates continuous text scrolling on both 
 *                 lines of a 16x2 LCD display connected to LPC2148.
 *                 Line1 -> "MSIS Manipal"
 *                 Line2 -> "Embedded System"
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 (LPC2148)
 * Processor     : LPC2148 (ARM7TDMI-S)
 * Notes         : LCD operates in 8-bit mode, P1.16–P1.18 used for 
 *                 control signals and P1.24–P1.31 for data bus.
 ********************************************************/

#include <lpc214x.h>
#include <stdio.h>
#include <string.h>

#define RS   (1 << 16) /* RS pin (P1.16) */
#define RW   (1 << 17) /* RW pin (P1.17) */
#define EN   (1 << 18) /* EN pin (P1.18) */
#define DATA (0xFF000000) /* P1.24–P1.31 used for D0–D7 */

/* Delay Function */
void delay(unsigned int x) {
    unsigned int i, j;
    for (i = 0; i < x; i++) {
        for (j = 0; j < 6000; j++);
    }
}

/* LCD Enable Pulse */
void lcd_pulse(void) {
    IOSET1 = EN;
    delay(2);
    IOCLR1 = EN;
}

/* Send Command to LCD */
void lcd_cmd(unsigned char cmd) {
    IOCLR1 = RS; /* RS = 0 -> command */
    IOCLR1 = RW; /* RW = 0 -> write   */
    IOCLR1 = DATA; /* Clear previous data */

    IOSET1 = ((unsigned int)cmd << 24);
    lcd_pulse();
    delay(2);
}

/* Send Data (character) to LCD */
void lcd_data(unsigned char data) {
    IOSET1 = RS; /* RS = 1 -> data */
    IOCLR1 = RW; /* RW = 0 -> write */
    IOCLR1 = DATA;

    IOSET1 = ((unsigned int)data << 24);
    lcd_pulse();
    delay(2);
}

/* Initialize LCD */
void lcd_init(void) {
    IODIR1 |= RS | RW | EN; /* Control pins */
    IODIR1 |= DATA; /* Data pins */

    delay(20);
    lcd_cmd(0x38); /* 8-bit, 2 line, 5x7 */
    lcd_cmd(0x0C); /* Display ON, cursor OFF */
    lcd_cmd(0x06); /* Entry mode */
    lcd_cmd(0x01); /* Clear display */
    delay(2);
}

/* Send String to LCD */
void lcd_string(char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

/* Shift display left */
void lcd_shift_left(void) {
    lcd_cmd(0x18); /* Command: Shift entire display left */
}

/* Main Program */
int main(void) {
    char line1[] = "MSIS Manipal    "; /* padded with spaces */
    char line2[] = "Embedded System "; /* padded with spaces */
    int i;

    lcd_init();

    /* Write initial strings */
    lcd_cmd(0x80); /* Line 1 start */
    lcd_string(line1);
    lcd_cmd(0xC0); /* Line 2 start */
    lcd_string(line2);

    while (1) {
        for (i = 0; i < 16; i++) { /* Scroll left 16 times */
            delay(500); /* Adjust scroll speed */
            lcd_shift_left();
        }
    }
}
