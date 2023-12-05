#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool poss(vector<pair<int,int>> &segs, int k) {
    int low_pos = 0, hi_pos = 0;
    bool poss = 1;
    for(int i = 0; i < segs.size(); i++) {
        //can be anywhere on the segment between low_pos and hi_pos inclusively

        if(low_pos - k <= segs[i].second && hi_pos + k >= segs[i].first) {
            int next_most_lo = max(low_pos - k,segs[i].first);
            int next_most_hi = min(hi_pos + k, segs[i].second);
            low_pos = next_most_lo;
            hi_pos = next_most_hi;
        } else {
            poss = 0;
            break;
        }
    }
    return poss;
}

void solve() {
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(auto &x : v) cin >> x.first >> x.second;
    int lo = 0, hi = 1e9;
    while(lo != hi) {
        int m = (lo + hi) / 2;
        if(poss(v, m)) {
            hi = m;
        } else {
            lo = m + 1;
        }
    }
    cout << lo << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}