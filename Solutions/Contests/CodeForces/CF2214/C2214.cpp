#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
RXOEARDMTINHUSERMEDESIANT & 20260401

R O A D T N U E M D S A T
R O A D 
*/

void solve() {
    
    int a, b, c; cin >> a >> b >> c;
    cout << (a ^ b ^ c) - (a + b + c - min({a, b, c}) - max({a, b, c})) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}