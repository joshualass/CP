#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int greedy(vector<int> &pref, int n, int x) {
    if((pref[n] | x) > x) return -1;

    int k = 0;
    int lo = 0, hi = 1;
    while(lo != n) { // [lo, hi)
        if(((pref[lo] ^ pref[hi]) | x) <= x && ((pref[hi] ^ pref[n]) | x) <= x) {
            k++;
            lo = hi;
            hi = hi + 1;
        } else {
            hi++;
        }
    }
    return k;
}

void solve() {
    int n, x; cin >> n >> x;

    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> pref(n+1);
    for(int i = 0; i < n; i++) {
        pref[i+1] = pref[i];
        pref[i+1] ^= a[i];
    }

    int res = -1;
    res = max(res, greedy(pref,n,x));

    for(int b = 1; b < 30; b++) {
        if(x & (1 << b)) {
            int t = x - (1 << b);
            t |= (1 << b) - 1;
            res = max(res, greedy(pref,n,t));
        }
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