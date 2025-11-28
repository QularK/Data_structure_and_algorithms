def is_palindrome(s):
    s = s.lower().replace(" ", "")
    if len(s) <= 1:
        return True
    if s[0] != s[-1]:
        return False
    return is_palindrome(s[1:-1])

test_str = "А роза упала на лапу Азора"
print(f"'{test_str}' -> {is_palindrome(test_str)}")
