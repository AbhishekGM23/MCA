/********************************************************
Program           : Inside-Out LED Blinking
Author            : Abhaya Y, Abhishek G M
Board             : ARM7 Development Board
Processor         : LPC2148

Port Used         : P0.0 – P0.7 (8 LEDs connected)

Description       : 
- Two LEDs at the center (P0.3 & P0.4) turn ON first.
- Then LEDs expand outward in pairs: (P0.2 & P0.5), 
  (P0.1 & P0.6), and finally (P0.0 & P0.7).
- The sequence repeats continuously, giving a
  symmetrical blinking pattern.
********************************************************/

#include <lpc214x.h>    // Header file for LPC2148

#define DELAY 200       // Delay time in ms

//Generate software delay in milliseconds
void delay_ms(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++) {
        for(j = 0; j < 1000; j++);  // Approximate delay
    }
}

int main(void) {
	
// Defineing LED ON patterns for Inside–Out sequence
    unsigned int pattern[] = {
        (1 << 3) | (1 << 4),   // Step 1: LEDs at center
        (1 << 2) | (1 << 5),   // Step 2: Next pair outward
        (1 << 1) | (1 << 6),   // Step 3: Next outward pair
        (1 << 0) | (1 << 7)    // Step 4: Extreme LEDs
    };

    int i;
    IODIR0 |= 0xFF;   // Configure P0.0 – P0.7 as output

    while(1) {
        for(i = 0; i < 4; i++) {
            IOCLR0 = 0xFF;        // Turn OFF all LEDs
            IOSET0 = pattern[i];  // Turn ON selected LEDs
            delay_ms(DELAY);      // Wait for some time
        }
    }
}
