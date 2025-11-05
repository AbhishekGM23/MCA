/********************************************************
 * Program       : Jump Search Demo
 * Description   : Performs jump search on a sorted array; 
 *                 writes index (-1 if not found) to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 ********************************************************/
#include <LPC214x.h>
#include <stdint.h>
#include <math.h>

/* Memory-mapped output address to store result for observation */
#define RESULT_ADDR ((volatile int*)0x40000000)

static int min(int a, int b) {
    return (a < b) ? a : b;
}

static int jump_search(const int *arr, int size, int key) {
    int step = (int)sqrt(size); // Jump size (block size)
    int prev = 0; // Start index of current block

    /* Identify the block where the key may be present */
    while (arr[min(step, size) - 1] < key) {
        prev = step;
        step += (int)sqrt(size);
        if (prev >= size)
            return -1; // Reached end, key not found
    }

    /* Perform linear search within the identified block */
    while (arr[prev] < key) {
        prev++;
        if (prev == min(step, size))
            return -1; // Key not found within block
    }

    /* Check if current element matches the key */
    if (arr[prev] == key)
        return prev; // Return index if key found

    return -1; // Key not found
}

int main(void) {
    /* Predefined sorted array for jump search algorithm */
    const int arr[] = {5, 10, 15, 20, 25, 30, 35};
    const int n = sizeof(arr) / sizeof(arr[0]);  // Total elements
    const int key = 30; // Element to search

    int index = jump_search(arr, n, key); // Perform jump search

    /* Store the search result index to 0x40000000 (debug/observation) */
    *RESULT_ADDR = index;

    while (1) {}  // Infinite loop to hold result
}
