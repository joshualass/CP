N, M = map(int, input().split())
if N > M:
    N,M = M,N  
for i in range(N + 1, M + 2):
    print(i)