import java.util.*;

public class Graph {
    private int vertices;
    private int[][] adjMatrix;
    private List<List<Integer>> adjList;

    // Конструктор
    public Graph(int v) {
        this.vertices = v;
        
        // Инициализация матрицы смежности
        this.adjMatrix = new int[v][v];
        
        // Инициализация списка смежности
        this.adjList = new ArrayList<>();
        for (int i = 0; i < v; i++) {
            adjList.add(new ArrayList<>());
        }
    }

    // Добавление ребра (для неориентированного графа)
    public void addEdge(int u, int v, int weight) {
        // Для матрицы смежности
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight; // Для ориентированного графа удалить эту строку
        
        // Для списка смежности
        adjList.get(u).add(v);
        adjList.get(v).add(u); // Для ориентированного графа удалить эту строку
    }

    // Перегруженный метод для ребра без веса
    public void addEdge(int u, int v) {
        addEdge(u, v, 1);
    }

    // Добавление ориентированного ребра
    public void addDirectedEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjList.get(u).add(v);
    }

    // Вывод матрицы смежности
    public void printAdjMatrix() {
        System.out.println("Матрица смежности:");
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                System.out.print(adjMatrix[i][j] + " ");
            }
            System.out.println();
        }
    }

    // Вывод списка смежности
    public void printAdjList() {
        System.out.println("Список смежности:");
        for (int i = 0; i < vertices; i++) {
            System.out.print(i + ": ");
            for (int neighbor : adjList.get(i)) {
                System.out.print(neighbor + " ");
            }
            System.out.println();
        }
    }

    // Поиск в ширину (BFS)
    public void BFS(int start) {
        boolean[] visited = new boolean[vertices];
        Queue<Integer> queue = new LinkedList<>();

        System.out.print("BFS начиная с вершины " + start + ": ");
        
        visited[start] = true;
        queue.add(start);

        while (!queue.isEmpty()) {
            int current = queue.poll();
            System.out.print(current + " ");

            for (int neighbor : adjList.get(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.add(neighbor);
                }
            }
        }
        System.out.println();
    }

    // Вспомогательная функция для DFS
    private void DFSUtil(int v, boolean[] visited) {
        visited[v] = true;
        System.out.print(v + " ");

        for (int neighbor : adjList.get(v)) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    // Поиск в глубину (DFS)
    public void DFS(int start) {
        boolean[] visited = new boolean[vertices];
        System.out.print("DFS начиная с вершины " + start + ": ");
        DFSUtil(start, visited);
        System.out.println();
    }

    // Проверка на связность
    public boolean isConnected() {
        boolean[] visited = new boolean[vertices];
        Queue<Integer> queue = new LinkedList<>();
        
        visited[0] = true;
        queue.add(0);

        while (!queue.isEmpty()) {
            int current = queue.poll();

            for (int neighbor : adjList.get(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.add(neighbor);
                }
            }
        }

        for (boolean v : visited) {
            if (!v) return false;
        }
        return true;
    }
}
