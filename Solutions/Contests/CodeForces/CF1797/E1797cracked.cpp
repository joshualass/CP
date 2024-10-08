#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ls x<<1
#define rs x<<1|1
#define lson x<<1,l,mid
#define rson x<<1|1,mid+1,r
#define ll long long
using namespace std;
const int N = 1e5+5,M = 5e6+5;
int a[N],p[M],phi[M],cnt,f[M],n,m;
bool vis[M];
struct node
{
    int x,sum,len;bool tp;
    friend node operator + (node x,node y)
    {
        int nx = x.x,ny = y.x,lx = x.len,ly = y.len,sum = x.sum+y.sum;
        if(!nx)return y;
        while(nx != ny)
        {
            if(nx < ny)swap(nx,ny),swap(lx,ly);
            nx = phi[nx];sum += lx;
        }
        return {nx,sum,lx+ly,x.tp&&y.tp};
    }
}t[N << 2];
node zh(int x){return {x,0,1,x==1};}
void init()
{
    phi[1] = 1;
    for(int i = 2;i < M;i++)
    {
        if(!vis[i])p[++cnt] = i,phi[i] = i-1;
        for(int j = 1;j <= cnt&&i*p[j] < M;j++)
        {
            int now = i*p[j];vis[now] = 1;
            if(i%p[j] == 0){phi[now] = phi[i]*p[j];break;}
            phi[now] = phi[i]*(p[j]-1);
        }
    }
}
void build(int x,int l,int r)
{
    if(l == r){t[x] = zh(a[l]);return ;}
    int mid = l+r>>1;
    build(lson);build(rson);
    t[x] = t[ls]+t[rs];
}
void modify(int x,int l,int r,int L,int R)
{
    if(t[x].tp)return ;
    if(l == r){t[x] = zh(a[l] = phi[a[l]]);return ;}
    int mid = l+r>>1;
    if(L <= mid)modify(lson,L,R);
    if(mid < R)modify(rson,L,R);
    t[x] = t[ls]+t[rs];
}
node query(int x,int l,int r,int L,int R)
{
    if(L <= l&&r <= R)return t[x];
    int mid = l+r>>1;node ans = {0,0,0,0};
    if(L <= mid)ans = ans+query(lson,L,R);
    if(mid < R)ans = ans+query(rson,L,R);
    return ans;
}
inline int rd()
{
    char c;int f = 1;
    while(!isdigit(c = getchar()))if(c=='-')f = -1;
    int x = c-'0';
    while(isdigit(c = getchar()))x = x*10+(c^48);
    return x*f;
}
int main()
{
    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    n = rd();m = rd();
    for(int i = 1;i <= n;i++)a[i] = rd();
    init();build(1,1,n);
    while(m--)
    {
        int op = rd(),l = rd(),r = rd();
        if(op == 1)modify(1,1,n,l,r);
        else printf("%d\n",query(1,1,n,l,r).sum);
    }
    return 0;
}