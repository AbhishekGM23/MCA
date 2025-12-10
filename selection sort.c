#include <lpc214x.h>

void selectionSort(int arr[], int n)
{
    int i, j, minIndex, temp;

    for (i = 0; i < n - 1; i++)
    {
        minIndex = i;

        // Find the minimum element in the remaining array
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element
        temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}

int main(void)
{
    int data[6] = {29, 10, 14, 37, 13, 5};
    int n = 6;

    selectionSort(data, n);

    // Place a breakpoint here to view sorted array in debugger
    while(1);
}

