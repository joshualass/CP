#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    string x, y; cin >> x >> y;
    bool eq = 1;
    for(int i = 0; i < x.size(); i++) {
        if(eq) {
            if(x[i] != y[i]) {
                if(y[i] > x[i]) {
                    swap(x[i], y[i]);
                }
                eq = 0;
            }
        } else if(x[i] > y[i]) swap(x[i],y[i]);
    }
    cout << x << '\n' << y << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}