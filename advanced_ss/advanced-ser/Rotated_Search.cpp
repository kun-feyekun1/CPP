#include <iostream>
using namespace std;

int rotatedSearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid] == target)
            return mid;

        // Left half sorted
        if (arr[low] <= arr[mid]) {
            if (target >= arr[low] && target < arr[mid])
                high = mid - 1;
            else
                low = mid + 1;
        }
        // Right half sorted
        else {
            if (target > arr[mid] && target <= arr[high])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int arr[] = {6,7,8,1,2,3,4,5};
    int n = 8;

    cout << rotatedSearch(arr, n, 3);
    return 0;
}
