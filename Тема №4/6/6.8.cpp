#include <iostream>
#include <vector>

using namespace std;

// Функция сортировки выбором
void selectionSort(vector<int> &arr) {
    int n = arr.size();
    
    // Проходим по всем элементам массива
    for (int i = 0; i < n - 1; i++) {
        // Предполагаем, что минимальный элемент - текущий
        int min_index = i;
        
        // Ищем минимальный элемент в оставшейся части
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        
        // Меняем найденный минимальный элемент с первым неотсортированным
        if (min_index != i) {
            swap(arr[i], arr[min_index]);
        }
    }
}

// Функция для вывода массива
void printArray(const vector<int> &arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Создаем тестовый массив
    vector<int> test_array = {64, 25, 12, 22, 11};
    
    cout << "Исходный массив: ";
    printArray(test_array);
    
    // Сортируем массив
    selectionSort(test_array);
    
    cout << "Отсортированный массив: ";
    printArray(test_array);
    
    return 0;
}
