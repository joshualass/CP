#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
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

//make the observation, the probability of each bit does not solve the problem. consider 3 with .5 and 1 with .5 and 2 with .5. The bits have the same probability, but they have different expected values. 

void solve() {
    int n; cin >> n;
    vector<ll> a(n), p(n);
    for(auto &x : a) cin >> x;
    for(auto &x : p) cin >> x;

    vector<ll> dp(1024), prev(1024);
    prev[0] = 1;
    for(int i = 0; i < n; i++) {
        ll pon = p[i] * modInverse(10000,MOD) % MOD;
        ll poff = (10000 - p[i]) * modInverse(10000,MOD) % MOD;
        for(int j = 0; j < 1024; j++) {
            dp[j] = (prev[j] * poff + prev[j ^ a[i]] * pon) % MOD;
        }
        swap(dp,prev);
    }



    // vector<array<ll,2>> bits(10, {1,0}); //{off, on}

    // for(int bit = 0; bit < 10; bit++) {

    //     for(int i = 0; i < n; i++) {
    //         if((a[i] >> bit) & 1) {
    //             ll pon = p[i] * modInverse(10000,MOD) % MOD;
    //             ll poff = (10000 - p[i]) * modInverse(10000,MOD) % MOD;
    //             array<ll,2> next = {
    //                 (bits[bit][0] * poff + bits[bit][1] * pon) % MOD,
    //                 (bits[bit][0] * pon + bits[bit][1] * poff) % MOD
    //             };
    //             bits[bit] = next;
    //         }
    //     }

    // }

    // cout << "bits : " << bits << '\n';

    ll res = 0;
    // for(int bit1 = 0; bit1 < 10; bit1++) {
    //     for(int bit2 = 0; bit2 < 10; bit2++) {
    //         res = ((1LL << (bit1 + bit2)) * bits[bit1][1] % MOD * bits[bit2][1] + res) % MOD;
    //     }
    // }
    for(int num = 0; num < 1024; num++) {
        ll prob = prev[num];
        if(prob) {
            // cout << "num : " << num << "prob : " << prob << '\n';
        }
        res = (res + prob * num % MOD * num) % MOD;
        // cout << "r : " << res << '\n';
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << 1023 * 1023 * modInverse(2,MOD)%MOD << '\n';

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}