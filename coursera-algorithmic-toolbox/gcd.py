# Uses python3
a, b = map(int, input().split())
a, b = min(a, b), max(a, b) % min(a, b)
while b:
	a, b = b, a % b
print(a)
