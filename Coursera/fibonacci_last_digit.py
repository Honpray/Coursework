# Uses python3
n = int(input())
fiblist_last_digit = [0, 1]
for i in range(1, n):
#here it has to be (1, n) Or erroring message list index out of range
    fiblist_last_digit[0], fiblist_last_digit[1] = fiblist_last_digit[1], (fiblist_last_digit[0]+fiblist_last_digit[1]) % 10
print(fiblist_last_digit[1])

'''
eg. range(1, 3) [1, 2] 2loops    [0, 1, 1, 2]
range(2,3) [2] only 1 loops    [0, 1, ?]    there is no fiblist_last_digit[2] now!!!! 
list index out of range
'''