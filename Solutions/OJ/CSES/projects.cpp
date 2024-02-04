#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<ll>> v(0);
    for(int i = 0; i < n; i++) {
        ll a, b, c; cin >> a >> b >> c;
        v.push_back({a,b,c});
    }
    sort(v.begin(),v.end());
    priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
    ll cur = 0;
    for(int i = 0; i < n; i++) {
        while(pq.size() && pq.top().first < v[i][0]) {
            pair<ll,ll> p = pq.top();
            pq.pop();
            cur = max(cur, p.second);
        }
        pq.push({v[i][1],cur+v[i][2]});
    }
    while(pq.size()) {
        pair<ll,ll> p = pq.top();
        pq.pop();
        cur = max(cur, p.second);
    }    
    cout << cur << "\n";
    return 0;
}