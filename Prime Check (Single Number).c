/********************************************************
 * Program       : Prime Check (Single Number)
 * Description   : Checks if a given number is prime; writes 1 (prime) or 0 (not prime) to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Result 1 or 0 written to 0x40000000.
 ********************************************************/

#include <LPC214x.h> // Header file for LPC214x register definitions
#include <stdint.h> // Standard integer type definitions

// Define memory-mapped address to store the result
#define RESULT_ADDR ((volatile int*)0x40000000)

// Define the number to check for primality
#define NUM 9
int i;
// Function to check if a number is prime
static int is_prime(int n) {
    if (n < 2) return 0; // Numbers less than 2 are not prime
    for (i = 2; i * i <= n; i++) { // Check divisibility up to sqrt(n)
        if (n % i == 0) // If divisible, it is not prime
            return 0;
    }
    return 1; // If no divisors found, number is prime
}

int main(void) {
    volatile int *dst = RESULT_ADDR; // Pointer to memory-mapped result address
    dst[0] = is_prime(NUM); // Store result (1 or 0) at 0x40000000
    while (1) {} // Infinite loop to halt program execution
}
