#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//no prewritten code :( => no Mint. 
ll f[10000];

void solve(int n) {
    int k; cin >> k;
    vector<int> a(n,-1);
    for(int i = 0; i < k; i++) {
        int idx, j; cin >> idx >> j;
        a[idx] = j;
    }

    ll res = 0;

    if(n & 1) {
        int piv = n / 2;
        int fixover = 0, fixunder = 0;
        for(int i = 0; i < n; i++) {
            if(a[i] != -1) {
                if(a[i] < piv) fixunder++;
                if(a[i] > piv) fixover++;
            }
        }

        auto gook = [&](int start, int sh, int d, int s) -> int {
            for(int i = start; i != s; i += d) {
                if(sh) {
                    if(a[i] != -1 && a[i] <= piv) return 0;
                } else {
                    if(a[i] != -1 && a[i] >= piv) return 0;
                }
            }
            return 1;
        };

        for(int start = 0; start < n; start++) {
            if(start & 1) {
                for(int i = 0; i < 2; i++) {
                    if(gook(start + 1, i, 1, n) && gook(start - 1, i ^ 1, -1, -1)) res++;
                }
            } else {
                for(int i = 0; i < 2; i++) {
                    for(int j = 0; j < 2; j++) {
                        if(gook(start + 1, i, 1, n) && gook(start - 1, j, -1, -1)) res++;
                    }
                }
            }
        }
        res = res * f[n / 2 - fixover] % MOD * f[n / 2 - fixunder] % MOD;
    } else {
        vector<int> g(n);
        for(int i = 0; i < n; i++) {
            if(i & 1) {
                g[i] = i / 2;
            } else {
                g[i] = i / 2 + n / 2;
            }
        }
        auto checkok = [&]() -> int {
            for(int i = 0; i < n; i++) {
                if(a[i] != -1 && a[i] != g[i]) return 0;
            }
            return 1;
        };
        res += checkok();
        reverse(g.begin(), g.end());
        res += checkok();
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    f[0] = 1;
    for(int i = 1; i < 10000; i++) {
        f[i] = f[i-1] * i % MOD;
    }

    int casi, n; cin >> casi >> n;
    while(casi-->0) solve(n);

    return 0;
}