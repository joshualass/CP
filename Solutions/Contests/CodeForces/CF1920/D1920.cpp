#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, q; cin >> n >> q;

    vector<pair<int,vector<ll>>> ops;
    for(int i = 0; i < n; i++) {
        int type; cin >> type;
        int num; cin >> num;
        if(type == 1) {
            if(ops.empty() || ops.back().first == 2) {
                ops.push_back({1,{num}});
            } else {
                ops.back().second.push_back(num);
            }
        } else {
            ops.push_back({2,{num}});
        }
    }

    

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}