#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const ll inf = 1e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<array<ll,2>> a(n), qs(m); // {position, utility}, workstations
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : qs) for(auto &y : x) cin >> y;
    
    vector<ll> res(m, -inf);

    auto work = [&]() -> void {
        //{x, type, info}
        vector<array<ll,4>> events;

        // {type = 0, utility, _}
        for(int i = 0; i < n; i++) {
            events.push_back({a[i][0], 0, a[i][1], 0});
        }
        //{type = 1, y, id}
        for(int i = 0; i < m; i++) {
            events.push_back({qs[i][0], 1, qs[i][1], i});
        }

        sort(events.begin(), events.end());
        ll best = -inf;

        for(auto event : events) {
            if(event[1] == 0) {
                best = max(best, event[0] + event[2]);
            } else {
                res[event[3]] = max(res[event[3]], best - event[0] - abs(event[2]));
            }
        }
    };

    work();
    for(auto &x : a) x[0] *= -1;
    for(auto &x : qs) x[0] *= -1;
    work();

    for(int i = 0; i < m; i++) {
        cout << max(0LL, res[i]) << " \n"[i == m - 1];
    }

    return 0;
}
