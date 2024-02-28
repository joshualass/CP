#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for(int &x : v) cin >> x;
    int sum = reduce(v.begin(), v.end()) % 3;
    int has1 = 0;
    for(int i = 0; i < n; i++) {
        has1 |= v[i] % 3 == 1;
    }
    
    if(sum == 0) {
        cout << "0\n";
    } else if(sum == 1) {
        if(has1) {
            cout << "1\n";
        } else {
            cout << "2\n";
        }
    } else {
        cout << "1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}