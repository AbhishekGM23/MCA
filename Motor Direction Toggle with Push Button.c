/********************************************************
 * Program       : Motor Direction Toggle with Push Button
 * Description   : This program toggles the DC motor's direction each time 
 *                 a push button is pressed. The motor starts rotating in 
 *                 the forward direction and reverses on every button press.
 *
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 LPC2148
 * Processor     : LPC2148
 * Motor Driver  : L293D
 *
 * Connections:
 *   Motor Pins  : P0.0 -> IN1 (L293D Input1)
 *                 P0.1 -> IN2 (L293D Input2)
 *   Button Pin  : P0.2 -> Push Button (Active LOW)
 *
 * Notes         : Debouncing is handled through a small software delay.
 ********************************************************/

#include <lpc214x.h> // Include LPC214x register definitions

/* Pin Definitions */
#define IN1     (1 << 0) // Motor input pin 1 connected to P0.0
#define IN2     (1 << 1) // Motor input pin 2 connected to P0.1
#define BUTTON  (1 << 2) // Push button connected to P0.2

// Function to generate a software delay in milliseconds
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 6000; j++); // Approximate delay of 1 ms at 60 MHz
    }
}

// Motor control functions for L293D driver
void motor_forward(void) { IOSET0 = IN1; IOCLR0 = IN2; } // Forward direction
void motor_reverse(void) { IOSET0 = IN2; IOCLR0 = IN1; } // Reverse direction
void motor_stop(void)    { IOCLR0 = IN1 | IN2; } // Stop motor

// Function to return 1 if button is pressed (active LOW)
int button_pressed(void) {
    if ((IO0PIN & BUTTON) == 0) { // 0 indicates button press
        delay_ms(1); // Small delay for debouncing
        if ((IO0PIN & BUTTON) == 0) // Confirm press after delay
            return 1;
    }
    return 0; // Button not pressed
}

int main(void) {
    int direction = 0; // 0 = forward, 1 = reverse

    /* Pin Configuration */
    IO0DIR |= (IN1 | IN2); // Configure motor control pins as output
    IO0DIR &= ~(BUTTON); // Configure button pin as input
    PINSEL0 = 0; // Set pins for GPIO function

    motor_forward(); // Start motor in forward direction

    // Main loop: Toggle motor direction on each button press
    while (1) {
        if (button_pressed()) { // Check for button press
            direction = !direction; // Toggle the direction flag

            if (direction == 0)
                motor_forward(); // Run motor in forward direction
            else
                motor_reverse(); // Run motor in reverse direction

            // Wait until button is released to avoid multiple toggles
            while ((IO0PIN & BUTTON) == 0);
        }
    }
}
