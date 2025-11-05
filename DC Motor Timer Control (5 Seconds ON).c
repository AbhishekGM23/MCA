/********************************************************
 * Program       : DC Motor Timer Control (5 Seconds ON)
 * Description   : When the push button is pressed, the DC motor runs
 *                 in the forward direction for 5 seconds and then stops automatically.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 LPC2148
 * Processor     : LPC2148
 * Motor Driver  : L293D
 * 
 * Motor Connections:
 *      P0.0 -> IN1 (Motor Driver Input)
 *      P0.1 -> IN2 (Motor Driver Input)
 * Button Connection:
 *      P0.2 -> Push Button (Active LOW)
 * 
 * Notes         : The program uses software delay for timing and polling for button input.
 ********************************************************/

#include <LPC214x.h> // LPC214x microcontroller-specific header file

/* Pin Definitions */
#define IN1     (1 << 0) // Motor input pin 1: P0.0
#define IN2     (1 << 1) // Motor input pin 2: P0.1
#define BUTTON  (1 << 2) // Push button input pin: P0.2

/* Delay Function (Approximate Millisecond Delay) */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 6000; j++); // Inner loop calibrated for ~1ms delay at 60 MHz
    }
}

/* Motor Control Functions */
void motor_forward(void) {
    IOSET0 = IN1; // Set IN1 HIGH
    IOCLR0 = IN2; // Set IN2 LOW -> rotates motor in forward direction
}

void motor_stop(void) {
    IOCLR0 = IN1 | IN2; // Set both pins LOW -> stop motor
}

/* Button Check Function (Active LOW) */
int button_pressed(void) {
    if ((IO0PIN & BUTTON) == 0) { // If button pressed (LOW)
        delay_ms(10); // Simple debounce delay
        if ((IO0PIN & BUTTON) == 0) // Check again after debounce
            return 1; // Confirm button press
    }
    return 0; // Button not pressed
}

int main(void) {

    PINSEL0 = 0; // Configure pins as GPIO
    IO0DIR |= (IN1 | IN2); // Set motor pins as output
    IO0DIR &= ~(BUTTON); // Configure button pin as input

    motor_stop(); // Ensure motor is off initially

    while (1) {
        if (button_pressed()) { // Check for button press
            motor_forward(); // Start motor rotation
            delay_ms(5000); // Run motor for 5 seconds
            motor_stop(); // Stop motor after timeout

            while ((IO0PIN & BUTTON) == 0);  // Wait until button released
        }
    }
}
