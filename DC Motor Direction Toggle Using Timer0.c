/********************************************************
 * Program       : DC Motor Direction Toggle Using Timer0
 * Description   : This program toggles the direction of a DC motor 
 *                 connected to L293D on each valid button press. 
 *                 Timer0 interrupt is used for button debouncing 
 *                 and continuous poll checking (no delay loops used).
 *
 * Hardware Setup:
 *   - L293D IN1 connected to P0.0
 *   - L293D IN2 connected to P0.1
 *   - Push Button connected to P0.2 (active LOW)
 *
 * Working:
 *   - Timer0 generates periodic interrupts every 1 ms.
 *   - On each interrupt, the button state is read.
 *   - A stable low signal for 30 ms is considered a valid press.
 *   - Each valid press toggles the motor direction between forward and reverse.
 *
 * Authors        : Abhaya Y, Abhishek G M
 * Board          : ARM7 Stick / MCB2140
 * Processor      : LPC2148
 ********************************************************/

#include <LPC214x.h> // LPC214x microcontroller header for register definitions

// Define pin connections
#define IN1     (1 << 0) // P0.0 -> L293D IN1
#define IN2     (1 << 1) // P0.1 -> L293D IN2
#define BUTTON  (1 << 2) // P0.2 -> Push Button (Active LOW)

// Global variables for motor control and debouncing
volatile int direction = 0; // 0 = forward, 1 = reverse
volatile int debounce_count = 0; // Millisecond counter for stable button detection
volatile int button_state = 1; // 1 = released, 0 = pressed

// Function to run motor forward
void motor_forward(void) {
    IOSET0 = IN1; // Set IN1 high
    IOCLR0 = IN2; // Set IN2 low
}

// Function to run motor in reverse
void motor_reverse(void) {
    IOSET0 = IN2; // Set IN2 high
    IOCLR0 = IN1; // Set IN1 low
}

void __irq Timer0_ISR(void)
{
    int read = IO0PIN & BUTTON; // Read button input (active LOW)

    if (read == 0) // Button pressed
    {
        debounce_count++;
        if (debounce_count >= 30 && button_state == 1) // Stable for 30 ms
        {
            button_state = 0; // Confirm button pressed
            direction ^= 1; // Toggle direction bit

            if (direction == 0)
                motor_forward();
            else
                motor_reverse();
        }
    }
    else // Button released
    {
        debounce_count = 0;
        button_state = 1; // Reset button state
    }

    T0IR = 1; // Clear Timer0 interrupt flag
    VICVectAddr = 0; // Acknowledge end of ISR
}

void Timer0_Init(void)
{
    T0TCR = 0x02; // Reset Timer0
    T0PR  = 15000 - 1; // Prescaler for 1 ms tick (Pclk = 15 MHz)
    T0MR0 = 1; // Match every 1 ms
    T0MCR = 3; // Interrupt and reset on match

    VICIntSelect &= ~(1 << 4); // Use IRQ for Timer0
    VICVectAddr0 = (unsigned)Timer0_ISR; // Set ISR address
    VICVectCntl0 = 0x20 | 4; // Enable slot 0 for Timer0 interrupt
    VICIntEnable |= (1 << 4); // Enable Timer0 interrupt

    T0TCR = 1; // Start Timer0
}

int main(void)
{
    PINSEL0 = 0x00000000; // Configure pins as GPIO
    IO0DIR |= (IN1 | IN2); // Set motor control pins as output
    IO0DIR &= ~(BUTTON); // Set button pin as input

    motor_forward(); // Start motor initially in forward direction
    Timer0_Init(); // Initialize Timer0

    while(1); // Infinite loop (work handled by ISR)
}
