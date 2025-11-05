/********************************************************
 * Program       : Fibonacci Using Recursion (Single Value)
 * Description   : Calculates Nth Fibonacci number using recursion; writes result to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Recursive approach, computes only nth term.
 ********************************************************/

#include <LPC214x.h> // Header for LPC214x microcontroller register definitions
#include <stdint.h> // Standard integer type definitions

// Define the memory address to store the computed Fibonacci result
#define RESULT_ADDR ((volatile int*)0x40000000)

// Define which Fibonacci term to compute
#define FIB_N 5

// Recursive function to compute the nth Fibonacci number
int fibonacci_rec(int n) {
    if (n <= 0) return 0; // Base case: Fibonacci(0) = 0
    if (n == 1) return 1; // Base case: Fibonacci(1) = 1
    return fibonacci_rec(n - 1) + fibonacci_rec(n - 2); // Recursive relation
}

int main(void) {
    volatile int *dst = RESULT_ADDR; // Pointer to memory-mapped output address
    dst[0] = fibonacci_rec(FIB_N); // Compute nth Fibonacci term and store at 0x40000000
    while (1) {} // Infinite loop to stop execution
}
