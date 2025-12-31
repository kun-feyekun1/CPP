#include <iostream>
using namespace std;

int interpolationSearch(int arr[], int n, int target) {
    int low = 0;
    int high = n - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {

        // Avoid division by zero
        if (arr[high] == arr[low])
            return (arr[low] == target) ? low : -1;

        // Probing the position
        int pos = low + ((double)(high - low) /
                         (arr[high] - arr[low])) *
                         (target - arr[low]);

        if (arr[pos] == target)
            return pos;

        if (arr[pos] < target)
            low = pos + 1;
        else
            high = pos - 1;
    }

    return -1; // Not found
}

int main() {
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 40;

    int index = interpolationSearch(arr, n, target);

    if (index != -1)
        cout << "Element found at index " << index << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
