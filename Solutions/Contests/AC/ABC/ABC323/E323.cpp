#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
  // Function to compute a/b under modulo m
ll modDivide(ll a, ll b) {
    a = a % MOD;
    int inv = modInverse(b, MOD);
    return (inv * a) % MOD;
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;
    ll choose = modDivide(1,n);
    vector<ll> songs(n);
    for(auto &y: songs) cin >> y;
    vector<ll> probs(x+2);
    probs[0] = 1;
    for(int i = 0; i <= x; i++) {
        for(int j = 0; j < n; j++) {
            if(i + songs[j] <= x) {
                probs[i + songs[j]] = (probs[i] * choose + probs[i + songs[j]]) % MOD;
                // cout << "add possibility " << i << " to: " << i + songs[j] << "\n";
            } else if(j == 0 && i + songs[j] >= x+1) {
                probs[x+1] = (probs[i] * choose + probs[x+1]) % MOD;
                // cout << "add to answer: " << i << "\n";
            }
        }
    }
    cout << probs[x+1] << "\n";
    return 0;
}