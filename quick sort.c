/********************************************************
 * Program       : Quick Sort Demo
 * Description   : Implements quick sort (divide and conquer);
 *                 stores sorted array at 0x40000000.
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
	
static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = (low - 1); // Index of smaller element
    int j;

    /* Traverse array and rearrange elements relative to the pivot */
    for (j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {  // If current element is smaller than pivot
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    /* Place the pivot element in its correct position */
    swap(&arr[i + 1], &arr[high]);
    return (i + 1); // Return pivot index
}

static void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); // Partition the array
        quick_sort(arr, low, pi - 1); // Sort left sub-array
        quick_sort(arr, pi + 1, high); // Sort right sub-array
    }
}

int main(void) {
    /* Input array to be sorted */
    int arr[] = {33, 12, 98, 56, 7, 41, 67, 25};
    const int n = sizeof(arr) / sizeof(arr[0]); // Determine array size
    volatile int *dst = RESULT_ADDR; // Output location pointer
    int i;

    /* Perform in-place Quick Sort in ascending order */
    quick_sort(arr, 0, n - 1);

    for (i = 0; i < n; i++) {
        dst[i] = arr[i];
    }

    while (1) {} // Infinite loop to preserve result
}
