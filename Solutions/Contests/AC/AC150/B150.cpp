#include <bits/stdc++.h>
typedef long long ll;
typedef __int128_t lll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll a, b; cin >> a >> b;
    if(a >= b) {
        cout << a - b << "\n";
        return;
    }
    //b is strictly greater
    ll ans = a - b % a; //we only try by increasing
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}