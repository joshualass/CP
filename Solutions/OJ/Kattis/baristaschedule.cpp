#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for(int i = 0; i < k; i++) pq.push(0);
    int p = 0;
    sort(a.begin(), a.end());
    ll res = 0;
    while(p < n) {
        ll t = pq.top();
        pq.pop();
        ll nx = t + a[p++];
        res += nx;
        pq.push(nx);
    }

    cout << res << '\n';

    return 0;
}
