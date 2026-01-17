#include <iostream>
using namespace std;

int linearSearchArray(int arr[], int n, int key)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            return i;
    return -1;
}

int main()
{
    int n;
    cout << "Enter array size: ";
    cin >> n;
    int arr[n];
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int key;
    cout << "Enter key to search: ";
    cin >> key;

    int idx = linearSearchArray(arr, n, key);
    if (idx >= 0)
        cout << "Found at index: " << idx << "\n";
    else
        cout << "Not found\n";
}
