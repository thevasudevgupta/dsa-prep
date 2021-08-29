#include <iostream>
// max subsequence sum

// O(n^3) ; O(1)
int mss1(int a[], int N) {
    int max_sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            int current_sum = 0;
            for (int k = i; k <= j; k++) {
                current_sum += a[k];
            }
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
};


// O(n^2) ; O(1)
int mss2(int a[], int N) {
    int max_sum = 0;
    for (int i = 0; i < N; i++) {
        int current_sum = 0;
        for (int j = i; j < N; j++) {
            current_sum += a[j];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
};


// O(n) ; O(1)
int mss(int a[], int N) {
    int max_sum = 0, current_sum = 0;
    for (int i = 0; i < N; i++) {
        current_sum += a[i];
        if (current_sum > max_sum) {max_sum = current_sum;}
        else if (current_sum < 0) {current_sum = 0;}
    }
    return max_sum;
}


int main() {
    int arr[] = {31, -33, -32, 8, 23, 2, -2};
    int N = sizeof(arr) / sizeof(*arr);

    // std::cout << mss1(arr, N) << " " << mss2(arr, N) << std::endl;
    std::cout << mss(arr, N) << std::endl;
};
