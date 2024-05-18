#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<pair<ld,ld>> v(10);

    for(auto &p : v) cin >> p.first >> p.second;

    bool isrectangle = 0;
    for(int i = 0; i < 10; i++) {
        int samex = 0, samey = 0;
        for(int j = 0; j < 10; j++) {
            if(abs(v[i].first - v[j].first) < 0.00001) {
                samex++;
            }
            if(abs(v[i].second - v[j].second) < 0.00001) {
                samey++;
            }
        }
        // cout << "sx : " << samex << " sy : " << samey << '\n';
        if(samex >= 3 || samey >= 3) isrectangle = 1;
    }
    cout << (!isrectangle ? "VINYL" : "CASSETTE") << '\n';
    return 0;
}