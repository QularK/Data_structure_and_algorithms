#include <queue>
#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>

class WeightedGraph {
private:
    int vertices;
    std::vector<std::vector<std::pair<int, int>>> adjList; // пара: (вершина, вес)

public:
    WeightedGraph(int v) : vertices(v) {
        adjList.resize(v);
    }

    // Добавление взвешенного ребра
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Для неориентированного графа
    }

    // Алгоритм Дейкстры
    std::vector<int> dijkstra(int start) {
        std::vector<int> distance(vertices, std::numeric_limits<int>::max());
        std::priority_queue<std::pair<int, int>, 
                          std::vector<std::pair<int, int>>, 
                          std::greater<std::pair<int, int>>> pq;

        distance[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            int dist = pq.top().first;
            int current = pq.top().second;
            pq.pop();

            if (dist > distance[current]) continue;

            for (auto& neighbor : adjList[current]) {
                int next = neighbor.first;
                int weight = neighbor.second;
                int newDist = dist + weight;

                if (newDist < distance[next]) {
                    distance[next] = newDist;
                    pq.push({newDist, next});
                }
            }
        }

        return distance;
    }

    // Вывод кратчайших путей
    void printShortestPaths(int start) {
        std::vector<int> distances = dijkstra(start);
        
        std::cout << "Кратчайшие пути от вершины " << start << ":\n";
        for (int i = 0; i < vertices; i++) {
            if (distances[i] == std::numeric_limits<int>::max()) {
                std::cout << "Вершина " << i << ": недостижима\n";
            } else {
                std::cout << "Вершина " << i << ": " << distances[i] << "\n";
            }
        }
    }
};
