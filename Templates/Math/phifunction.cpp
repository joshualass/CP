const int MAXN = 5e6 + 1;
int phi[MAXN], p[MAXN];
bool vis[MAXN];
void build_phi() {
    phi[1] = 1;
    int cnt = 0;
    for(int i = 2;i < MAXN;i++)
    {
        if(!vis[i])p[++cnt] = i,phi[i] = i-1;
        for(int j = 1;j <= cnt&&i*p[j] < MAXN;j++)
        {
            int now = i*p[j];vis[now] = 1;
            if(i%p[j] == 0){phi[now] = phi[i]*p[j];break;}
            phi[now] = phi[i]*(p[j]-1);
        }
    }
}
