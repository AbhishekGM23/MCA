/********************************************************
 * Program       : Timer0 LED Toggle Using Interrupt
 * Description   : Configures Timer0 to generate periodic interrupts every 500ms
 *                 and toggles an LED connected to P0.10 on each interrupt.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Demonstrates Timer0 interrupt setup with VIC and LED toggling.
 ********************************************************/

#include <LPC214x.h> // Include LPC214x register definitions

// Define LED pin connected to Port 0.10
#define LED (1 << 10)

// Function prototype for Timer0 Interrupt Service Routine
void TIMER0_ISR(void) __irq;

int main(void)
{
    // Configure P0.10 as output for LED
    IODIR0 |= LED;

    // Timer0 setup for periodic interrupt generation
    T0PR = 60000 - 1; // Prescaler: generates 1ms tick (60 MHz / 60000 = 1 kHz)
    T0MR0 = 500; // Match value to trigger every 500ms
    T0MCR = (1 << 0) | (1 << 1); // On MR0: Generate interrupt and reset timer

    // Configure VIC for Timer0 interrupt
    VICIntSelect &= ~(1 << 4); // Assign Timer0 interrupt to IRQ (not FIQ)
    VICVectAddr0 = (unsigned)TIMER0_ISR; // Set ISR address in VIC vector slot 0
    VICVectCntl0 = (1 << 5) | 4; // Enable vector slot 0 for Timer0
    VICIntEnable = (1 << 4); // Enable Timer0 interrupt in VIC

    // Start Timer0
    T0TCR = 1;

    while (1); // Infinite loop; LED toggling handled by interrupt
}

// Timer0 Interrupt Service Routine
void TIMER0_ISR(void) __irq
{
    IOSET0 ^= LED; // Toggle LED on each interrupt
    T0IR = 1; // Clear interrupt flag for MR0
    VICVectAddr = 0; // Signal end of interrupt to VIC
}
