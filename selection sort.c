/********************************************************
 * Program       : Selection Sort Demo
 * Description   : Implements selection sort; stores sorted array at 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Final result is written to 0x40000000.
 *                 - For sorting: the sorted array is copied
 *                   starting at 0x40000000 (word-aligned).
 *                 
 ********************************************************/
#include <LPC214x.h>
#include <stdint.h>

#define RESULT_ADDR ((volatile int*)0x40000000)

static void selection_sort(int *arr, int n) {
    int i, j, min_idx, temp;

    /* Move the boundary of the unsorted subarray one by one */
    for (i = 0; i < n - 1; i++) {
        min_idx = i; // Assume current index as minimum

        /* Find the index of the smallest element in the remaining unsorted part */
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j; // Update index of new minimum
            }
        }

        /* Swap the found minimum element with the first element */
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main(void) {
    /* Input array to be sorted */
    int arr[] = {64, 25, 12, 22, 11};
    const int n = sizeof(arr) / sizeof(arr[0]); // Calculate number of elements
    volatile int *dst = RESULT_ADDR; // Pointer to output memory location
    int i;

    /* Perform in-place selection sort */
    selection_sort(arr, n);
    for (i = 0; i < n; i++) {
        dst[i] = arr[i];
    }

    while (1) {} // Infinite loop to retain result
}
