#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<int> l(n);
    vector<int> r(n);
    vector<ll> c(n);
    for(auto &x : l) cin >> x;
    for(auto &x : r) cin >> x;
    for(auto &x : c) cin >> x;
    
    vector<pair<int,int>> events;
    for(int i = 0; i < n; i++) {
        events.push_back({l[i],0});
        events.push_back({r[i],1});
    }

    sort(events.begin(),events.end());

    vector<ll>lengths;

    stack<int> s;
    for(int i = 0; i < events.size(); i++) {
        if(events[i].second == 0) {
            s.push(events[i].first);
        } else {
            lengths.push_back(events[i].first - s.top());
            s.pop();
        }
    }

    ll cost = 0;
    sort(lengths.begin(), lengths.end());
    sort(c.begin(),c.end());
    for(int i = 0; i < n; i++) {
        cost += lengths[i] * c[n-i-1];
    }
    cout << cost << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}