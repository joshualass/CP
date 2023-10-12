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
    
    int n, m; cin >> n >> m;
    
    string str; cin >> str;
    ll ans = 1;
    for(int i = 1; i < str.size(); i++) {
        if(str[i] == '?') {
            ans = ans * i % MOD;
        }
    }
    // cout << str[0] << "\n";
    if(str[0] == '?') {
        cout << "0\n";
    } else {
        cout << ans << "\n";
    }
    for(int i = 0; i < m; i++) {
        int idx; cin >> idx;
        char c; cin >> c;
        if(str[--idx] == '?' && c != '?' && idx != 0) {
            ans = modDivide(ans,idx);
        }
        if(c == '?' && str[idx] != '?' && idx != 0) {
            ans = ans * idx % MOD;
        }
        str[idx] = c;
        if(str[0] == '?') {
            cout << "0\n";
        } else {
            cout << ans << "\n";
        }
    }

    return 0;
}