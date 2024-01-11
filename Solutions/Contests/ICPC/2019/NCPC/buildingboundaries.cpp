#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll ans;

void try1(vector<pair<ll,ll>> v, int i, ll w, ll h, ll currw, ll currh) {
    //put this piece in the corner
    if(i == 3) {
        // cout << "i : " << i << " w : " << w << " h : " << h << " currw : " << currw << " currh : " << currh << '\n';
        ans = min(ans, w * h);
        return;
    }
    w = max(w, currw + v[i].first);
    h = max(h, currh + v[i].second);
    try1(v, i + 1, w, h, currw + v[i].first, currh);
    try1(v, i + 1, w, h, currw, currh + v[i].second);
    if(i == 0) {
        ans = min(ans, max(v[0].first + v[1].first, v[2].first) * (max(v[0].second, v[1].second) + v[2].second));
        ans = min(ans, max(v[0].second + v[1].second, v[2].second) * (max(v[0].first, v[1].first) + v[2].first));
    }
}

void solve() {
    vector<pair<ll,ll>> v(3);
    for(auto &p : v) cin >> p.first >> p.second;
    ans = LLONG_MAX;
    sort(v.begin(), v.end());
    for(int i = 0; i < 8; i++) {
        for(int k = 0; k < 8; k++) {
            for(int j = 0; j < 3; j++) {
                if((i >> j) & 1) {
                    swap(v[j].first,v[j].second);
                }
            }
            try1(v,0,0,0,0,0);
            for(int j = 0; j < 3; j++) {
                if((i >> j) & 1) {
                    swap(v[j].first,v[j].second);
                }
            }
            next_permutation(v.begin(), v.end());
        }
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}