/********************************************************
 * Program       : LED Pattern Control using Buttons
 * Description   : Controls LED patterns based on button input.
 *                 - Button1: Runs LEDs sequentially (pattern1)
 *                 - Button2: Toggles alternate LEDs (pattern2)
 *                 - No button: All LEDs OFF
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 (LPC2148)
 * Processor     : LPC2148
 * Notes         : Demonstrates GPIO input (buttons) and output (LEDs) operations.
 ********************************************************/

#include <LPC214x.h> // Include LPC214x header for register definitions

// Simple software delay function
void delay(unsigned int t) {
    unsigned int i, j;
    for (i = 0; i < t; i++)
        for (j = 0; j < 6000; j++); // Loop to create approximate delay
}

int i;

// Pattern1: Running LED sequence (one-by-one ON)
void pattern1() {
    for (i = 0; i < 8; i++) {
        IOSET0 = (1 << i); // Turn ON LED at position i
        delay(10); // Short delay for visible transition
        IOCLR0 = (1 << i); // Turn OFF current LED before next one
    }
}

// Pattern2: Alternate blinking LEDs
void pattern2() {
    IOSET0 = 0x55; // Binary: 01010101 ? LEDs ON at even positions
    delay(20); // Wait for a while
    IOSET0 = 0xAA; // Binary: 10101010 ? LEDs ON at odd positions
    delay(20);
    IOCLR0 = 0xFF; // Turn OFF all LEDs
}

int main() {
    IODIR0 |= 0xFF; // Configure P0.0–P0.7 as output for LEDs
    IODIR0 &= ~((1 << 10) | (1 << 11)); // Configure P0.10 and P0.11 as input for buttons

    while (1) {
        if (!(IOPIN0 & (1 << 10))) { // If Button1 (P0.10) is pressed
            delay(20); // Debounce delay
            pattern1(); // Execute running LED pattern
        } 
        else if (!(IOPIN0 & (1 << 11))) { // If Button2 (P0.11) is pressed
            delay(20); // Debounce delay
            pattern2(); // Execute alternate LED pattern
        } 
        else {
            IOCLR0 = 0xFF; // If no button pressed, turn OFF all LEDs
        }
    }
}
