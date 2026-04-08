#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    int n, q; cin >> n >> q;
    vector<array<ll,2>> a(n); // {position, utility}, workstations
    for(auto &x : a) cin >> x[0];
    for(auto &x : a) cin >> x[1];
    vector<array<ll,2>> qs(q);
    for(auto &x : qs) for(auto &y : x) cin >> y;
    
    auto dis = [&](array<ll,2> f, array<ll,2> s) -> ld {
        auto [x1, y1] = f;
        auto [x2, y2] = s;
        return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };
    
    vector<ld> res(q);

    auto work = [&]() -> void {
        vector<array<ll,4>> events;

        //{x, y, utility, type}
        for(int i = 0; i < n; i++) {
            events.push_back({a[i][0], 0, a[i][1], 0});
        }
        //{x, y, idx, type}
        for(int i = 0; i < q; i++) {
            events.push_back({qs[i][0], qs[i][1], i, 1});
        }

        sort(events.begin(), events.end(), [&](const auto &lhs, const auto &rhs) -> bool {
            if(lhs[0] != rhs[0]) return lhs[0] < rhs[0];
            return lhs[3] < rhs[3];
        });

        vector<array<ll,3>> st; // {px, py, u}
        for(auto event : events) {
            if(event[3] == 0) {
                auto [x, y, utility, _] = event;
                while(sz(st) && (utility >= st.back()[2] || sz(st) >= 2 && ))
            }
        }

    };


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}
