#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x, x--;
    bool poss = 0;
    for(int i = 0; i < n; i++) {

        if(a[a[i]] == i) poss = 1;

    }
    cout << 3 - poss << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}