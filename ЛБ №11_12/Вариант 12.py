def generate_combinations(n, k, start=1, current=None, result=None):
    if current is None:
        current = []
    if result is None:
        result = []
    if len(current) == k:
        result.append(current[:])
        return
    for i in range(start, n + 1):
        current.append(i)
        generate_combinations(n, k, i + 1, current, result)
        current.pop()
    return result

n, k = 4, 2
combs = generate_combinations(n, k)
print(f"Сочетания из {n} по {k}: {combs}")
