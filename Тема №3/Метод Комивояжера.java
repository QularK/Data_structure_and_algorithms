import java.util.*;

public class TSPBruteForce {
    
    // Функция для вычисления длины пути
    public static int calculatePathLength(int[][] graph, List<Integer> path) {
        int length = 0;
        int n = path.size();
        
        for (int i = 0; i < n - 1; i++) {
            length += graph[path.get(i)][path.get(i + 1)];
        }
        // Возвращаемся в начальный город
        length += graph[path.get(n - 1)][path.get(0)];
        
        return length;
    }
    
    // Генерация всех перестановок
    public static void generatePermutations(List<Integer> cities, int start, 
                                          List<List<Integer>> allPermutations) {
        if (start == cities.size() - 1) {
            allPermutations.add(new ArrayList<>(cities));
            return;
        }
        
        for (int i = start; i < cities.size(); i++) {
            Collections.swap(cities, start, i);
            generatePermutations(cities, start + 1, allPermutations);
            Collections.swap(cities, start, i);
        }
    }
    
    // Метод полного перебора
    public static void tspBruteForce(int[][] graph) {
        int n = graph.length;
        List<Integer> cities = new ArrayList<>();
        
        // Инициализируем список городов: 0, 1, 2, ..., n-1
        for (int i = 0; i < n; i++) {
            cities.add(i);
        }
        
        List<List<Integer>> allPermutations = new ArrayList<>();
        // Генерируем все перестановки, фиксируя первый город
        List<Integer> remainingCities = new ArrayList<>(cities.subList(1, n));
        generatePermutations(remainingCities, 0, allPermutations);
        
        int minDistance = Integer.MAX_VALUE;
        List<Integer> bestPath = new ArrayList<>();
        
        // Перебираем все перестановки
        for (List<Integer> permutation : allPermutations) {
            List<Integer> currentPath = new ArrayList<>();
            currentPath.add(0); // Всегда начинаем с города 0
            currentPath.addAll(permutation);
            
            int currentDistance = calculatePathLength(graph, currentPath);
            
            if (currentDistance < minDistance) {
                minDistance = currentDistance;
                bestPath = currentPath;
            }
        }
        
        // Выводим результат
        System.out.println("Минимальное расстояние: " + minDistance);
        System.out.print("Оптимальный маршрут: ");
        for (int city : bestPath) {
            System.out.print(city + " ");
        }
        System.out.println(bestPath.get(0)); // Замыкаем цикл
    }
    
    public static void main(String[] args) {
        // Пример матрицы расстояний (4 города)
        int[][] graph = {
            {0, 10, 15, 20},
            {10, 0, 35, 25},
            {15, 35, 0, 30},
            {20, 25, 30, 0}
        };
        
        System.out.println("Решение методом полного перебора:");
        tspBruteForce(graph);
    }
}
