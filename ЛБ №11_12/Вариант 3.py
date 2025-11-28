def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a % b)

a, b = 56, 98
print(f"НОД({a}, {b}) = {gcd(a, b)}")
