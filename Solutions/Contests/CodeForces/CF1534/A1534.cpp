#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    auto color = [&](char a, char b) -> vector<string> {
        vector<string> res(n, string(m, 'a'));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if((i + j) % 2 == 0) {
                    res[i][j] = a;
                } else {
                    res[i][j] = b;
                }
            }
        }
        return res;
    };

    auto check = [&](vector<string> a, vector<string> t) -> bool {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(a[i][j] != '.') {
                    if(t[i][j] != a[i][j]) return 0;
                }
            }
        }
        return 1;
    };

    auto test1 = color('R', 'W');
    auto test2 = color('W', 'R');

    vector<string> res;

    if(check(a, test1)) {
        res = test1;
    }
    if(check(a, test2)) res = test2;

    if(sz(res)) {
        cout << "YES\n";
        for(auto &x : res) cout << x << '\n';
    } else {
        cout << "NO\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}