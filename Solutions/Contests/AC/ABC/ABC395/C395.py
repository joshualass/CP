n = int(input())

a = list(map(int, input().split()))

b = {}

for i in range(n):
    if a[i] not in b:
        b[a[i]] = []
    b[a[i]].append(i)

res = 100000000

for _, l in b.items():
    for i in range(1, len(l)):
        res = min(res, l[i] - l[i-1] + 1)

if res == 100000000:
    res = -1

print(res)