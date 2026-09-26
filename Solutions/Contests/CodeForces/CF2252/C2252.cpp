#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, m; cin >> n >> m;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;

    vector<vector<ll>> a(n, vector<ll>(m));
    for(auto &x : a) for(auto &y : x) cin >> y;

    int res = m;
    priority_queue<ll, vector<ll>, greater<ll>> pq;

    ll cnt = 0;

    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < m; j++) {
            ll x = a[i][j];
            if(sz(pq) < res && cnt < v[i]) {
                pq.push(x);
                cnt += x;
            } else if(!pq.empty() && x > pq.top()) {
                cnt -= pq.top();
                pq.pop();
                cnt += x;
                pq.push(x);
            }
        }
        while(!pq.empty() && cnt - pq.top() >= v[i]) {
            cnt -= pq.top();
            pq.pop();
        }
        res = min(res, sz(pq));
    }
    
    cout << res << '\n';

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