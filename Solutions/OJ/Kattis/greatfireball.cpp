#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const ld PI = acos(-1);

//yaya geometry

int maxOrcs(vector<pair<ld,ld>> &orcs, ld r) {

    vector<pair<ld,int>> events;
    for(int i = 0; i < orcs.size(); i++) {
        ld angle = atan2(orcs[i].second, orcs[i].first);
        ld dist = orcs[i].second * orcs[i].second + orcs[i].first * orcs[i].first;
        if(r * r + 0.000000001 > dist) {
            ld enter = angle - acos(sqrt(dist)/r);
            if(enter < -PI) {
                enter += 2 * PI;
            }
            ld exit = angle + acos(sqrt(dist)/r);
            if(exit > PI) {
                exit -= 2 * PI;
            }
            events.push_back({enter,i+1});
            events.push_back({exit,-i-1});
        }
    }

    sort(events.begin(), events.end());

    int ans = 0;
    set<int> s;
    for(int i = 0; i < events.size() * 2; i++) {
        pair<ld,int> event = events[i % events.size()];
        if(event.second > 0) {
            s.insert(event.second);
        } else {
            s.erase(-event.second);
        }
        ans = max(ans, (int) s.size());
    }

    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<pair<ld,ld>> orcs(n);
    for(auto &x : orcs) cin >> x.first >> x.second;

    ld l = 0.000000001, r = 1e12;
    while(r - l > 0.0000001) {
        ld m = l + (r - l) / 2;
        if(maxOrcs(orcs,m) >= k) {
            r = m;
        } else {
            l = m;
        }
    }   
    if(l > 1e12 - 1) {
        cout << "-1\n";
    } else {
        cout << fixed << setprecision(10) << l / 2 << '\n';
    }

    return 0;
}