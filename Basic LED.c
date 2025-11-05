/********************************************************/
/* This Program is to demonstrate the LED Functionality */
/********************************************************
Author          : Abhaya Y, Abhishek G M
Board           : ARM7 Development Board
Processor       : LPC2148

LED Mapping     : LED0 thru LED7 : P1.24 through P1.31

Description     : This program turns ON LEDs one by one (LED chaser effect),
                  with a small delay between each ON and OFF operation.
********************************************************/

#include <LPC214x.h>          // Header file for LPC2148

#define LED_MASK 0xFF000000   // LED bit mask for P1.24–P1.31

int main() {
    int i = 0, j = 0;

    PINSEL2 = 0;              // Configure Port1 pins (P1.16–P1.31) as GPIO
    IODIR1 |= LED_MASK;       // Set P1.24–P1.31 as output for LEDs

    while (1) {
        // Loop through LEDs from P1.24 to P1.31
        for (j = 24; j < 32; j++) {
            IOSET1 = (1 << j);      // Turn ON LED at position j
            for (i = 0; i < 7500; i++); // Delay
            IOCLR1 = (1 << j);      // Turn OFF LED at position j
            for (i = 0; i < 7500; i++); // Delay
        }
    }
}
