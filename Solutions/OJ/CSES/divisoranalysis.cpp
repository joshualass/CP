#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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
 // Function to compute a/b under modulo m
ll modDivide(ll a, ll b, ll m) {
    a = a % m;
    ll inv = modInverse(b, m);
    return inv * a % m;
}

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

ll geometric_summation(ll x, ll k) {
    ll num = binexp(x,k+1) - 1;
    ll den = x - 1;
    return modDivide(num,den,MOD);
}

ll trianglenumber(ll x, ll MOD) {
    if(x & 1) {
        return (x + 1) / 2 * x % MOD;
    } else {
        return x / 2 * (x + 1) % MOD;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<ll,ll>> v(n);
    for(auto &x: v) cin >> x.first >> x.second;
    ll num_divs = 1;
    for(int i = 0; i < n; i++) {
        num_divs *= v[i].second + 1;
        if(num_divs >= MOD) num_divs %= MOD;
    }
    cout << num_divs << " "; //step 1
    ll sum_divs = 1;
    for(int i = 0; i < n; i++) {
        sum_divs *= geometric_summation(v[i].first,v[i].second);
        if(sum_divs >= MOD) sum_divs %= MOD;
    }
    cout << sum_divs << " "; //step 2

    // ll prod_divs = 1;
    // ll num_divs_MOD1 = 1;
    // for(int i = 0; i < n; i++) {
    //     num_divs_MOD1 *= v[i].second + 1;
    //     if(num_divs_MOD1 >= (MOD - 1)) num_divs_MOD1 %= (MOD - 1);
    // }
    // cout << "num_divs_MOD1: " << num_divs_MOD1 << "\n";
    // for(int i = 0; i < n; i++) {
        // ll exp = modDivide((num_divs * v[i].second),2,MOD);
        // ll mult = binexp(v[i].first,exp,MOD);
        // prod_divs *= mult;
        // if(prod_divs >= MOD) prod_divs %= MOD;
        // cout << "numerator: " << (num_divs_MOD1 * v[i].second) << "\n";
        // ll exp = modDivide((num_divs_MOD1 * v[i].second) / g,2,(MOD-1)/g);
        // ll exp = num_divs_MOD1 * v[i].second / 2 % (MOD - 1);
        // cout << "exp: " << exp << "\n";
        // ll mult = binexp(v[i].first,exp,MOD);
        // prod_divs *= mult;
        // if(prod_divs >= MOD) prod_divs %= MOD;
        // ll times = trianglenumber(v[i].second,MOD-1) * num_divs_MOD1 % (MOD - 1);
        // ll testing = v[i].second * num_divs_MOD1 / 2 % (MOD - 1); 
        // cout << "test --- " << testing << "\n";
        // ll g = gcd(MOD-1, v[i].second);
        // ll times = modDivide(num_divs_MOD1/g,(v[i].second)/g,MOD-1) * v[i].second / 2 % (MOD-1);
        // cout << "first part: " << modDivide(num_divs_MOD1/g,(v[i].second+1)/g,MOD-1) << " times: " << times << "\n";
        // prod_divs = binexp(v[i].first,testing,MOD) % MOD * prod_divs % MOD;
    // }
    // cout << prod_divs << "\n";

    ll prod_divs = 1;
    ll num_divs_MOD1 = 1;
    for(int i = 0; i < n; i++) {
        ll expo = trianglenumber(v[i].second,MOD-1) * num_divs_MOD1 % (MOD-1);
        prod_divs = binexp(v[i].first, expo, MOD) * binexp(prod_divs, v[i].second + 1, MOD) % MOD;
        num_divs_MOD1 = num_divs_MOD1 * (v[i].second + 1) % (MOD - 1);
    }
    cout << prod_divs << endl;


    return 0;
}