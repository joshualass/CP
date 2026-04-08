#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, m, a, b; cin >> n >> m >> a >> b;

    cout << (gcd(n, a) == 1 && gcd(m, b) == 1 && gcd(n,m) <= 2 ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}