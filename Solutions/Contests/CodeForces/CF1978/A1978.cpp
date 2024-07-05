#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    int res = 0;
    for(int i = 0; i < n - 1; i++) {
        int num; cin >> num;
        res = max(res,num);
    }
    int num; cin >> num;
    cout << res + num << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}