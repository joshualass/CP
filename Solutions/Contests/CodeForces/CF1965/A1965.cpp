#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    set<int> s(v.begin(),v.end());
    vector<int> a(s.begin(), s.end());
    n = a.size();
    if(n == 1) {
        cout << "Alice\n";
        return;
    }
    for(int i = 0; i < n; i++) {
        bool freedom = 0;
        if(i == 0 && a[i] != 1) freedom = 1;
        if(i != 0 && a[i]-1 != a[i-1]) freedom = 1;
        if(freedom) {
            cout << (i & 1 ? "Bob" : "Alice") << '\n';
            return;
        }
    }
    cout << (n & 1 ? "Alice" : "Bob") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}