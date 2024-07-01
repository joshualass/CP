#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    ll prevmax; cin >> prevmax;
    ll res = 0, maxops = 0;
    for(int i = 1; i < n; i++) {
        ll num; cin >> num;
        if(num < prevmax) {
            res += prevmax - num;
            maxops = max(maxops, prevmax-num);
        } else {
            prevmax = num;
        }
    }
    cout << res + maxops << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}