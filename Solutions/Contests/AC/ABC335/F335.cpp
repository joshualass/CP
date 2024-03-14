#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int MAXN = 200000;
const int SN = 447;

//pref doesn't need MAXN elements. Just needs for each prefix, all the mods. therefore only SN^2

ll pref[SN][SN];
ll adds[200000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    memset(pref,0,sizeof(pref));
    memset(adds,0,sizeof(adds));
    int n; cin >> n;

    ll res = 0;
    adds[0] = 1;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        ll curr = adds[i];
        for(int j = 1; j < SN; j++) {
            curr += pref[i%SN][j];
            if(curr >= MOD) curr -= MOD;
            if(j + i < n) {
                pref[(j + i)%j][j] += pref[i%j][j];
                if(pref[(j + i)%j][j] >= MOD) pref[(j + i)%j][j] -= MOD;
            }
        }
        if(num < SN) {
            if(num + i < n) {
                pref[(num + i)%num][num] += curr;
                if(pref[(num + i)%num][num] >= MOD) pref[(num + i)%num][num] -= MOD;
            }
        } else {
            for(ll j = 1; i + num * j < n; j++) {
                adds[i + num * j] += curr;
                if(adds[i + num * j] >= MOD) adds[i + num * j] -= MOD;
            }
        }
        res += curr;
        if(res >= MOD) res -= MOD;
    }
    cout << res << '\n';

    return 0;
}

// ll pref[200000][SN];
// ll adds[200000];

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     memset(pref,0,sizeof(pref));
//     memset(adds,0,sizeof(adds));
//     int n; cin >> n;

//     ll res = 0;
//     adds[0] = 1;
//     for(int i = 0; i < n; i++) {
//         ll num; cin >> num;
//         ll curr = adds[i];
//         for(int j = 1; j < SN; j++) {
//             curr += pref[i][j];
//             if(curr >= MOD) curr -= MOD;
//             if(j + i < n) {
//                 pref[j + i][j] += pref[i][j];
//                 if(pref[j + i][j] >= MOD) pref[j + i][j] -= MOD;
//             }
//         }
//         if(num < SN) {
//             if(num + i < n) {
//                 pref[num + i][num] += curr;
//                 if(pref[num + i][num] >= MOD) pref[num + i][num] -= MOD;
//             }
//         } else {
//             for(ll j = 1; i + num * j < n; j++) {
//                 adds[i + num * j] += curr;
//                 if(adds[i + num * j] >= MOD) adds[i + num * j] -= MOD;
//             }
//         }
//         res += curr;
//         if(res >= MOD) res -= MOD;
//     }
//     cout << res << '\n';

//     return 0;
// }