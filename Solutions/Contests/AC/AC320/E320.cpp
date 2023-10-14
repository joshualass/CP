#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<ll> noodles(n);
    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;
    for(int i = 0; i < m; i++) {
        ll t, w, s; cin >> t >> w >> s;
        pq.push({t,1,w,s});
    }
    set<int> s;
    for(int i = 0; i < n; i++) {
        s.insert(i);
    }
    while(pq.size()) {
        vector<ll> v = pq.top();
        pq.pop();
        if(v[1] == 0) { //person goes back in line
            s.insert(v[2]);
        } else {
            if(s.size()) {
                int next = *s.begin();
                noodles[next] += v[2];
                s.erase(next);
                pq.push({v[0] + v[3], 0, next});
            }
        }
    }

    for(auto &x: noodles) cout << x << "\n";

    return 0;
}