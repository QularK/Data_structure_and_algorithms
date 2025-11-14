#include <iostream>
#include <vector>
using namespace std;

int binarySearch(vector<int>& arr, int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int exponentialSearch(vector<int>& arr, int target) {
    int n = arr.size();
    if (arr[0] == target) return 0;

    int i = 1;
    while (i < n && arr[i] <= target) {
        i *= 2;
    }

    return binarySearch(arr, i / 2, min(i, n - 1), target);
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
    int target = 9;
    int index = exponentialSearch(arr, target);
    cout << "Индекс элемента " << target << ": " << index << endl;
    return 0;
}
