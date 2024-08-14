#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
some observations 
a0 is easy to calculate, ad = bd. 
We can determine the leading coefficient of the highest degree with the help of finite differences.
Using our finite differences magic, we can extract the ad term, as well as the a_{d-1} term which we are really after
do the same for the b polynomial. Then, we take the differences between these 2 numbers, divide by our ad and d.

Finite differences magic - when analyzing a point on the graph the contribution in finite differences that this point has in calculating the leading coefficient is

A[i] * d choose d - i. We add or subtract this value depending on the parity of the distance from d. 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
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

pair<vector<ll>, ll> extractlcf(vector<ll> &poly) {
    
    ll res = 0;
    ll deg = poly.size() - 1;
    for(int i = deg; i >= 0; i--) {
        ll mult = ((deg - i) & 1 ? -1 : 1);
        ll add = poly[i] * choose(deg, deg - i) % MOD * mult;
        // cout << "add : " << add << " res : " << res << endl;
        // cout << "i : " << i << " poly : " << poly[i] << " c : " << choose(deg, deg - i) << " m : " << mult << '\n';
        res = (res + MOD + add) % MOD;
    }
    
    // cout << "res ok here : " << res << endl;
    
    res = (res * inv_fact[deg]) % MOD;
    
    // cout << "res : " << res << endl;
    
    for(int i = 0; i < deg; i++) {
        poly[i] = ((poly[i] - res * binexp(i,deg) % MOD + MOD) % MOD);
    }
    poly.pop_back();
    return {poly, res};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll d; cin >> d;
    vector<ll> a(d+1), b(d+1);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;
    
    auto [ae, ac1] = extractlcf(a);
    auto [aee, ac2] = extractlcf(ae);
    
    auto [be, bc1] = extractlcf(b);
    auto [bee, bc2] = extractlcf(be);
    
    // cout << "ac1 : " << ac1 << " ae : " << ae << '\n';
    // cout << "ac2 : " << ac2 << " aee : " << aee << '\n';
    
    // cout << "bc1 : " << bc1 << " be : " << be << '\n';
    // cout << "bc2 : " << bc2 << " bee : " << bee << '\n';
    
    // cout << "diff : " << ((bc2 - ac2 + MOD) % MOD) << " divide by : " << ac1 << " and divide by " << d << "!\n";
    
    cout << ((bc2 - ac2 + MOD) % MOD) * modInverse(ac1,MOD) % MOD * modInverse(d,MOD) % MOD << '\n';

    return 0;
}

//math research

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     // cout << "build polynomial of degree" << endl;
//     // ll n; cin >> n;
//     // cout << "upper bound of coefficients" << endl;
//     // ll hi; cin >> hi;
    
//     // vector<ll> poly;
//     // for(int i = 0; i <= n; i++) {
//     //     poly.push_back(rng() % hi + 1);
//     // }
    
//     vector<ll> poly = {9,7,5,6,7,8};
//     ll n = 5;
    
//     cout << "polynomial is : ";
    
//     for(int i = 0; i <= n; i++) {
//         cout << poly[i] << "x^{" << i << "} " << "+\n"[i == n];
//     }
    
//     cout << "differentiation tree\n";
    
//     vector<ll> tree;
//     for(int i = 0; i <= n; i++) {
//         vector<ll> next;
//         if(i) {
//             for(int i = 0; i < tree.size() - 1; i++) {
//                 next.push_back((tree[i+1] - tree[i] + MOD) % MOD);
//             }
//         } else {
//             next.assign(n+1,poly[0]);
//             for(ll j = 1; j <= n; j++) { // degree
//                 for(ll k = 0; k <= n; k++) { // x
//                     ll mult = k;
//                     for(ll l = 1; l < j; l++) {
//                         mult *= k;
//                         mult %= MOD;
//                     }
//                     next[k] = (next[k] + poly[j] * mult) % MOD;
//                 }
//             }
//         }
//         cout << "i : " << i << " poly : ";
//         for(int j = 0; j < next.size(); j++) {
//             cout << next[j] << " \n"[j == next.size() - 1];
//         }
//         tree = next;
//     }

//     return 0;
// }