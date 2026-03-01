tc = int(input())

for _ in range(tc):
    n = int(input())
    a = list(map(int, input().split()))

    res = [0] * n

    for i in range(1, n - 1):
        res[i] = (a[i-1] + a[i+1] - a[i] * 2) // 2
    
    sub_one = 0
    for i in range(0, n - 1):
        sub_one += i * res[i]
    res[n-1] = (a[0] - sub_one) // (n - 1)
    sub_two = 0
    for i in range(0, n - 1):
        sub_two += i * res[n-1-i]
    res[0] = (a[n-1] - sub_two) // (n - 1)
    # print(res)
    for x in res:
        print(x, end = ' ')
    print()