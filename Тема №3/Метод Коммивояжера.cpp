#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Функция для вычисления длины пути
int calculatePathLength(const vector<vector<int>>& graph, const vector<int>& path) {
    int length = 0;
    int n = path.size();
    
    for (int i = 0; i < n - 1; i++) {
        length += graph[path[i]][path[i + 1]];
    }
    // Возвращаемся в начальный город
    length += graph[path[n - 1]][path[0]];
    
    return length;
}

// Метод полного перебора
void tspBruteForce(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> cities(n);
    
    // Инициализируем вектор городов: 0, 1, 2, ..., n-1
    for (int i = 0; i < n; i++) {
        cities[i] = i;
    }
    
    int minDistance = INT_MAX;
    vector<int> bestPath;
    
    // Перебираем все перестановки
    do {
        int currentDistance = calculatePathLength(graph, cities);
        
        if (currentDistance < minDistance) {
            minDistance = currentDistance;
            bestPath = cities;
        }
    } while (next_permutation(cities.begin() + 1, cities.end())); // Фиксируем первый город
    
    // Выводим результат
    cout << "Минимальное расстояние: " << minDistance << endl;
    cout << "Оптимальный маршрут: ";
    for (int city : bestPath) {
        cout << city << " ";
    }
    cout << bestPath[0] << endl; // Замыкаем цикл
}

int main() {
    // Пример матрицы расстояний (4 города)
    vector<vector<int>> graph = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    cout << "Решение методом полного перебора:" << endl;
    tspBruteForce(graph);
    
    return 0;
}
