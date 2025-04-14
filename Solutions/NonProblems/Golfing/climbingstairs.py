s,r,o=map(int,input().split())
x=max(s,o+o-r)if o>r else max(r,s)
print(x+(x%2^r%2)+r)
