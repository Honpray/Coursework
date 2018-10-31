# Uses python3
n = int(input())

fiblist= [0,1]
for i in range(1, n):
	fiblist.append(fiblist[i-1]+fiblist[i])

print(fiblist[n])

#0 1 1 2 3 5