#include <iostream>
using namespace std;

// Manual integer square root
int intSqrt(int n) {
    int i = 1;
    while (i * i <= n)
        i++;
    return i - 1;
}

int jumpSearch(int arr[], int n, int target) {
    int step = intSqrt(n);
    int prev = 0;

    while (prev < n && arr[min(step, n) - 1] < target) {
        prev = step;
        step += intSqrt(n);
        if (prev >= n)
            return -1;
    }

    for (int i = prev; i < min(step, n); i++) {
        if (arr[i] == target)
            return i;
    }
    return -1;
}

int main() {
    int arr[] = {1,3,5,7,9,11,13};
    int n = 7;

    cout << jumpSearch(arr, n, 11);
    return 0;
}
