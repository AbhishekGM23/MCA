/********************************************************
 * Program       : LED Control After 10 Button Presses
 * Description   : This program uses Timer0 in counter mode to count 
 *                 button presses on pin P0.2 (CAP0.0). 
 *                 When the button is pressed 10 times, the LED on 
 *                 P0.10 is turned ON.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 LPC2148
 * Processor     : LPC2148
 * LED Pin       : P0.10
 * Button Pin    : P0.2 (CAP0.0)
 * Notes         : Timer0 counts external rising edges on CAP0.0.
 ********************************************************/

#include <LPC214x.h> // Include LPC214x microcontroller definitions

// Function to initialize Timer0 in counter mode
void init_counter0(void) {
    // Configure pin P0.2 for CAP0.0 functionality
    PINSEL0 |= (2 << 4); // Set bits 5:4 = 10 -> P0.2 acts as CAP0.0

    T0TCR = 0x02; // Reset Timer0 to clear previous count
    T0CTCR = 0x01; // Set Counter Mode: run on rising edge of CAP0.0
    T0PR = 0; // No prescaling; count every pulse directly
    T0TCR = 0x01; // Enable Timer0 counter
}

int main(void) {
    unsigned int count; // Variable to store button press count

    init_counter0(); // Initialize counter configuration

    IO0DIR |= (1 << 10); // Configure P0.10 as output for LED

    while (1) {
        count = T0TC; // Read current count of button presses (Timer Counter)

        // Turn ON LED when button has been pressed 10 or more times
        if (count >= 10) {
            IO0SET = (1 << 10); // Set P0.10 high to turn ON LED
        }
    }
}
