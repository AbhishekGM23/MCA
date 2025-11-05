/********************************************************
 * Program       : Factorial Using Iteration
 * Description   : Calculates factorial of a number iteratively; writes result to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Result stored as unsigned long at 0x40000000.
 ********************************************************/

#include <LPC214x.h> // LPC214x microcontroller-specific register definitions
#include <stdint.h> // Standard integer definitions

// Define the memory address where factorial result will be stored
#define RESULT_ADDR ((volatile unsigned long*)0x40000000)

// Define the number for which factorial is to be calculated
#define FACT_NUM 5

// Function to calculate factorial of n using iterative method
unsigned long factorial_iter(int n) {
		int i;
    unsigned long result = 1; // Initialize result to 1
    for (i = 2; i <= n; i++) { // Loop from 2 to n
        result *= i; // Multiply result by each number
    }
    return result; // Return the computed factorial
}

int main(void) {
    volatile unsigned long *dst = RESULT_ADDR; // Pointer to memory address 0x40000000
    dst[0] = factorial_iter(FACT_NUM); // Store factorial result to memory
    while (1) {} // Infinite loop to stop execution
}
