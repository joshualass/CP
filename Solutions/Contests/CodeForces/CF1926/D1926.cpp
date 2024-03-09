#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        m[num]++;
    }
    int merges = 0;
    for(auto [u,v] : m) {
        if(m.count(INT_MAX - u)) {
            merges += min(v,m[INT_MAX-u]);
        }
    }
    cout << n - merges / 2 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}