/********************************************************
 * Program       : Fibonacci Using Dynamic Programming
 * Description   : Computes first N Fibonacci numbers using DP; writes sequence to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Avoids recursion overhead using DP array.
 ********************************************************/

#include <LPC214x.h> // Include LPC214x microcontroller header file
#include <stdint.h> // Include standard integer type definitions

// Define the base memory address to store resulting Fibonacci sequence
#define RESULT_ADDR ((volatile int*)0x40000000)

// Define the number of Fibonacci terms to compute
#define FIB_N 5

int main(void) {
    volatile int *dst = RESULT_ADDR; // Pointer to memory address for storing results
    int fib[FIB_N], i; // Array to store computed Fibonacci series

    fib[0] = 0; // Initialize first Fibonacci term
    fib[1] = 1; // Initialize second Fibonacci term

    // Compute Fibonacci sequence using the bottom-up dynamic programming approach
    for (i = 2; i < FIB_N; i++) {
        fib[i] = fib[i - 1] + fib[i - 2]; // Each term = sum of previous two terms
    }

    // Write computed Fibonacci sequence to memory starting from 0x40000000
    for (i = 0; i < FIB_N; i++) {
        dst[i] = fib[i]; // Store each term sequentially
    }

    while (1) {} // Infinite loop to halt program execution
}
