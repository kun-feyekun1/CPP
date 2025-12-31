#include <iostream>
using namespace std;

int ternarySearch(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        if (arr[mid1] == target)
            return mid1;
        if (arr[mid2] == target)
            return mid2;

        if (target < arr[mid1])
            right = mid1 - 1;
        else if (target > arr[mid2])
            left = mid2 + 1;
        else {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    return -1;
}

int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 10;

    int index = ternarySearch(arr, 0, n - 1, target);

    if (index != -1)
        cout << "Element found at index " << index << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
