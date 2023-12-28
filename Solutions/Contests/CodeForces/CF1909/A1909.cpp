#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    vector<bool> v(4);

    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        if(x > 0) v[0] = 1;
        if(x < 0) v[1] = 1;
        if(y > 0) v[2] = 1;
        if(y < 0) v[3] = 1;
    }
    if(count(v.begin(),v.end(),1) == 4) {

        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}