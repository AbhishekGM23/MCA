#include <LPC214x.h>   // include LPC2148 header file

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function used by Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];   // choose last element as pivot
    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Quick Sort function (recursive)
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int data[5] = {25, 10, 30, 5, 15};  // unsorted array

    quickSort(data, 0, 4);  // sort array

    while (1);  // stop here to check output in Keil memory window
}