#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
const int MAXN = 3e5;
ll hashes[MAXN];
mt19937 rng;

void solve() {
    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(string &x : a) cin >> x;

    unordered_map<ll,vector<array<int,2>>> hv;
    for(int i = 0; i < m; i++) {
        ll sh = 0;
        for(int j = 0; j < n; j++) {
            if(a[j][i] == '1') {
                sh += hashes[j];
            }
        }
        for(int j = 0; j < n; j++) {
            if(a[j][i] == '1') {
                hv[sh - hashes[j]].push_back({j,i});
            } else {
                hv[sh + hashes[j]].push_back({j,i});
            }
        }
    }
    int res = 0;
    array<int,2> rh = {-1,-1};
    for(auto [u, v] : hv) {
        if(v.size() > res) {
            res = v.size();
            rh = v[0];
        }
    }
    cout << res << '\n';
    // cout << "rh : " << rh[0] << ", " << rh[1] << '\n';
    for(int i = 0; i < n; i++) {
        cout << ((a[i][rh[1]] == '1' ^ i == rh[0]));
    }
    cout << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    for(int i = 0; i < MAXN; i++) {
        hashes[i] = rng() * (i + 1LL);
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}