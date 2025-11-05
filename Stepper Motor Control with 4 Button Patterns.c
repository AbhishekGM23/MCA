/********************************************************
 * Program       : Stepper Motor Control with 4 Button Patterns
 * Description   : Controls a unipolar/bipolar stepper motor using
 *                 four input switches. Each switch triggers a fixed
 *                 number of steps and direction as follows:
 *
 *   SW1 - 4 steps Clockwise (CW)
 *   SW2 - 2 steps Counter-clockwise (CCW)
 *   SW3 - 8 steps Clockwise (CW)
 *   SW4 - 6 steps Counter-clockwise (CCW)
 *
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7 LPC2148
 * Compiler      : Keil (C89 standard)
 * Motor Pins    : P0.16–P0.19 (connected to driver inputs)
 * Buttons       : P0.4–P0.7  (active LOW)
 * Notes         : Uses full-step sequence with 4 control bits.
 ********************************************************/

#include <LPC214x.h> // Include LPC214x register and peripheral definitions

/* Delay Function: Generates software delay (approx. 1 ms per iteration) */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 6000; j++); // Approximate delay loop
    }
}

/* Full-step sequence for controlling the stepper motor */
int step_seq[4] = {0x01, 0x02, 0x04, 0x08};

/* Function to rotate motor by specified steps in a given direction */
void rotate_steps(int steps, int dir) {
    int i, pos = 0;
    for (i = 0; i < steps; i++) {
        IOCLR0 = (0x0F << 16); // Clear motor control pins (P0.16–P0.19)
        IOSET0 = (step_seq[pos] << 16); // Set control pins as per current step pattern
        delay_ms(50); // Small delay for visible motor movement

        if (dir == 1) // dir = 1 ? Clockwise
            pos = (pos + 1) % 4; // Move to next step sequence
        else // dir = 0 ? Counter-clockwise
            pos = (pos - 1 + 4) % 4; // Move to previous step sequence
    }
    IOCLR0 = (0x0F << 16); // Turn off all coils after motion
}

int main(void) {
    /* Configure motor pins (P0.16–P0.19) as output */
    IODIR0 |= (0x0F << 16);

    /* Configure button pins (P0.4–P0.7) as input */
    IODIR0 &= ~(0x0F << 4);

    /* Infinite loop to check button presses and trigger corresponding motion */
    while (1) {
        if (!(IOPIN0 & (1 << 4))) { // SW1 pressed ? 4 steps CW
            rotate_steps(4, 1);
        }
        else if (!(IOPIN0 & (1 << 5))) { // SW2 pressed ? 2 steps CCW
            rotate_steps(2, 0);
        }
        else if (!(IOPIN0 & (1 << 6))) { // SW3 pressed ? 8 steps CW
            rotate_steps(8, 1);
        }
        else if (!(IOPIN0 & (1 << 7))) { // SW4 pressed ? 6 steps CCW
            rotate_steps(6, 0);
        }
    }
}
