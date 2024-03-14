#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    // vector<int> b(n);
    vector b(n,0);
    vector<int> c(m);
    int cnt = 0;
    for(int &x : b) cin >> x;
    for(int &x : c) cin >> x;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(b[i] + c[j] <= k) cnt++;
        }
    }
    cout << cnt << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}