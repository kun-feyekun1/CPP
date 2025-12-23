#include <iostream>
using namespace std;

int binarySearchArray(int arr[], int n, int key){
    int l=0, r=n-1;
    while(l<=r){
        int mid = l + (r-l)/2;
        if(arr[mid]==key) return mid;
        else if(arr[mid]<key) l=mid+1;
        else r=mid-1;
    }
    return -1;
}

int main(){
    int n; cout << "Enter sorted array size: "; cin >> n;
    int arr[n];
    cout << "Enter sorted array elements:\n";
    for(int i=0;i<n;i++) cin >> arr[i];

    int key; cout << "Enter key to search: "; cin >> key;

    int idx = binarySearchArray(arr, n, key);
    if(idx>=0) cout << "Found at index: " << idx << "\n";
    else cout << "Not found\n";
}
