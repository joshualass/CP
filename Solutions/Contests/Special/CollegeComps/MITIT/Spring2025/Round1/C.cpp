#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;

    string s; cin >> s;
    vector<array<int,2>> res;
    int o = 1, e = 2;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'E') {
            if(e * 2 + 2 <= o * 2 + 2 && e + 2 <= n * 2) {
                res.push_back({e, e + 2});
                e += 4;
            } else {
                res.push_back({o, o + 2});
                o += 4;
            }
        } else {
            res.push_back({o, e});
            o += 2;
            e += 2;
        }
    }

    int m = 0;
    for(auto x : res) for(auto y : x) m = max(m, y);

    if(m <= n * 2) {
        cout << "YES\n";
        for(array<int,2> x : res) cout << x[0] << " " << x[1] << '\n';
    } else {
        cout << "NO\n";
    }

    // cout << "o : " << o << " e : " << e << '\n';


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}