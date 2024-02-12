#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int a, b; cin >> a >> b;
    if(a > b) swap(a,b);
    if(a % 2 == 0 || b % 2 == 0 && a * 2 != b) {
        cout << "yes\n";
    } else {
        cout << "no\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}