#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

bool issquare(int n) {
    return ((int)sqrt(n)-1) * ((int)sqrt(n)-1) == n || ((int)sqrt(n)) * ((int)sqrt(n)) == n || ((int)sqrt(n)+1) * ((int)sqrt(n)+1) == n;
}

void solve() {
    int n; cin >> n;
    cout << (n % 2 == 0 && issquare(n/2) || n % 4 == 0 && issquare(n/4) ? "YES" : "NO") << '\n';
}

signed main() { 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}