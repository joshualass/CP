#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll a, b; cin >> a >> b;
    if(a > b) swap(a,b);

    ll crosses = gcd(a,b);
    a /= crosses;
    b /= crosses;
    if((a & 1) && (b & 1)) {
        cout << crosses << '\n';
    } else {
        cout << "0\n";
    }

    return 0;
}