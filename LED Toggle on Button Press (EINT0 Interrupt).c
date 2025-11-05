/********************************************************
 * Program       : LED Toggle on Button Press (EINT0 Interrupt)
 * Description   : Toggles an LED connected to P0.10 each time
 *                 the push button on P0.14 triggers an external interrupt (EINT0).
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Uses edge-triggered interrupt to toggle LED state.
 ********************************************************/

#include <LPC214x.h> // Include LPC214x microcontroller definitions

// Interrupt Service Routine for EINT0
void EINT0_ISR(void) __irq {
    IO0PIN ^= (1 << 10); // Toggle LED connected to P0.10
    EXTINT = 0x01; // Clear interrupt flag for EINT0
    VICVectAddr = 0; // Notify end of ISR to the VIC
}

int main(void) {
    IO0DIR |= (1 << 10); // Configure P0.10 as output (LED pin)

    // Configure P0.14 pin function as EINT0 (External Interrupt 0)
    PINSEL0 |= (1 << 29); // Set bits to select EINT0 function for P0.14

    // Configure external interrupt registers
    EXTMODE = 0x01; // Set EINT0 as edge-sensitive
    EXTPOLAR = 0x00; // Trigger on falling edge

    // Configure VIC (Vectored Interrupt Controller)
    VICIntSelect &= ~(1 << 14); // Select EINT0 as IRQ (not FIQ)
    VICVectAddr0 = (unsigned)EINT0_ISR; // Set address of ISR
    VICVectCntl0 = (1 << 5) | 14; // Enable slot 0 and assign source 14 (EINT0)
    VICIntEnable = (1 << 14); // Enable interrupt for EINT0 in VIC

    while (1); // Infinite loop; CPU waits for interrupts
}
