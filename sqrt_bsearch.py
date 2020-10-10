# sqrt_bsearch.py
# Calculates the square root of a given integer using binary search
# with an error of 10^-6


DELTA = 1e-6

n = int(input())
left, right = 0, n

while True:
	mid = (right + left) / 2
	sqr = mid * mid
	if abs(sqr - n) < DELTA:
		break
	elif sqr > n:
		right = mid
	else:
		left = mid

print(mid)
