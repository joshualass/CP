tc = int(input())

for _ in range(tc):
    n = int(input())

    arr = list(map(int, input().split()))
    vis = [0] * (n + 1)
    arr = [-1] + arr
    res = [0] * (n + 1)

    for i in range(n + 1):
        vals = []
        idxs = []
        cur = i
        while cur <= n and vis[cur] == False:
            vis[cur] = True
            # temp.append((arr[cur], cur))
            vals.append(arr[cur])
            idxs.append(cur)
            cur *= 2

        # temp.sort()

        # print("sorted temp", temp)
        vals.sort()

        for i in range(len(idxs)):
            res[idxs[i]] = vals[i]

    ok = True

    # print("res", res)

    for i in range(1, n + 1):
        if res[i-1] > res[i]:
            ok = False

    if ok:
        print("YES")
    else:
        print("NO")