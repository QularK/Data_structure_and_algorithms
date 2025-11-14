import java.util.*;

public class BeadSort {
    public static void beadSort(int[] arr) {
        int max = Arrays.stream(arr).max().getAsInt();
        int n = arr.length;
        int[][] beads = new int[n][max];

        // Расставляем бусины
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < arr[i]; j++) {
                beads[i][j] = 1;
            }
        }

        // Бусины падают
        for (int j = 0; j < max; j++) {
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += beads[i][j];
                beads[i][j] = 0;
            }
            for (int i = n - sum; i < n; i++) {
                beads[i][j] = 1;
            }
        }

        // Считываем результат
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < max && beads[i][j] == 1; j++) {
                count++;
            }
            arr[i] = count;
        }
    }

    public static void main(String[] args) {
        int[] arr = {4, 2, 3, 1};
        System.out.println("Исходный массив: " + Arrays.toString(arr));
        beadSort(arr);
        System.out.println("Отсортированный массив: " + Arrays.toString(arr));
    }
}
