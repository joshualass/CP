n = int(input())

a = list(map(int, input().split()))
ok = 1
for i in range(1, n):
    if a[i-1] >= a[i]:
        ok = 0

if ok == 1:
    print("Yes")
else:
    print("No")