#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    // ll w, l; cin >> w >> l;
    // vector<ld> p(w + 1 + l);

    // ld res = 0;
    // p[w] = 1;
    // for(int i = 0; i < 10000; i++) {
    //     vector<ld> next(w + l + 1);
    //     res += p[0] * i;
    //     for(int j = 1; j < w + l; j++) {
    //         next[j-1] += p[j] / 2;
    //         next[j+1] += p[j] / 2;
    //     }
    //     next[w + l - 1] += p[w + l];
    //     swap(p,next);
    // }

    // cout << fixed << setprecision(10) << res << '\n';

    // ll W, G, L; cin >> W >> G >> L;
    // ll l = L;
    // ll w = W - G;

    // ll init = (((w + 1) % MOD) * ((w + 1) % MOD) + MOD - 1) % MOD;
    // ll add = (((w * 2) % MOD) * ((l - 1) % MOD)) % MOD;


    // // cout << "init : " << init << " add : " << add << '\n';
    // cout << (add + init) % MOD << '\n';

    ll W, G, L; cin >> W >> G >> L;

    ll losing_weight_ev = (L * 2 + 1) % MOD;
    cout << ((W - G) % MOD) * losing_weight_ev % MOD << '\n';
    
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);


    // freopen(".in","r",stdin);
    // freopen(".out","w",stdout);
    
    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}

/*
20
1 1
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 11
1 12
1 13 
1 14
1 15
1 16
1 17
1 18
1 19
1 20

Pattern: + 2 each time

10
1 1
2 1
3 1
4 1
5 1
6 1
7 1
8 1
9 1
10 1

Pattern: 1 less than W^2. Increasing by 3, where each subsequent increase increases by 2

16
1 1
1 2
1 3
1 4
2 1
2 2
2 3
2 4
3 1
3 2
3 3
3 4
4 1
4 2
4 3
4 4



*/