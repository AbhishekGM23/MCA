/********************************************************
 * Program       : Prime Numbers List (Range)
 * Description   : Finds all prime numbers from 2 up to N; writes list ending with -1 at 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Prime list in memory ending with sentinel -1.
 ********************************************************/

#include <LPC214x.h> // Header file for LPC214x microcontroller register definitions
#include <stdint.h> // Standard integer type definitions

// Define base address where prime results will be stored
#define RESULT_ADDR ((volatile int*)0x40000000)

// Define the upper range value for prime calculation
#define N 50

// Function to check whether a given number 'n' is prime
int i;
static int is_prime(int n) {
    if (n < 2) return 0; // Numbers below 2 are not prime
    for (i = 2; i * i <= n; i++) { // Check divisibility up to sqrt(n)
        if (n % i == 0) // If divisible, it's not prime
            return 0;
    }
    return 1; // If no divisors found, number is prime
}

int main(void) {
    volatile int *dst = RESULT_ADDR; // Pointer to memory location 0x40000000
    int idx = 0; // Index for storing primes sequentially

    // Loop through all numbers from 2 up to N inclusive
		int num;
    for (num = 2; num <= N; num++) {
        if (is_prime(num)) { // If number is prime
            dst[idx++] = num; // Store the prime in memory
        }
    }

    dst[idx] = -1; // Write sentinel value (-1) to mark end of list
    while (1) {} // Infinite loop to halt program
}
