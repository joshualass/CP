#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll n; cin >> n;
    vector<vector<ll>> mat(n,vector<ll>(n));
    for(auto &x : mat) {
        for(auto &y : x) cin >> y;
    }

    vector<ll> ans(n, 1073741823LL);
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i == j) continue;
            for(ll bit = 0; bit < 63; bit++) {
                if((mat[i][j] & (1LL << bit)) == 0) {
                    if((ans[i] & (1LL << bit)) != 0) {
                        ans[i] ^= (1LL << bit);
                    }
                    if((ans[j] & (1LL << bit)) != 0) {
                        ans[j] ^= (1LL << bit);
                    }
                }
            }
        }
    }
    bool poss = 1;

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(i != j) {
                if((ans[i] | ans[j]) != mat[i][j]) poss = 0;
            }
        }
    }
    if(poss) {
        cout << "YES\n";
        for(auto x : ans) cout << x << ' ';
        cout << '\n';
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}