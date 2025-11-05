/********************************************************
 * Program       : Electronic Dice Using Timer and LED Display
 * Description   : Simulates an electronic dice using Timer0 for randomness. 
 *                 When a push button (P0.10) is pressed, a random pattern 
 *                 representing dice face 1–6 is displayed on LEDs (P0.0–P0.5).
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 Development Board
 * Processor     : LPC2148
 * Notes         : Uses Timer0 counter (T0TC) as random seed.
 ********************************************************/

#include <LPC214x.h> // LPC214x register definitions

// Simple delay function to debounce button or create visible effect
void delay(unsigned int time){
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 6000; j++);
}

int main() {
    unsigned int dice_value; // Variable to store dice roll value
    unsigned int pattern[6] = {0x01, 0x02, 0x04, 
                               0x08, 0x10, 0x20}; // LED patterns for dice faces 1–6

    IODIR0 |= 0x3F; // Configure pins P0.0–P0.5 as output for LEDs
    IODIR0 &= ~(1 << 10); // Configure P0.10 as input for button

    // Initialize and start Timer0
    T0PR = 0; // Prescaler = 0 for continuous counting
    T0TCR = 0x01; // Timer Enable (sets T0TC to start up-counting)

    while(1) {
        // Check if button is pressed (active low)
        if(!(IOPIN0 & (1 << 10))) {
            
            dice_value = T0TC % 6; // Obtain pseudo-random number from Timer counter (0–5)
            
            IOCLR0 = 0x3F; // Clear all LED outputs
            IOSET0 = pattern[dice_value]; // Display the corresponding dice face pattern
            
            delay(10); // Delay for simple button debounce
            
            // Wait until button is released to avoid multiple triggers
            while(!(IOPIN0 & (1 << 10)));
        }
    }
}
