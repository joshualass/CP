#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ll,4>> a(n);
    for(int i = 0; i < n; i++) {
        ll s, x, y; cin >> s >> x >> y;
        a[i] = {s, x, y, i};
    }

    sort(a.begin(), a.end(), [&](const auto lhs, const auto &rhs) -> bool {
        return lhs[1] < rhs[1];
    });

    vector<ll> res(n);
    priority_queue<array<ll,3>> pq;
    
    int p = 0;
    ll time = 0;
    while(sz(pq) || p != n) {
        // cout << "p : " << p << " time : " << time << endl;
        if(pq.empty()) {
            time = a[p][1];
        }
        if(p < n && time == a[p][1]) {
            pq.push({a[p][0], a[p][3], a[p][2]});
            p++;
        }

        // cout << "upd time : " << time << endl;

        assert(sz(pq));
        auto [suit, id, tl] = pq.top();
        pq.pop();
    
        ll next_event = min(tl, (p < n ? a[p][1] - time : LLONG_MAX));

        // cout << "suit : " << suit << " id : " << id << " tl : " << tl << " ne : " << next_event << endl;
        time += next_event;
        if(next_event == tl) {
            res[id] = time;
        } else {
            pq.push({suit, id, tl - next_event});
        }
    }

    for(ll x : res) cout << x << '\n';

    return 0;
}
