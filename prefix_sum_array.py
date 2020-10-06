# prefix_sum_array.py
# Produces a one-dimensional prefix sum array from a 
# given list of numbers.

# Read inputted numbers
nums = list(map(int, input().split()))

n = len(nums)

# Initialize PSA to a list containing just first element
psa = [ nums[0] ]

# Populate the list
for i in range(1, n):
  psa.append(psa[-1] + nums[i])

print(str.join(' ', map(str, psa)))
