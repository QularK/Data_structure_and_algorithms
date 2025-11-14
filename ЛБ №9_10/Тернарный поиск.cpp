#include <iostream>
#include <vector>
using namespace std;

int ternarySearch(vector<int>& arr, int left, int right, int target) {
    if (right >= left) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;

        if (arr[mid1] == target) return mid1;
        if (arr[mid2] == target) return mid2;

        if (target < arr[mid1]) {
            return ternarySearch(arr, left, mid1 - 1, target);
        } else if (target > arr[mid2]) {
            return ternarySearch(arr, mid2 + 1, right, target);
        } else {
            return ternarySearch(arr, mid1 + 1, mid2 - 1, target);
        }
    }
    return -1;
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
    int target = 7;
    int index = ternarySearch(arr, 0, arr.size() - 1, target);
    cout << "Индекс элемента " << target << ": " << index << endl;
    return 0;
}
