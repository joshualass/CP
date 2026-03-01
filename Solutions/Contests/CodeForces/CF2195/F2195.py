tc = int(input())
for _ in range(tc):
    n = int(input())

    arr = [0] * n
    for i in range(n):
        a, b, c = map(int, input().split())
        arr[i] = (a, b, c, i)

    dp_up = [0] * n

    def intersect(i, j):
        a = arr[i][0] - arr[j][0]
        b = arr[i][1] - arr[j][1]
        c = arr[i][2] - arr[j][2]

        if a == 0 and b == 0:
            return c == 0

        residual = b * b - 4 * a * c


        
        if residual >= 0:
            return True
        else:
            return False

    arr = sorted(arr, key = lambda x: x[2])

    # print("arr", arr)

    for i in range(n):
        prev_best = 0
        for j in range(i):
            if intersect(i, j) == False:
                prev_best = max(prev_best, dp_up[j])
        dp_up[i] = prev_best + 1
    
    dp_down = [0] * n
    for i in range(n - 1, -1, -1):
        prev_best = 0
        for j in range(i + 1, n):
            if intersect(i, j) == False:
                prev_best = max(prev_best, dp_down[j])
        dp_down[i] = prev_best + 1

    # print("dp_up", dp_up)
    # print("dp_down", dp_down)

    res = [0] * n
    
    for i in range(n):
        val = dp_up[i] + dp_down[i] - 1
        res[arr[i][3]] = val

    for i in range(n):
        print(res[i], end = ' ' if i != n - 1 else '\n')
