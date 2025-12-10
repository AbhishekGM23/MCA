#include <lpc214x.h>

// Returns index of target if found, else -1
int binarySearch(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == target)
            return mid;          // Element found

        else if (arr[mid] < target)
            low = mid + 1;       // Search right half
        else
            high = mid - 1;      // Search left half
    }

    return -1;  // Element not found
}

int main(void)
{
    int data[] = {5, 10, 13, 14, 29, 37};  // Sorted array
    int n = 6;

    int target = 10;   // Value to search
    int result;

    result = binarySearch(data, n, target);

    // Place breakpoint here and check 'result'
    // result = 3 for target=14
    while(1);
}
