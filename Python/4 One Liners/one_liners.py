from functools import reduce

"Sums all the values of an array"
sum_of_array = lambda array: reduce(lambda a, b: a + b, array)

"Returns whether a number is a palindrome"
is_palindrome = lambda n: str(n) == str(n)[::-1]

"Returns the factorial of a number"
fact = lambda n: 1 if n == 1 else fact(n - 1) * n

print(sum_of_array([1,2,3,4,5]))
print(is_palindrome(123))
print(is_palindrome(12321))
print(fact(6))
