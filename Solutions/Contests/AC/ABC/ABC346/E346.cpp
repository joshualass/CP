#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll h,w,m; cin >> h >> w >> m;

    map<ll,ll> cnts;
    set<ll> usedh;
    set<ll> usedw;
    vector<array<ll,3>> ops;
    for(int i = 0; i < m; i++) {
        ll t, a, x; cin >> t >> a >> x;
        ops.push_back({t,a,x});
    }
    ll sum = 0;
    cnts[0] = 0;
    for(int i = m - 1; i >= 0; i--) {
        if(ops[i][0] == 1) {
            if(usedh.count(ops[i][1]) == 0) {
                usedh.insert(ops[i][1]);
                cnts[ops[i][2]] += w - usedw.size();
                sum += w - usedw.size();
            }
        } else {
            if(usedw.count(ops[i][1]) == 0) {
                usedw.insert(ops[i][1]);
                cnts[ops[i][2]] += h - usedh.size();
                sum += h - usedh.size();
            }
        }
    }

    vector<pair<ll,ll>> ans;
    for(auto [u,v] : cnts) {
        ll val = v + (u == 0 ? h*w-sum : 0);
        if(val != 0) {
            ans.push_back({u,val});
        }
        // cout << u << " " << v + (u == 0 ? h*w-sum : 0) << '\n';
    }

    cout << ans.size() << '\n';
    for(auto x : ans) {
        cout << x.first << " " << x.second << '\n';
    }

    return 0;
}