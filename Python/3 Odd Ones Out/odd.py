"Recieves an array of numbers and returns a new array with the even numbers only"
odd_ones_out = lambda numbers: [x for x in numbers if x % 2 == 0]

print(odd_ones_out([1,2,3,4,5,6]))
print(odd_ones_out(range(20)))
print(odd_ones_out([0]))
print(odd_ones_out([-1]))
print(odd_ones_out(range(-19, -2)))