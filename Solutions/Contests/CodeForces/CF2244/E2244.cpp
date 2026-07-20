#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, q; cin >> n >> q;
    string s; cin >> s;
    vector<int> p(n);
    for(int i = 1; i < n; i++) {
        p[i] = p[i-1] + (s[i] == s[i-1]);
    }

    for(int qq = 0; qq < q; qq++) {
        int l, r, k; cin >> l >> r >> k;
        int ops = p[r - 1] - p[l - 1];
        cout << ((ops + 1) / 2 <= k ? "YES" : "NO") << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}