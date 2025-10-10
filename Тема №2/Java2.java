import java.util.*;

class WeightedGraph {
    private int vertices;
    private List<List<Edge>> adjList;

    // Класс для представления ребра
    static class Edge {
        int target;
        int weight;
        
        Edge(int target, int weight) {
            this.target = target;
            this.weight = weight;
        }
    }

    // Класс для приоритетной очереди
    static class Node implements Comparable<Node> {
        int vertex;
        int distance;
        
        Node(int vertex, int distance) {
            this.vertex = vertex;
            this.distance = distance;
        }
        
        @Override
        public int compareTo(Node other) {
            return Integer.compare(this.distance, other.distance);
        }
    }

    public WeightedGraph(int v) {
        this.vertices = v;
        this.adjList = new ArrayList<>();
        for (int i = 0; i < v; i++) {
            adjList.add(new ArrayList<>());
        }
    }

    // Добавление взвешенного ребра
    public void addEdge(int u, int v, int weight) {
        adjList.get(u).add(new Edge(v, weight));
        adjList.get(v).add(new Edge(u, weight)); // Для неориентированного графа
    }

    // Алгоритм Дейкстры
    public int[] dijkstra(int start) {
        int[] distance = new int[vertices];
        Arrays.fill(distance, Integer.MAX_VALUE);
        PriorityQueue<Node> pq = new PriorityQueue<>();

        distance[start] = 0;
        pq.add(new Node(start, 0));

        while (!pq.isEmpty()) {
            Node node = pq.poll();
            int current = node.vertex;
            int dist = node.distance;

            if (dist > distance[current]) continue;

            for (Edge edge : adjList.get(current)) {
                int next = edge.target;
                int newDist = dist + edge.weight;

                if (newDist < distance[next]) {
                    distance[next] = newDist;
                    pq.add(new Node(next, newDist));
                }
            }
        }

        return distance;
    }

    // Вывод кратчайших путей
    public void printShortestPaths(int start) {
        int[] distances = dijkstra(start);
        
        System.out.println("Кратчайшие пути от вершины " + start + ":");
        for (int i = 0; i < vertices; i++) {
            if (distances[i] == Integer.MAX_VALUE) {
                System.out.println("Вершина " + i + ": недостижима");
            } else {
                System.out.println("Вершина " + i + ": " + distances[i]);
            }
        }
    }
}
