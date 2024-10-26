#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    vector<int> b(n);
    vector<ll> res(n,-1);
    vector<ll> p(n + 1);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
        p[i+1] = p[i] + a[i];
    }

    for(int &x : b) {
        cin >> x;
        x--;
    }

    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;
    pq.push({0,0});
    ll ans = 0;

    while(pq.size()) {
        auto [cost, i] = pq.top();
        pq.pop();

        if(res[i] != -1) continue;
        res[i] = cost;

        ans = max(ans, p[i+1] - cost);
        
        if(i) {
            pq.push({cost, i-1});
        }
        pq.push({cost + a[i], b[i]});

    }

    cout << ans << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}