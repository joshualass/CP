#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, m, k; cin >> n >> m >> k;
    vector<array<ll,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    int rp = 0;
    int mxidx = -1;
    ll cur = 0;

    auto x = [&](ll l, int interval) -> ll {
        ll lo = max(l, a[interval][0]), hi = min(l + m - 1, a[interval][1]);
        return max(0LL, hi - lo + 1);
    };

    for(int i = 0; i < n; i++) {
        if(i && rp >= i) {
            cur -= a[i-1][1] - a[i-1][0] + 1;
        }
        rp = max(rp, i);
        while(rp < n && a[rp][1] <= a[i][0] + m - 1) {
            cur += a[rp][1] - a[rp][0] + 1;
            rp++;
        }
        ll ex = 0;
        if(rp < n) ex = x(a[i][0], rp);
        // cout << "i : " << i << " cur : " << cur << " ex : " << ex << endl;
        if(cur + ex >= k) {
            mxidx = i;
        }
    }

    if(mxidx == -1) {
        cout << "-1\n";
        return;
    }

    ll l = a[mxidx][0], r = 1e16;
    while(l != r) {
        ll m = (l + r) / 2;
        ll score = 0;
        for(int i = 0; i < n; i++) {
            score += x(m, i);
        }
        if(score == k) {
            l = m;
            r = m;
        } else if(score > k) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    cout << l << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}