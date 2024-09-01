#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*

First, assume that FJ always has the cow on the far left and we multiply the number of configurations by 2 at the end.
The optimal strategy involves looking at the distance to the next cow for any of FJ's cows. 
If all the distances have an even parity of open spaces between the next cow, it is a loss because this state can always be maintained.
Now, we need to find a way to count the number of valid configurations. 
We get this number by counting 
We can kind of reorder the dependencies instead of having them be between every other cow. 
Once we reorder, we fix the furthest right cow that is under the influence of the dependencies and count the number of ways to do this.

*/

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

ll binexp(ll base, ll power) {
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

vector<ll> fact(1,1);
vector<ll> inv_fact(1,1);

ll choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    while(fact.size() < n + 1) {
        fact.push_back(fact.back() * fact.size() % MOD);
        inv_fact.push_back(modInverse(fact.back(), MOD));
    }

    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

void solve() {
    
    ll l, n; cin >> l >> n;
    ll totalconfigs = choose(l, n * 2);
    ll losscount = 0;

    for(ll left = n + 1, right = l - (n + 1); right >= n - 1; left++, right--) {

        ll emptyspaces = (left - (n + 1)) / 2;

        ll numleft = choose(n + emptyspaces, n);
        ll numright = choose(right, n - 1);

        // cout << "left : " << left << " right : " << right << " empty : " << emptyspaces << " numleft : " << numleft << " numright : " << numright << '\n';

        losscount = (losscount + numleft * numright) % MOD;

    }

    // cout << "total configs : " << totalconfigs << " losses : " << losscount << '\n';

    cout << ((totalconfigs - losscount + MOD) * 2) % MOD << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}