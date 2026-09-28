import heapq

inf = int(1e18)

n, m, x = map(int, input().split())

adj = [[[] for i in range(n)] for j in range(2)]

# print("adj",adj)

for i in range(m):
    u, v = map(int, input().split())
    u -= 1
    v -= 1
    adj[0][u].append(v)
    adj[1][v].append(u)

dp = [[inf for i in range(n)] for j in range(2)]

# print("dp",dp)

pq = []

heapq.heappush(pq, (0, 0, 0))

while pq:
    cost, i, mode = heapq.heappop(pq)

    if dp[mode][i] != inf:
        continue

    dp[mode][i] = cost

    #try toggling types
    if dp[mode ^ 1][i] == inf:
        heapq.heappush(pq, (cost + x, i, mode ^ 1))

    #go to all nei
    for nei in adj[mode][i]:
        if dp[mode][nei] == inf:
            heapq.heappush(pq, (cost + 1, nei, mode))

print(min(dp[0][n-1], dp[1][n-1]))