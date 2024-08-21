#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> f(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        f[num-1]++;
    }
    int res = 0;
    for(int i = 0; i < n; i++) {
        res = max(res,f[i]);
    }
    cout << n - res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}