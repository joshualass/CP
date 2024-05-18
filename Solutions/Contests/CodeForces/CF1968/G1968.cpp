#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    set<int> s;
    for(int i = 1; i <= 200000; i++) {
        s.insert(200000 / i);
    }
    cout << s.size() << '\n';
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}