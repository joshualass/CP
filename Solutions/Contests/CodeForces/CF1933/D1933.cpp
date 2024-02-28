#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    int g = -1;
    for(int i = 0; i < n; i++) {
        cin >> v[i];
        if(i == 0) {
            g = v[i];
        } else {
            g = gcd(g,v[i]);
        }
    }
    for(int i = 0; i < n; i++) {
        v[i] /= g;
    }
    cout << (count(v.begin(), v.end(),1) <= 1 ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}