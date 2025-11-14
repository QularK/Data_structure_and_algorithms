def flip(arr, k):
    left = 0
    while left < k:
        arr[left], arr[k] = arr[k], arr[left]
        left += 1
        k -= 1

def pancake_sort(arr):
    n = len(arr)
    for curr_size in range(n, 1, -1):
        # Находим индекс максимального элемента
        max_index = arr.index(max(arr[:curr_size]))
        if max_index != curr_size - 1:
            # Переворачиваем до максимального элемента
            flip(arr, max_index)
            # Переворачиваем всю текущую часть
            flip(arr, curr_size - 1)
    return arr

# Пример использования
arr = [3, 1, 5, 2, 4]
print("Исходный массив:", arr)
print("Отсортированный массив:", pancake_sort(arr))
