# bogosort.py
# Sort a given list of integers in ascending order.

from random import shuffle

# Read in a line of integers delimited by spaces
nums = list(map(int, input().split()))
n = len(nums)

while any(nums[i] > nums[i + 1] for i in range(n - 1)):
  shuffle(nums)
 
# Print sorted list delimited by spaces
print(str.join(' ', map(str, nums)))
