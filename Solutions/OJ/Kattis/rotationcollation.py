n=int(input());a=[-1];l=j=-1
def q(i,k):
 print("?",i%n+1,k%n+1,flush=True)
 return int(input())
r=-1
for i in range(2*n):
 z=i-l
 while z!=-1 and not q(z,i):z=a[z];l=i-z
 z+=1
 if z==n:r=(2*n-l)%n;break
 if z==len(a):
  while j!=-1 and not q(j,i):j=a[j]
  j+=1;a+=[j]
print("!",r,flush=True)