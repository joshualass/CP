//https://judge.yosupo.jp/problem/queue_operate_all_composite
/*
able to easily undo the first linear function
the slope/a coefficient can easily be undone by doing modular division on the current slope / undo slope
all numbers are positive so this is always possible
to update the y-intercept or b, we determine the coefficient that b has been multiplied after doing all these operations and remove that
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll gcdExtended(ll a, ll b, ll *x, ll *y) {
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
    ll x1, y1; // To store results of recursive call
    ll gcd = gcdExtended(b%a, a, &x1, &y1);
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}
ll modInverse(ll b, ll m) {
    ll x, y; // used in extended GCD algorithm
    ll g = gcdExtended(b, m, &x, &y);
    if (g != 1)
        return -1;
    return (x%m + m) % m;
}
 
ll modDivide(ll a, ll b, ll m) {
    a = a % m;
    ll inv = modInverse(b, m);
    return inv * a % m;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    ll currA = 1;
    ll currB = 0;
    queue<pair<ll,ll>> q;
    for(int i = 0; i < n; i++) {
        int type; cin >> type;
        if(type == 0) { //adding 
            ll a, b; cin >> a >> b;
            currB = (b + currB * a) % MOD;
            currA = (a * currA) % MOD;
            q.push({a,b});
        } else if(type == 1) { //popback
            pair<ll,ll> undo = q.front();
            q.pop();
            currA = modDivide(currA,undo.first,MOD);
            ll removeB = currA * undo.second % MOD;
            currB = (currB - removeB + MOD) % MOD;
        } else if(type == 2) {
            ll x; cin >> x;
            x = (x * currA + currB) % MOD;
            cout << x << "\n";
        }
    }

    return 0;
}