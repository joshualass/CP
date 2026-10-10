#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

ld pk[20][1001];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, k; cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m));
    for(auto &x : a) {
        for(auto &y : x) {
            cin >> y;
        }
    }

    vector<vector<ld>> p(n, vector<ld>(m)), downs(n, vector<ld>(m)), rights(n, vector<ld>(m));

    p[0][0] = 1;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            ld x; cin >> x;
            ld right = x / 100, down = (100 - x) / 100;
            if(i + 1 < n) {
                p[i+1][j] += p[i][j] * down;
                downs[i+1][j] += p[i][j] * down;
            }
            if(j + 1 < m) {
                p[i][j+1] += p[i][j] * right;
                rights[i][j+1] += p[i][j] * right;
            }
        }
    }

    vector<vector<ll>> c(k, vector<ll>(2));
    for(auto &x : c) for(auto &y : x) cin >> y;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j]) {
                int item = a[i][j] - 1;
                if(i && a[i-1][j] != a[i][j]) {
                    pk[item][i + j] += downs[i][j] * c[item][0];
                }
                if(j && a[i][j-1] != a[i][j]) {
                    pk[item][i + j] += rights[i][j] * c[item][0];
                }
            }
        }
    }

    for(int i = 0; i < k; i++) {
        for(int j = 1; j <= 1000; j++) {
            pk[i][j] += pk[i][j-1];
        }
    }

    vector<int> par(1 << k);
    vector<ld> dp(1 << k, -1);
    dp[0] = 0;

    for(int bm = 0; bm < 1 << k; bm++) {
        ll time = 0;
        for(int i = 0; i < k; i++) {
            if((bm >> i) & 1) {
                time += c[i][1];
            }
        }
        for(int i = 0; i < k; i++) {
            if((bm >> i) & 1) {
                // ll tt = time - c[i][1];

                ld save = pk[i][1000] - pk[i][max(0LL, min(1000LL, time - 1))];
                ld test = dp[bm ^ (1 << i)] + save;
                if(test > dp[bm]) {
                    dp[bm] = test;
                    par[bm] = i;
                }
            }
        }
    }

    vector<int> res;
    int cur = (1 << k) - 1;
    while(cur) {
        int p = par[cur];
        res.push_back(p + 1);
        cur ^= 1 << p;
    }

    reverse(res.begin(), res.end());

    cout << res << '\n';

    return 0;
}
