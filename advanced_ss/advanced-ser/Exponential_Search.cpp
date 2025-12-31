#include <iostream>
using namespace std;

int binarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int exponentialSearch(int arr[], int n, int target) {
    if (arr[0] == target)
        return 0;

    int i = 1;
    while (i < n && arr[i] <= target)
        i *= 2;

    return binarySearch(arr, i / 2, min(i, n - 1), target);
}

int main() {
    int arr[] = {2, 4, 8, 16, 32, 64, 128};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 32;

    int index = exponentialSearch(arr, n, target);

    if (index != -1)
        cout << "Element found at index " << index << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
