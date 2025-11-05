/********************************************************
 * Program       : Stepper Motor Control (2 CW & 2 CCW Cycles)
 * Description   : Rotates stepper motor two complete cycles in
 *                 clockwise direction, then two in counterclockwise
 *                 direction, repeating indefinitely.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 LPC2148
 * Processor     : LPC2148
 * Compiler      : Keil uVision (C89 Standard)
 * Motor Pins    : P0.16 – P0.19
 * Notes         : Uses full-step sequence for motor drive.
 ********************************************************/

#include <lpc214x.h> // Header file for LPC214x microcontroller

/* Delay Function: Generates approximate millisecond delay */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 6000; j++); // Inner loop for time delay
    }
}

/* Step sequence table for full-step driving mode */
int step_seq[4] = {0x01, 0x02, 0x04, 0x08};

/* Function to rotate motor in either direction */
void rotate_motor(int dir, int steps) {
    int i;
    for (i = 0; i < steps; i++) {
        if (dir == 1) {  // Clockwise rotation
            IOCLR0 = (0x0F << 16); // Clear previous coil states
            IOSET0 = (step_seq[i % 4] << 16); // Set next step pattern
        } else {         // Counterclockwise rotation
            IOCLR0 = (0x0F << 16); // Clear previous coil states
            IOSET0 = (step_seq[3 - (i % 4)] << 16); // Reverse step order
        }
        delay_ms(50); // Control speed of rotation (adjustable)
    }
}

int main(void) {
    IODIR0 |= (0x0F << 16); // Configure P0.16–P0.19 as output for motor control

    while (1) {
        rotate_motor(1, 8); // Two clockwise cycles (8 steps total)
        delay_ms(50);

        rotate_motor(0, 8); // Two counterclockwise cycles (8 steps total)
        delay_ms(50);
    }
}
