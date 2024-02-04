N=10**6
v=[[] for _ in range(N)]
d=[""]*N
L=1
def f(i):
    print(d[i], end="")
    for x in v[i]:
        f(x)
n=int(input())
for i in range(1,n+1):
    d[i]=input()
for _ in range(n-1):
    l,b=map(int,input().split())
    v[l].append(b)
    L=l
f(L)


