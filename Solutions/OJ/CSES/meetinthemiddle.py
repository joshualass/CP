# reading input

n, x = map(int, input().split())

a = list(map(int, input().split()))

left_size = (n + 1) // 2
right_size = n // 2

left_array = a[0:left_size]
right_array = a[left_size:]

#the dictionaries store the number of ways to make every sum from a group

left_dictionary = {}
right_dictionary = {}

for i in range(0, 1 << left_size):
    s = 0
    for j in range(left_size):
        if ((i >> j) & 1): #if it's in the subset for the bitmask i, representing the subsequence
            s += left_array[j]

    if s not in left_dictionary:
        left_dictionary[s] = 0

    left_dictionary[s] += 1

# repeat for the right group

for i in range(0, 1 << right_size):
    s = 0
    for j in range(right_size):
        if ((i >> j) & 1):
            s += right_array[j]

    if s not in right_dictionary:
        right_dictionary[s] = 0

    right_dictionary[s] += 1

answer = 0

for key, value in left_dictionary.items():
    #our goal is to sum to x
    #if our key is the sum of the left partition, then we need x - key from the right partition
    target = x - key
    if target in right_dictionary:
        answer += value * right_dictionary[target]

print(answer)

# res = 0

# #iterate over all subsets
# #numbers 0 to 2^n - 1
# for i in range(0, 1 << n):
#     s = 0
#     for j in range(n):
#         if ((i >> j) & 1):
#             s += a[j]

#     if s == x:
#         res += 1

# print(res)

'''
4 5
1 2 3 2


partition into 2 equal groups
[1 2]

{
    {0, 1},
    {1, 1},
    {2, 1},
    {3, 1}
}


[3 2]

{
    {0, 1},
    {3, 1},
    {2, 1},
    {5, 1}
}

target sum - 5

1 with left group, we need make 4 with the right group

'''