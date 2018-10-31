# Uses python3
import random
from random import randint

def slow(n,a,result=0):

	for i in range(0, n):
		for j in range(i+1, n):
			if a[i]*a[j] > result:
				result = a[i]*a[j]
	return result

def fast(n,a,max1=0,max2=0,index1=-1):
	for i in range(0, n):
		if a[i] > max1:
			max1 = a[i]
			index1=i
	print index1
	for j in range(0, n):
		if a[j]>max2 and j!=index1:
			max2= a[j]
	return max1*max2

n = randint(2,11)
a = []
for i in range(n):
	a.append(randint(0,10))
assert(len(a) == n)


print n
print a
print slow(n,a)
print fast(n,a)