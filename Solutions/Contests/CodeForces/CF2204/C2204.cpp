#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll a, b, c, m; cin >> a >> b >> c >> m;

    ll all = m / lcm(a, lcm(b, c));
    ll ab = m / lcm(a, b) - all, ac = m / lcm(a, c) - all, bc = m / lcm(b, c) - all;
    ll rema = m / a - ab - ac - all, remb = m / b - ab - bc - all, remc = m / c - ac - bc - all;

    // cout << "a : " << a << " b : " << b << " c : " << c << " m : " << m << endl;
    // cout << "all : " << all << endl;
    // cout << "ab : " << ab << " ac : " << ac << " bc : " << bc << endl;
    // cout << "rema : " << rema << " remb : " << remb << " remc : " << remc << endl;

    cout << rema * 6 + (ab + ac) * 3 + all * 2 << " " << remb * 6 + (ab + bc) * 3 + all * 2 << " " << remc * 6 + (ac + bc) * 3 + all * 2 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}