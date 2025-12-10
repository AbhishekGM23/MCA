#include <lpc214x.h>

void bubbleSort(int arr[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // Swap elements
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(void)
{
    int data[5] = {34, 12, 5, 66, 1};
    int i;

    bubbleSort(data, 5);

    // Optional: place breakpoint here to inspect sorted array
    while(1);
}
