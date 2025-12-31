#include <iostream>
using namespace std;

int fibonacciSearch(int arr[], int n, int target) {
    int fibMMm2 = 0;   // (m-2)'th Fibonacci
    int fibMMm1 = 1;   // (m-1)'th Fibonacci
    int fibM = fibMMm2 + fibMMm1;  // m'th Fibonacci

    // Find the smallest Fibonacci number >= n
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (arr[i] < target) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (arr[i] > target) {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else {
            return i;
        }
    }

    // Check last possible element
    if (fibMMm1 && offset + 1 < n && arr[offset + 1] == target)
        return offset + 1;

    return -1;
}

int main() {
    int arr[] = {5, 15, 25, 35, 45, 55, 65};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 35;

    int index = fibonacciSearch(arr, n, target);

    if (index != -1)
        cout << "Element found at index " << index << endl;
    else
        cout << "Element not found" << endl;

    return 0;
}
