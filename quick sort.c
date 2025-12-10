#include <lpc214x.h>

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];  // pivot element
    int i = (low - 1);
    int j;

    for (j = low; j <= high - 1; j++)
    {
        // If current element is smaller than pivot
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);   // Sort left half
        quickSort(arr, pi + 1, high);  // Sort right half
    }
}

int main(void)
{
    int data[6] = {25, 7, 9, 13, 2, 18};
    int n = 6;

    quickSort(data, 0, n - 1);

    // Place a breakpoint here to see the sorted array
    while(1);
}

