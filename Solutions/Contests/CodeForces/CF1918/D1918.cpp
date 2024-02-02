#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

bool poss(vector<ll> &v, ll m) {
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    int loidx = 0;
    ll losum = 0;
    pq.push({0,-1});
    for(int i = 0; i < v.size(); i++) {
        if(i != 0) {
            losum += v[i - 1];
        }
        while(losum > m) {
            losum -= v[loidx++];
        }
        while(pq.size() && pq.top().second < loidx - 1) {
            pq.pop();
        }
        
        pq.push({pq.top().first + v[i], i});
    }
    return pq.top().first <= m;
}

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    v.push_back(0);
    ll l = 1, r = reduce(v.begin(), v.end());
    while(l != r) {
        ll m = l + (r - l) / 2;
        if(poss(v,m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    cout << l << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}