#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll mod = 1e9 + 7;

ll binaryexponentiation(ll a, ll b) {
    ll ans = 1;
    while(b != 0) {
        if(b & 1) {
            ans *= a;
            ans %= mod;
        }
        b >>= 1;
        a *= a;
        a %= mod;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    while(n-->0) {
        ll a, b, c;
        cin >> a >> b >> c;
        cout << binaryexponentiation(a, binaryexponentiation(b,c)) << '\n';
    }
    
    return 0;
}