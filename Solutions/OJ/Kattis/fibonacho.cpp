#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll a3, a4, a5; cin >> a3 >> a4 >> a5;
    ll a2 = a5 - a4;
    ll a1 = a4 - a3;
    ll a0 = a3 - a2;
    cout << a0 << " " << a1 << " " << a2 << '\n';

    return 0;
}
