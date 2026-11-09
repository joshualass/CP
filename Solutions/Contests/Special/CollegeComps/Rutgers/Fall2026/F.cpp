#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    auto check = [&](int test) -> int {
        vector<int> c, d;
        for(int x : a) {
            if(x <= test) c.push_back(x);
        }
        for(int x : b) {
            if(x <= test) d.push_back(x);
        }
        return c == d;
    };

    int l = 1, r = min(n, m);
    while(l != r) {
        int m = (l + r + 1) / 2;
        if(check(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    cout << abs(l - n) + abs(l - m) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}