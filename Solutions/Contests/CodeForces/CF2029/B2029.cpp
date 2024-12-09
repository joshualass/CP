#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

// void solve() {
//     string s, r; cin >> s >> r;
//     array<int,4> poss = {};
//     if(s[r.size()] == '0') {
//         poss[0] = 1;
//     } else {
//         poss[3] = 1;
//     }
//     poss[s[r.size()]-'0'] = 1;
//     for(int i = r.size() - 1; i >= 0; i--) {
//         array<int,4> nextposs = {};
//         if(s[i] == '0') {

//         }
//     }
// }

void solve() {
    int n; cin >> n;
    string s, r; cin >> s >> r;
    int o = count(s.begin(),s.end(),'1'), z = count(s.begin(),s.end(),'0');
    int ok = 1;
    for(int i = 0; i < r.size(); i++) {
        if(o == 0 || z == 0) {
            ok = 0;
        }
        o--; z--;
        if(r[i] == '0') {
            z++;
        } else {
            o++;
        }
    }
    cout << (ok ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}