/********************************************************
 * Program       : Linear Search Demo
 * Description   : Performs linear search; writes found index (-1 if not found) to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Final result is written to 0x40000000.
 *              	 For searching: the search index (-1 if not found) is written to 0x40000000.
 *                   
 ********************************************************/
#include <LPC214x.h>
#include <stdint.h>

#define RESULT_ADDR ((volatile int*)0x40000000)

static int linear_search(const int *arr, int size, int key) {
    int i;
    for (i = 0; i < size; i++) { // Traverse through array elements
        if (arr[i] == key) { // Compare current element with key
            return i; // Return index if match found
        }
    }
    return -1; // Key not found in array
}

int main(void) {
    /* Example sorted array for demonstration */
    const int arr[] = {10, 22, 35, 40, 50};
    const int size = sizeof(arr) / sizeof(arr[0]); // Calculate array size
    const int key = 35; // Key to search in the array

    int index = linear_search(arr, size, key); // Perform linear search
    *RESULT_ADDR = index;

    while (1) {}  // Infinite loop to halt execution after storing result
}

