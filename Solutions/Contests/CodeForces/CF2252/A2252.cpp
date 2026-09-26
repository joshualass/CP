#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x]++;
    }    

    int res = 0;
    for(auto [k, v] : m) {
        int rest = n - v;
        res += min({v, (n + 1) / 2 + 1, rest + 2}) * k;
    }

    cout << res << '\n';

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