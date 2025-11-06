/********************************************************
 * Program       : Bubble Sort Demo
 * Description   : Implements bubble sort; stores sorted array at 0x40000000.
 * Author        : Abhaya Y, Abhishek G M
 * Board         : ARM7
 * Processor     : LPC2148
 * Notes         : Final result is written to 0x40000000.
 *                 - For sorting: the sorted array is copied
 *                   starting at 0x40000000 (word-aligned).
 ********************************************************/
#include <LPC214x.h>
#include <stdint.h>

#define RESULT_ADDR ((volatile int*)0x40000000)

static void bubble_sort(int *arr, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) { // Outer loop for each pass
        for (j = 0; j < n - i - 1; j++) { // Inner loop for comparison
            if (arr[j] > arr[j + 1]) { // Swap if elements out of order
                int t    = arr[j];
                arr[j]   = arr[j + 1];
                arr[j+1] = t;
            }
        }
    }
}

int main(void) {
    /* Input array: elements to be sorted */
    int arr[] = {5, 1, 4, 2, 8};
    const int n = sizeof(arr) / sizeof(arr[0]); // Total number of elements
    volatile int *dst = RESULT_ADDR; // Pointer to output location
    int i;

    /* Perform in-place bubble sort on the array */
    bubble_sort(arr, n);
    for (i = 0; i < n; i++) {
        dst[i] = arr[i];
    }

    while (1) {} // Infinite loop to hold result
}
