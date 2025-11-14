def bucket_sort(arr):
    if len(arr) == 0:
        return arr

    # Определяем количество корзин
    num_buckets = len(arr)
    max_val, min_val = max(arr), min(arr)
    bucket_range = (max_val - min_val) / num_buckets

    # Создаем корзины
    buckets = [[] for _ in range(num_buckets)]

    # Распределяем элементы по корзинам
    for num in arr:
        index = int((num - min_val) / bucket_range)
        if index == num_buckets:
            index -= 1
        buckets[index].append(num)

    # Сортируем каждую корзину
    for i in range(num_buckets):
        buckets[i].sort()

    # Объединяем корзины
    sorted_arr = []
    for bucket in buckets:
        sorted_arr.extend(bucket)

    return sorted_arr

# Пример использования
arr = [0.42, 0.32, 0.89, 0.11, 0.75]
print("Исходный массив:", arr)
print("Отсортированный массив:", bucket_sort(arr))
