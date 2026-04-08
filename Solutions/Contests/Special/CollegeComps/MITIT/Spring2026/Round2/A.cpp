#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, k, x, y; cin >> n >> k >> x >> y;
    vector<ll> a(k);
    for(ll &z : a) cin >> z;

    vector<set<ll>> b(n);
    ll cur = 0;
    for(int i = 0; i < k; i++) {
        cur = (cur + a[i]) % n;
        b[cur].insert(i);
    }

    for(int i = 0; i < n; i++) {
        if(i == x) continue;
        ll os = i;
        int step = -1;
        while(b[(x - os + n) % n].upper_bound(step) != b[(x - os + n) % n].end()) {
            int nx_step = *b[(x - os + n) % n].upper_bound(step);
            step = nx_step;
            os = (os + y - x + n * 2) % n;
        }
        cout << (cur + os) % n << " ";
    }

    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}