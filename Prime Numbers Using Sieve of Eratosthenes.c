/********************************************************
 * Program       : Prime Numbers Using Sieve of Eratosthenes
 * Description   : Generates primes up to N using Sieve; writes list ending with -1 at 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Efficient prime generation using sieve.
 ********************************************************/

#include <LPC214x.h> // LPC214x microcontroller register definitions
#include <stdint.h> // For standard integer definitions
#include <string.h> // For memset function

// Define memory-mapped address to store the resulting prime list
#define RESULT_ADDR ((volatile int*)0x40000000)

// Define the upper limit for generating prime numbers
#define N 50

int main(void) {
    // Static array to hold prime flags (1 = prime, 0 = not prime)
    static int prime[N+1];

    // Pointer to the output memory location
    volatile int *dst = RESULT_ADDR;

    int i, j, idx = 0; // Loop variables and index for writing primes

    // Initialize all elements of the array to 1 (assume all are prime initially)
    memset(prime, 1, sizeof(prime));

    // 0 and 1 are not prime by definition
    prime[0] = 0;
    prime[1] = 0;

    // Main loop for the Sieve of Eratosthenes algorithm
    for (i = 2; i * i <= N; i++) {
        if (prime[i]) { // If i is still marked as prime
            for (j = i * i; j <= N; j += i) {
                prime[j] = 0; // Mark all multiples of i as non-prime
            }
        }
    }

    // Collect all numbers that remain marked as prime and store them sequentially
    for (i = 2; i <= N; i++) {
        if (prime[i])
            dst[idx++] = i; // Write prime number to memory
    }

    dst[idx] = -1; // Write sentinel (-1) to mark end of prime list

    while (1) {} // Halt program execution (infinite loop)
}
