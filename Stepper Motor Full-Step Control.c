/********************************************************
 * Program       : Stepper Motor Full-Step Control
 * Description   : Drives a stepper motor in full-step mode using GPIO pins P0.16–P0.19.
 *                 The motor sequence is continuously rotated forward with a fixed delay
 *                 between steps to control speed.
 * Author        : Abhaya Y
 * Board         : ARM7 LPC2148
 * Processor     : LPC2148
 * Compiler      : Keil (C89 standard)
 * Notes         : Each GPIO pin drives one coil of the stepper motor.
 ********************************************************/

#include <lpc214x.h> // Header file containing LPC214x register definitions

/* Delay Function (software-based) */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 6000; j++); // Approximate delay loop
    }
}

int main(void) {
    int i;

    /* Full-step excitation sequence for 4-step rotation */
    int step_seq[4] = {0x01, 0x02, 0x04, 0x08};

    /* Configure P0.16–P0.19 as output for motor driver control */
    IODIR0 |= (0x0F << 16);

    while (1) {
        for (i = 0; i < 4; i++) {
            IOCLR0 = (0x0F << 16); // Clear P0.16–P0.19 before next step
            IOSET0 = (step_seq[i] << 16); // Set next pattern on motor pins
            delay_ms(100); // Delay to control motor speed
        }
    }
}
