#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int a, b, c; cin >> a >> b >> c;

    for(int i = 0; i < 5; i++) {
        if(a <= b && a <= c) {
            a++;
        } else if(b <= a && b <= c) {
            b++;
        } else {
            c++;
        }
    }
    cout << a * b * c << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}