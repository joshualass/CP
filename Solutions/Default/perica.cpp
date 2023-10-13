//https://open.kattis.com/problems/perica
//pretty straightforward choose logic
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 1e6;
ll factorials[N+1];

//finds all factorials 0-N iteratively
void factorial(int n, ll MOD) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
}

//TODO replace with template that supports all modular operations
ll binexp(ll base, ll power, ll MOD = 1e9 + 7) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

//returns a / b using modular inverse. this implementation uses fermat's little theorem
ll modDivide(ll a, ll b, ll MOD = 1e9 + 7) {
    return binexp(b,MOD-2,MOD) * a % MOD;
}

ll choose(ll n, ll k) {
    if(k > n) return 0;
    return modDivide(factorials[n],factorials[n-k] * factorials[k] % MOD);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    factorial(N,MOD);
    ll n, k; cin >> n >> k;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    sort(v.begin(),v.end());
    ll ans = 0;
    for(int i = k - 1; i < n; i++) {
        // cout << "i: " << i << " " << (choose(i + 1, k) - choose(i,k)) << " ways to make: " << v[i] << "\n";
        ans = (ans + (choose(i + 1, k) - choose(i,k) + MOD) * v[i]) % MOD;
    }   
    cout << ans << "\n";
    return 0;
}