#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()
const ll inf = 1e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, a, t; cin >> n >> m >> a >> t;
    ll h, w; cin >> h >> w;
    vector<array<ll,2>> c(n), b(m);
    for(auto &x : c) for(auto &y : x) cin >> y;
    for(auto &x : b) for(auto &y : x) cin >> y;

    sort(b.begin(), b.end());

    vector<ll> eaten(n), ps(n, inf);
    vector<int> nears(n);

    ll time = 0;

    auto dist = [&](int cock, int bait) -> ll {
        ll d = abs(c[cock][0] - b[bait][0]) + abs(c[cock][1] - b[bait][1]);
        ll death_time = (ps[cock] != inf ? ps[cock] + t : inf);
        if(time + d <= death_time) return d;
        return inf;
    };

    while(1) {
        // cout << "time : " << time << endl;
        ll best = -1, best_dist = inf;
        for(int i = 0; i < n; i++) {
            ll best_here = -1, best_dist_here = inf;
            for(int j = 0; j < m; j++) {
                if(b[j] == array<ll,2>{inf,inf}) continue;
                ll d = dist(i, j);
                if(d < best_dist_here) {
                    best_here = j;
                    best_dist_here = d;
                }
            }
            nears[i] = best_here;
            // cout << "i : " << i << " best_here : " << best_here << " bdh : " << best_dist_here << endl;
            if(best_dist_here < best_dist) {
                best = i;
                best_dist = best_dist_here;
            }
        }
        // cout << " best : " << best << " best dist : " << best_dist << endl;
        if(best == -1) break; //no more cockroaches can reach any bait
        for(int i = 0; i < n; i++) {
            if(nears[i] != -1) {
                ll rem = best_dist;
                ll dx = min(rem, abs(b[nears[i]][0] - c[i][0]));
                rem -= dx;
                if(b[nears[i]][0] > c[i][0]) {
                    c[i][0] += dx;
                } else { 
                    c[i][0] -= dx;
                }
                ll dy = min(rem, abs(b[nears[i]][1] - c[i][1]));
                rem -= dy;
                if(b[nears[i]][1] > c[i][1]) {
                    c[i][1] += dy;
                } else { 
                    c[i][1] -= dy;
                }
            }
        }
        time += best_dist;
        eaten[best]++;
        if(eaten[best] == a) ps[best] = time;
        b[nears[best]] = {inf, inf};
    }

    for(int i = 0; i < n; i++) cout << (ps[i] == inf ? -1 : ps[i] + t) << '\n';

    return 0;
}
