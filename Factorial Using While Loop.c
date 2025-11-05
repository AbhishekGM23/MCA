/********************************************************
 * Program       : Factorial Using While Loop
 * Description   : Calculates factorial using while loop; writes result to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Iterative factorial with loop variation.
 ********************************************************/

#include <LPC214x.h> // LPC214x microcontroller-specific register definitions
#include <stdint.h> // Standard integer type definitions

// Define the memory-mapped address to store the factorial result
#define RESULT_ADDR ((volatile unsigned long*)0x40000000)

// Define the number whose factorial will be calculated
#define FACT_NUM 5

// Function to calculate factorial using a while loop
unsigned long factorial_while(int n) {
    unsigned long result = 1; // Initialize the result variable to 1
    while (n > 1) { // Continue loop as long as n > 1
        result *= n--; // Multiply result by n, then decrement n
    }
    return result; // Return the final computed factorial
}

int main(void) {
    volatile unsigned long *dst = RESULT_ADDR; // Pointer to result memory address
    dst[0] = factorial_while(FACT_NUM); // Store factorial value at 0x40000000
    while (1) {} // Infinite loop to hold program execution
}
