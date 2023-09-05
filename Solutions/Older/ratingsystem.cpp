#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;
    v.insert(v.begin(), 0);
    v.push_back(0);
    ll count = 0;
    ll best = 0;
    int bestidx = 0;
    int curridx = 0;
    for(int i = 0; i < n+2; i++) {
        if(v[i] <= 0) {
            count += v[i];
            if(count < best) {
                best = count;
                bestidx = curridx;
            }
        } else {
            if(count + v[i] > 0) {
                count = 0;
                curridx = i;
            } else {
                count += v[i];
            }
        }
    }
    // cout << "bestidx: " << bestidx << "\n";
    ll k = 0;
    for(int i = 0; i <= bestidx; i++) {
        k += v[i];
    }
    cout << k << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}