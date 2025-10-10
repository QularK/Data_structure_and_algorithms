#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <limits>

class Graph {
private:
    int vertices;
    std::vector<std::vector<int>> adjMatrix;
    std::vector<std::vector<int>> adjList;

public:
    // Конструктор
    Graph(int v) : vertices(v) {
        // Инициализация матрицы смежности
        adjMatrix.resize(v, std::vector<int>(v, 0));
        
        // Инициализация списка смежности
        adjList.resize(v);
    }

    // Добавление ребра (для неориентированного графа)
    void addEdge(int u, int v, int weight = 1) {
        // Для матрицы смежности
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; // Для ориентированного графа удалить эту строку
        
        // Для списка смежности
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Для ориентированного графа удалить эту строку
    }

    // Добавление ориентированного ребра
    void addDirectedEdge(int u, int v, int weight = 1) {
        adjMatrix[u][v] = weight;
        adjList[u].push_back(v);
    }

    // Вывод матрицы смежности
    void printAdjMatrix() {
        std::cout << "Матрица смежности:\n";
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                std::cout << adjMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Вывод списка смежности
    void printAdjList() {
        std::cout << "Список смежности:\n";
        for (int i = 0; i < vertices; i++) {
            std::cout << i << ": ";
            for (int neighbor : adjList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    // Поиск в ширину (BFS)
    void BFS(int start) {
        std::vector<bool> visited(vertices, false);
        std::queue<int> q;

        std::cout << "BFS начиная с вершины " << start << ": ";
        
        visited[start] = true;
        q.push(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            std::cout << current << " ";

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        std::cout << std::endl;
    }

    // Вспомогательная функция для DFS
    void DFSUtil(int v, std::vector<bool>& visited) {
        visited[v] = true;
        std::cout << v << " ";

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    // Поиск в глубину (DFS)
    void DFS(int start) {
        std::vector<bool> visited(vertices, false);
        std::cout << "DFS начиная с вершины " << start << ": ";
        DFSUtil(start, visited);
        std::cout << std::endl;
    }

    // Проверка на связность
    bool isConnected() {
        std::vector<bool> visited(vertices, false);
        std::queue<int> q;
        
        visited[0] = true;
        q.push(0);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        for (bool v : visited) {
            if (!v) return false;
        }
        return true;
    }
};
