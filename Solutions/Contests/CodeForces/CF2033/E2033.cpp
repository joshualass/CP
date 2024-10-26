#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    int res = 0;
    vector<int> vis(n);

    for(int i = 0; i < n; i++) {
        int s = 0;
        int t = i;
        while(!vis[t]) {
            vis[t] = 1;
            t = a[t];
            s++;
        }
        res += (s - 1) / 2;
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}