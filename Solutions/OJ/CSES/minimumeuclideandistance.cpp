#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    set<pair<ll,ll>> p; //(x, y)
    for(int i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        p.insert({a,b});
    }
    set<pair<ll,ll>> cmp; //(y,x)
    ll mindist = 8e18;
    // cout << "mindist : " << mindist << '\n';
    while(p.size()) {
        pair<ll,ll> pt = *p.begin();
        vector<pair<ll,ll>> r;
        for(set<pair<ll,ll>>::iterator it = cmp.lower_bound({(ll) (pt.second - sqrt(mindist)), (ll) -2e18}); it != cmp.end() && (*it).first <= pt.second + sqrt(mindist); it++) {
            pair<ll,ll> t = *it;
            if((pt.first - t.second) * (pt.first - t.second) + (pt.second - t.first) * (pt.second - t.first) < mindist) {
                mindist = (pt.first - t.second) * (pt.first - t.second) + (pt.second - t.first) * (pt.second - t.first);
            }
            if(t.second < pt.first - sqrt(mindist)) {
                r.push_back(t);
            }
        }
        for(auto pt : r) {
            cmp.erase(pt);
        }
        p.erase(p.begin());
        cmp.insert({pt.second,pt.first});
    }
    cout << mindist << '\n';
    return 0;
}