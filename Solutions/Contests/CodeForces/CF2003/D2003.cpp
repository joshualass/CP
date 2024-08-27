#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    ll n, m; cin >> n >> m;
    vector<vector<int>> adj;
    vector<int> firsts;
    int gm = 0;
    for(int i = 0; i < n; i++) {
        ll l; cin >> l;
        while(adj.size() < l + 2) {
            adj.push_back({});
            firsts.push_back(0);
        }

        vector<int> vis(l + 2);
        for(int j = 0; j < l; j++) {
            int num; cin >> num;
            if(num < l + 2) {
                vis[num] = 1;
            }
        }
        vector<int> holes;
        for(int j = 0; j < l + 2; j++) {
            if(vis[j] == 0) {
                holes.push_back(j);
                if(holes.size() == 2) {
                    break;
                }
            }
        }

        assert(holes.size() == 2);

        adj[holes[1]].push_back(holes[0]);
        firsts[holes[0]]++;
    }

    vector<int> bestholes(firsts.size());

    for(int i = bestholes.size() - 1; i >= 0; i--) {
        bestholes[i] = max(bestholes[i], i);
        if(firsts[i]) {
            gm = max(gm, i);
        }
        if(firsts[i] >= 2) {
            gm = max(gm, bestholes[i]);
        }
        for(int c : adj[i]) {
            bestholes[c] = max(bestholes[c], bestholes[i]);
        }
    }

    ll res = 0;
    ll boost = min((ll) bestholes.size(), m + 1);
    for(int i = 0; i < boost; i++) {
        res += max(bestholes[i],gm);
    }

    ll left = m + 1 - boost;
    res += (boost + boost + left - 1) * left / 2;
    cout << res << '\n';

}

//     ll res = 0;
    
//     ll boost = min(m + 1, hi + 1);

//     // cout << "boost : " << boost << '\n';

//     res += boost * hi;
//     ll leftlength = m + 1 - boost;

//     // cout << "left length : " << leftlength << '\n';

//     res += (boost + boost + leftlength - 1) * leftlength / 2;
//     cout << res << '\n';

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// void solve() {
    
//     ll n, m; cin >> n >> m;
//     ll hi = 0;

//     for(int i = 0; i < n; i++) {
//         ll l; cin >> l;
//         vector<int> vis(l + 2);
//         for(int j = 0; j < l; j++) {
//             int num; cin >> num;
//             if(num < l + 2) {
//                 vis[num] = 1;
//             }
//         }
//         int holecnt = 0;
//         for(int j = 0; j < l + 2; j++) {
//             if(vis[j] == 0) {
//                 holecnt++;
//                 if(holecnt == 2) {
//                     hi = max(hi, (ll) j);
//                     break;
//                 }
//             }
//         }
//     }

//     // cout << "hi : " << hi << '\n';

//     ll res = 0;
    
//     ll boost = min(m + 1, hi + 1);

//     // cout << "boost : " << boost << '\n';

//     res += boost * hi;
//     ll leftlength = m + 1 - boost;

//     // cout << "left length : " << leftlength << '\n';

//     res += (boost + boost + leftlength - 1) * leftlength / 2;
//     cout << res << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }