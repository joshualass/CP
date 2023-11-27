#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool poss(int a, int b, int c) {
    return (((b + c) & 1) == 0);
}

void solve() {
    int a, b, c; cin >> a >> b >> c;
    cout << poss(a,b,c) << " " << poss(b,a,c) << " " << poss(c,a,b) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}