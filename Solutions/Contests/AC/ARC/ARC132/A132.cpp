#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> r(n);
    vector<int> c(n);

    for(auto &x: r) cin >> x;
    for(auto &y: c) cin >> y;
    int q; cin >> q;

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        if(r[a] + c[b] > n) {
            cout << "#";
        } else {
            cout << ".";
        }
    }

    return 0;
}