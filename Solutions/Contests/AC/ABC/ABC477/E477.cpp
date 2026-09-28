#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    vector<ll> dis(n, LLONG_MAX);
    vector<int> vis(n);

    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;

    auto pushq = [&](ll x, ll d) -> void {
        if(vis[x] == 0 && d < dis[x]) {
            dis[x] = d;
            pq.push({d, x});
        }
    };

    for(int i = 0; i < n; i++) pushq(i, b[i]);
    while(!pq.empty()) {
        auto [d, x] = pq.top();
        pq.pop();
        if(vis[x]) continue;
        vis[x] = 1;
        int prev = (x - 1 + n) % n, nx = (x + 1) % n;
        pushq(prev, d + a[prev]);
        pushq(nx, d + a[x]);
    }

    // cout << "dis : " << dis << endl;

    vector<ll> p(n * 2 + 1);
    for(int i = 0; i < n * 2; i++) {
        p[i + 1] = a[i % n] + p[i];
    }

    for(int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;
        l--; r--;
        ll res;
        if(r == n) {
            res = dis[l];
        } else {
            res = min({dis[l] + dis[r], p[r] - p[l], p[l + n] - p[r]});
        }
        cout << res << '\n';
    }

    return 0;
}
