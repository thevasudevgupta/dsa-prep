#include <iostream>
// Binary search (array needs to be sorted)

// O(log(n)) ; O(1)
int bsearch(int arr[], int val, int low, int high) {
    int mid = (low + high) / 2;
    if (low == high && arr[mid] != val) {
        return -1;
    }
    if (arr[mid] == val) {return mid;}
    else if (arr[mid] > val) {
        high = mid - 1;
        return bsearch(arr, val, low, high);
    }
    else {
        low = mid + 1;
        return bsearch(arr, val, low, high);
    }
}

int main() {
    int arr[] = {4, 5, 8, 10, 33, 44, 52, 89, 100, 2012, 10000};
    int val = 53;
    int low = 0, high = sizeof(arr) / sizeof(*arr);

    std::cout << bsearch(arr, val, low, high) << std::endl;
}
