num = int(input())

def solve(lo, hi):
    trynum = num - num // (lo + hi) * (lo + hi)
    if trynum == 0 or trynum == lo:
        return 1
    else:
        return 0
print(num,':',sep='')
for i in range(2,(num + 1) // 2 + 1):
    if solve(i,i-1):
        print(i,',',i-1,sep='')
    
    if solve(i,i):
        print(i,',',i,sep='')