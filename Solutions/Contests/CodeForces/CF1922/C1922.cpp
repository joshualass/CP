#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> lr(n);
    vector<int> rl(n);
    vector<int> a(n);
    for(int &x : a) cin >> x;
    for(int i = 1; i < n; i++) {
        lr[i] = lr[i-1];
        if(i - 1 == 0 || a[i] - a[i-1] < a[i-1] - a[i-2]) {
            lr[i]++;
        } else {
            lr[i] += a[i] - a[i-1];
        }
    }
    for(int i = n - 2; i >= 0; i--) {
        rl[i] = rl[i+1];
        if(i + 1 == n - 1 || a[i+1] - a[i] < a[i+2] - a[i+1]) {
            rl[i]++;
        } else {
            rl[i] += a[i+1] - a[i];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}