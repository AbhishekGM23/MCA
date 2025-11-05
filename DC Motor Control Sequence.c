/********************************************************
 * Program       : DC Motor Control Sequence
 * Description   : Controls the rotation of a DC motor 
 *                 using LPC2148 and L293D driver IC.
 *                 The motor runs forward and reverse 
 *                 for specific time intervals with delays.
 *
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 LPC2148
 * Processor     : NXP LPC2148
 * Motor Driver  : L293D
 * Connections   : P0.0 -> IN1 (L293D Input1)
 *                 P0.1 -> IN2 (L293D Input2)
 * Notes         : Uses software delay loops for timing.
 ********************************************************/

#include <lpc214x.h> // Include LPC214x MCU header for register definitions

/* Motor pin definitions */
#define IN1 (1<<0) // Define motor input pin IN1 at P0.0
#define IN2 (1<<1) // Define motor input pin IN2 at P0.1

/* Delay Function (approx 1 ms at 60 MHz) */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 6000; j++); // Inner loop for delay generation
    }
}

/* Function to rotate motor forward */
void motor_forward(void) {
    IOSET0 = IN1; // Set IN1 high
    IOCLR0 = IN2; // Clear IN2 low — Motor rotates forward
}

/* Function to rotate motor in reverse */
void motor_reverse(void) {
    IOSET0 = IN2; // Set IN2 high
    IOCLR0 = IN1; // Clear IN1 low — Motor rotates reverse
}

/* Function to stop motor rotation */
void motor_stop(void) {
    IOCLR0 = IN1 | IN2; // Clear both IN1 and IN2
}

/* Main function to control DC motor sequence */
int main(void) {
    PINSEL0 = 0x00000000; // Set Port0 pins as GPIO
    IO0DIR |= (IN1 | IN2); // Configure P0.0 and P0.1 as output pins

    while (1) {
        motor_forward(); // Move motor forward for 3 seconds
        delay_ms(3000);

        motor_stop(); // Stop motor for 1 second
        delay_ms(1000);

        motor_reverse(); // Move motor in reverse for 3 seconds
        delay_ms(3000);

        motor_stop(); // Stop motor for 1 second
        delay_ms(1000);

        motor_forward(); // Move motor forward again for 2 seconds
        delay_ms(2000);

        // Additional sequences can be added here if needed
    }
}
