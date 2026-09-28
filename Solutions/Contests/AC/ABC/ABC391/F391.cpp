#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    set<array<ll,3>> s;
    priority_queue<array<ll,4>> pq;
    vector<ll> a(n), b(n), c(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;
    for(ll &x : c) cin >> x;
    auto work = [&](int ai, int bi, int ci) -> ll {
        return a[ai] * b[bi] + a[ai] * c[ci] + b[bi] * c[ci];
    };
    sort(a.rbegin(),a.rend());
    sort(b.rbegin(),b.rend());
    sort(c.rbegin(),c.rend());
    pq.push({work(0,0,0), 0, 0, 0});
    ll res = 0;
    while(k) {
        auto [v, ai, bi, ci] = pq.top();
        pq.pop();
        if(s.count({ai,bi,ci})) continue;
        s.insert({ai,bi,ci});
        // cout << "v : " << v << '\n';
        k--;
        res = v;
        if(ai != n - 1) {
            ai++;
            pq.push({work(ai,bi,ci), ai, bi, ci});
            ai--;
        }
        if(bi != n - 1) {
            bi++;
            pq.push({work(ai,bi,ci), ai, bi, ci});
            bi--;
        }
        if(ci != n - 1) {
            ci++;
            pq.push({work(ai,bi,ci), ai, bi, ci});
            ci--;
        }
    }

    cout << res << '\n';

    return 0;
}