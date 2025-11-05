/********************************************************/
/* This Program is to demonstrate the Push button Functionality */
/*******************************************************
Author 			: Abhaya Y, Abhishek G M
Board 			: arm 7
Processor 	: LPC2148

LED Mapping 	: LED0 thru LED7 : P1.24 through P1.31
Button Mapping: Button : P0.14 (Active High)
********************************************************/
#include <LPC214x.h>          // Header file for LPC2148

#define LED_MASK  0xFF000000  // LEDs connected to Port1 pins P1.24–P1.31
#define BUTTON    (1<<14)     // Push button connected to P0.14

int main() {
    int i = 0;

    // Configure all pins as GPIO
    PINSEL2 = 0x00000000;
    PINSEL1 = 0x00000000;
    PINSEL0 = 0x00000000;

    // Configure P0.14 as input (button)
    IODIR0 &= ~BUTTON;

    // Configure P1.24–P1.31 as output (LEDs)
    IODIR1 |= LED_MASK;

    while (1) {
        // Check button state (HIGH = pressed if pull-up is enabled externally)
        if (IOPIN0 & BUTTON) {
            // If button is pressed ,blink upper 4 LEDs (P1.28–P1.31)
            IOSET1 = 0xF0000000;     // Turn ON LEDs (upper 4 bits)
            for (i = 0; i < 7500; i++); // Delay loop
            IOCLR1 = 0xF0000000;     // Turn OFF LEDs
            for (i = 0; i < 7500; i++); // Delay loop
        }
        else {
            // If button is not pressed,blink lower 4 LEDs (P1.24–P1.27)
            IOSET1 = 0x0F000000;     // Turn ON LEDs (lower 4 bits)
            for (i = 0; i < 7500; i++); // Delay loop
            IOCLR1 = 0x0F000000;     // Turn OFF LEDs
            for (i = 0; i < 7500; i++); // Delay loop
        }
    }
}
