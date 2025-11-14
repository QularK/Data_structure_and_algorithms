#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

int jumpSearch(vector<int>& arr, int target) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < target) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

    while (arr[prev] < target) {
        prev++;
        if (prev == min(step, n)) return -1;
    }

    if (arr[prev] == target) return prev;
    return -1;
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
    int target = 7;
    int index = jumpSearch(arr, target);
    cout << "Индекс элемента " << target << ": " << index << endl;
    return 0;
}
