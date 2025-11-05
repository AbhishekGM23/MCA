/********************************************************
 * Program       : Factorial Using Recursion
 * Description   : Calculates factorial of a number recursively; writes result to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Recursive implementation.
 ********************************************************/

#include <LPC214x.h> // LPC214x microcontroller header file (register definitions)
#include <stdint.h> // Standard integer data type definitions

// Define the memory-mapped address to store the computed factorial result
#define RESULT_ADDR ((volatile unsigned long*)0x40000000)

// Define the number whose factorial will be calculated
#define FACT_NUM 5

// Recursive function to calculate factorial
unsigned long factorial_rec(int n) {
    if (n <= 1) // Base case: factorial(0) and factorial(1) = 1
        return 1;
    return n * factorial_rec(n - 1); // Recursive call: n * factorial(n-1)
}

int main(void) {
    volatile unsigned long *dst = RESULT_ADDR; // Pointer to result memory location
    dst[0] = factorial_rec(FACT_NUM); // Store calculated factorial at 0x40000000
    while (1) {} // Infinite loop to halt program execution
}
