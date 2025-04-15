#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

#pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 

// i have no idea how to do better than m * n^2 / 64
// gg, it's intended. 

bitset<5000> a[5000];
bitset<5000> cur;


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int m, n; cin >> m >> n;
    vector<ll> c(n);

    for(int i = 0; i < n; i++) {
        a[i].set();
        cin >> c[i];
    }

    for(int i = 0; i < m; i++) {

        vector<array<int,2>> b(n);
        for(int j = 0; j < n; j++) {
            cin >> b[j][0];
            b[j][1] = j;
        }

        sort(b.begin(), b.end());
        cur.reset();

        int l = -1, r = 0;
        while(r < n) {
            if(b[l+1][0] < b[r][0]) {
                cur[b[++l][1]] = 1;
            } else {
                a[b[r++][1]] &= cur;
            }
        }

    }

    vector<ll> dp(n,-1);

    auto dfs = [&](auto self, int i) -> ll {

        if(dp[i] != -1) return dp[i];
        dp[i] = c[i];
        ll p = 0;

        for(int j = 0; j < n; j++) {
            if(a[i][j]) p = max(p, self(self, j));
        }
        dp[i] += p;
        return dp[i];
    };

    ll res = 0;
    for(int i = 0; i < n; i++) res = max(res, dfs(dfs,i));

    cout << res << '\n';

    return 0;
}