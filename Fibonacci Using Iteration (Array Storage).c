/********************************************************
 * Program       : Fibonacci Using Iteration (Array Storage)
 * Description   : Generates first N Fibonacci numbers; writes them sequentially to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Basic iterative sequence storage.
 ********************************************************/

#include <LPC214x.h> // Include LPC214x microcontroller-specific header file
#include <stdint.h> // Include standard integer type definitions

// Define base memory address where Fibonacci sequence will be stored
#define RESULT_ADDR ((volatile int*)0x40000000)

// Define number of Fibonacci terms to generate
#define FIB_N 12

int main(void) {
    volatile int *dst = RESULT_ADDR; // Pointer to the memory-mapped result address

    int a = 0, b = 1, temp, i; // Initialize first two Fibonacci numbers
    dst[0] = a; // Store the first term (0)
    
    if (FIB_N > 1) // Check if at least two terms are required
        dst[1] = b; // Store the second term (1)

    // Generate remaining Fibonacci terms iteratively
    for (i = 2; i < FIB_N; i++) {
        temp = a + b; // Next term = sum of previous two
        a = b; // Update 'a' to previous 'b'
        b = temp; // Update 'b' to new term
        dst[i] = temp; // Store the computed term in memory
    }

    while (1) {} // Infinite loop to stop program execution
}
