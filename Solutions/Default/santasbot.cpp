//https://codeforces.com/contest/1279/problem/D
/*
if you have an irreducible fraction x/y and you need to prll x * y inverse,
you don't actually need the irreducible fraction, but rather the fractions that add up to the fraction
and can add x * y inverse of all those fractions and modulo.
2 ways to do modular division
*/
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
ll binexp(ll base, ll power, ll MOD = 1e9 + 7) {
    ll ans = 1;
    base %= MOD;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

//modular division finding the inverse from little fermat's theorem
ll fractional_answer(ll x, ll y) {
    ll yinv = binexp(y,MOD-2,MOD); 
    return yinv * x % MOD;
}
*/

// C function for extended Euclidean Algorithm (used to
// find modular inverse.
ll gcdExtended(ll a, ll b, ll *x, ll *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
 
    ll x1, y1; // To store results of recursive call
    ll gcd = gcdExtended(b%a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;
 
    return gcd;
}
ll modInverse(ll b, ll m)
{
    ll x, y; // used in extended GCD algorithm
    ll g = gcdExtended(b, m, &x, &y);
 
    // Return -1 if b and m are not co-prime
    if (g != 1)
        return -1;
 
    // m is added to handle negative x
    return (x%m + m) % m;
}
 
// Function to compute a/b under modulo m
ll modDivide(ll a, ll b, ll m)
{
    a = a % m;
    ll inv = modInverse(b, m);
    // if (inv == -1)
    //    cout << "Division not defined";
    // else
    //    cout << "Result of division is " << (inv * a) % m;
    return inv * a % m;
}
 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    vector<ll> cnts(1e6);
    vector<vector<ll>> reqs(n);
    for(ll i = 0; i < n; i++) {
        ll k; cin >> k;
        for(ll j = 0; j < k; j++) {
            ll num; cin >> num;
            num--;
            cnts[num]++;
            reqs[i].push_back(num);
        }
    }
    ll total_prob = 0;
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < reqs[i].size(); j++) {
            ll num = cnts[reqs[i][j]];
            ll den = n * reqs[i].size() * n;
            // cout << "num: " << num << " den: " << den << "\n";
            // total_prob += fractional_answer(num,den);
            total_prob += modDivide(num,den,MOD);
        }
    }
    cout << total_prob % MOD << "\n";
    return 0;
}