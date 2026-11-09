#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<array<ll,4>> a(n);
    for(ll i = 0; i < n; i++) {
        ll y, d, r; cin >> y >> d >> r;
        a[i] = {y, d, r, i};
    }

    sort(a.begin(), a.end());

    priority_queue<array<ll,4>, vector<array<ll,4>>, greater<array<ll,4>>> pq;
    vector<vector<ll>> vis(n, vector<ll>(2));
    vector<map<ll,int>> unvis(2);
    vector<ll> dis(n, -1);

    auto visit_city = [&](ll city, ll time) -> void {
        // cout << "vc city : " << city << " time : " << time << " dir : " << dir << endl;
        auto [y, d, r, _] = a[city];
        auto it = unvis[1].lower_bound(y+d);
        if(it != unvis[1].end()) {
            int idx = it->second;
            pq.push({time + abs(a[idx][0] - y) + r, city, time, idx});
        }
        it = unvis[0].upper_bound(y - d);
        if(it != unvis[0].begin()) {
            it--;
            int idx = it->second;
            array<ll,4> push = {time + abs(a[idx][0] - y) + r, city, time, idx};
            // cout << "push down : " << push << endl;
            // cout << "city at idx : " << a[idx] << endl;
            pq.push(push);
        }
    };

    ll start = -1;
    for(ll i = 0; i < n; i++) {
        if(a[i][3] == 0) start = i;
        for(int j = 0; j < 2; j++) {
            unvis[j][a[i][0]] = i;
        }
    }

    visit_city(start, 0);

    while(!pq.empty()) {
        auto [time, from_city, from_time, to_city] = pq.top();
        pq.pop();
        // cout << "time : " << time << " fc : " << from_city << " ft : " << from_time << " tc : " << to_city << "tc info : " << a[to_city] << endl;
        // cout << "visit of this"
        if(vis[to_city][0] || vis[to_city][1]) {
            assert(time >= dis[to_city]);
        }
        if(vis[to_city][0] && vis[to_city][1]) continue;

        ll dir;
        if(to_city > from_city) {
            dir = 1;
        } else {
            dir = 0;
        }
        // cout << "nxc : " << nx_city << endl;
        if(vis[to_city][0] == 0 && vis[to_city][1] == 0) {
            dis[to_city] = time;
            visit_city(to_city, time);
        }
        if(vis[to_city][dir] == 0) {
            // cout << "visit tc : " << to_city << " dir : " << dir << endl;
            vis[to_city][dir] = 1;
            unvis[dir].erase(a[to_city][0]);
            if(dir == 1) {
                if(unvis[dir].upper_bound(a[to_city][0]) != unvis[dir].end()) {
                    int nx_city = unvis[dir].upper_bound(a[to_city][0])->second;
                    array<ll,4> nx = {from_time + a[from_city][2] + abs(a[from_city][0] - a[nx_city][0]), from_city, from_time, nx_city};
                    pq.push(nx);
                }
            } else {
                if(unvis[dir].upper_bound(a[to_city][0]) != unvis[dir].begin()) {
                    int nx_city = (--unvis[dir].upper_bound(a[to_city][0]))->second;
                    array<ll,4> nx = {from_time + a[from_city][2] + abs(a[from_city][0] - a[nx_city][0]), from_city, from_time, nx_city};
                    pq.push(nx);
                }
            }
        }
    }

    vector<ll> res(n);
    for(ll i = 0; i < n; i++) {
        res[a[i][3]] = dis[i];
    }
    
    res.erase(res.begin());
    for(ll x : res) cout << x << '\n';

    return 0;
}