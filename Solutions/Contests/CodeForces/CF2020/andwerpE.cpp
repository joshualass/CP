#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll mod = 1e9 + 7;
ll a[200000 + 100];
ll p[200000 + 100];
ll pmo[200000 + 100];
ll dp[2][1024];

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
  // Function to compute a/b under modulo m
ll modDivide(ll a, ll b) {
    a = a % mod;
    int inv = modInverse(b, mod);
    return (inv * a) % mod;
}
 
ll gcdExtended(ll a, ll b, ll *x, ll *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    dp[0][0] = 1;
    ll inv10k = modInverse(10000, mod);
    int t, n;
    ll ans;
    cin >> t;
    while(t--){
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> p[i];
            p[i] = (p[i] * inv10k) % mod;
            pmo[i] = 1 - p[i];
            if(pmo[i] < 0){
                pmo[i] += mod;
            }
        }
        ans = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < (1 << 10); j++){
                dp[1][j] = dp[0][j] * pmo[i];
            }
            for(int j = 0; j < (1 << 10); j++){
                dp[1][j ^ a[i]] += dp[0][j] * p[i];
                dp[1][j ^ a[i]] %= mod;
            }
            swap(dp[0], dp[1]);
        }
        for(int i = 0; i < (1 << 10); i++){
            ans += dp[0][i] * (i * i);
            ans %= mod;
            dp[0][i] = 0;
        }
        dp[0][0] = 1;
        cout << ans << "\n";
    }
    
    return 0;
}