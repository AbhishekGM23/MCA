/********************************************************
 * Program       : Binary Search Demo
 * Description   : Performs binary search on a sorted array; writes index (-1 if not found) to 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Final result is written to 0x40000000.
 *                - For searching: the search index (-1 if not found)
 *                 is written to 0x40000000.
 ********************************************************/
#include <LPC214x.h>
#include <stdint.h>

/* Memory-mapped output address (for simulation or debugging) */
#define RESULT_ADDR ((volatile int*)0x40000000)

static int binary_search(const int *arr, int size, int key) {
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        int mid = (low + high) / 2; // Find mid index

        if (arr[mid] == key)     // Key found at mid
            return mid;
        else if (arr[mid] < key) // Key may lie in right half
            low = mid + 1;
        else                  // Key may lie in left half
            high = mid - 1;
    }
    return -1;          // Key not found
}

int main(void) {
    /* Pre-sorted array for binary search */
    const int arr[] = {5, 10, 15, 20, 25};
    const int n = sizeof(arr) / sizeof(arr[0]);  // Array length
    const int key = 15;                          // Search target value

    int index = binary_search(arr, n, key);      // Perform binary search

    /* Store the found index to address 0x40000000 for observation */
    *RESULT_ADDR = index;

    while (1) {}                                 // Infinite loop to halt program
}
