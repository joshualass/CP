#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    ll slimes = 0;
    map<ll,ll> m;
    for(int i = 0; i < n; i++) {
        ll s, c; cin >> s >> c;
        m[s] = c;
    }
    while(m.size()) {
        pair<ll,ll> p = *m.begin();
        m.erase(m.begin());
        if(p.second & 1) slimes++;
        if(p.second > 1) {
            if(m.find(p.first << 1) == m.end()) {
                m[p.first << 1] = p.second / 2;
            } else {
                m[p.first << 1] += p.second / 2;
            }
        }
    }
    cout << slimes << "\n";
    return 0;
}