import sys
mod = 1000000007
sys.setrecursionlimit(676767)

tc = int(input())
for _ in range(tc):
    n = int(input())
    ch = [(0,0)] * (n + 1)
    for i in range(1, n + 1):
        l, r = map(int, input().split())
        ch[i] = (l, r)

    steps = [0] * (n + 1)

    def dfs1(i):
        if ch[i][0] == 0:
            return 0
        cnt = 4 + dfs1(ch[i][0]) + dfs1(ch[i][1])
        steps[i] = cnt
        return cnt
    
    dfs1(1)

    res = [0] * (n + 1)

    def dfs2(i, cur):            
        cur += steps[i] + 1
        res[i] = cur
        if ch[i][0] != 0:
            dfs2(ch[i][0], cur)
            dfs2(ch[i][1], cur)
    
    dfs2(1, 0)
    for i in range(1, n + 1):
        print(res[i] % (1000000007), end = ' ')
    print()