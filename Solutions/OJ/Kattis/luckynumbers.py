# n = int(input())    

for n in range(1, 40):

    res = 0

    def dfs(num, depth):

        global res

        if depth == n:
            res += 1
            return

        lo = 1 if depth == 0 else 0

        for i in range(lo, 10):
            t = num * 10 + i
            if t % (depth + 1) == 0:
                dfs(t, depth + 1)

    dfs(0, 0)
    print("n",n,"res",res)

