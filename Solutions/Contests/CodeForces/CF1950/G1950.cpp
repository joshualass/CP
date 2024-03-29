#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    map<string,int> gids;
    map<string,int> wids;
    vector<pair<int,int>> a;

    for(int i = 0; i < n; i++) {
        string g, w; cin >> g >> w;
        if(gids.count(g) == 0) {
            gids[g] = gids.size();
        }
        if(wids.count(w) == 0) {
            wids[w] = wids.size();
        }
        a.push_back({gids[g], wids[w]});
    }

    vector<vector<bool>> dp(1 << n, vector<bool>(n)); //bitmask, start

    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}