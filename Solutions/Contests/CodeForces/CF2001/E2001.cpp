#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD;
const int N = 1e6;
ll factorials[N+1];

/*
We solve with the most obvious approach. At each depth, compute the number of ways for the current node to be v as well as how many ways to do it with 0 - k operations done on the tree leading up to v. 
The number of ways to do it to each child 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//finds all factorials 0-N iteratively
void factorial(int n = N, ll MOD = MOD) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
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

ll choose(ll n, ll k) {
    if(k > n) return 0;
    return modDivide(factorials[n],factorials[n-k] * factorials[k] % MOD);
}

void solve() {
    ll n, k; cin >> n >> k >> MOD;

    vector<ll> curr(k + 1);
    curr[k] = 1;

    for(int depth = 0; depth < n - 1; depth++) {

        // cout << "start curr : " << curr << '\n';

        ll childrenssize = binexp(2,n - (depth + 1)) - 1;
        ll bars = childrenssize - 1;

        vector<ll> chooses(k+1); //let x be k, y be childrensize. Then, calculating i + y - 1 choose i. Do some maths on paper. 
        chooses[0] = 1;

        // cout << "ssize : " << childrenssize << '\n';
        // cout << "bars : " << bars << '\n';

        for(ll i = 1; i <= k; i++) {
            // cout << "i : " << i << " mul : " << (bars + i) << " div : " << i << '\n';
            chooses[i] = chooses[i-1] * (bars + i) % MOD * modInverse(i, MOD) % MOD;
        }

        // cout << "chooses : " << chooses << '\n';

        vector<ll> p(k + 2);
        for(ll i = 1; i <= k + 1; i++) {
            p[i] = (p[i-1] + curr[i-1]) % MOD;
        }

        // cout << "p : " << p << '\n';

        vector<ll> next(k + 1);

        for(ll i = 0; i <= k; i++) {//i going to other subtree
            for(ll j = i + 1; i + j <= k; j++) {//j going to next node

                ll minneeded = i + j;

                // cout << "i : " << i << " j : " << j << " minneeded : " << minneeded << " addmul : " << p[k + 1] - p[minneeded] << '\n';

                next[j] = (next[j] + (p[k + 1] - p[minneeded] + MOD) * chooses[i]) % MOD;

            }
        }

        curr = next;
        // cout << "next : " << next << '\n';
    }

    ll sum = accumulate(curr.begin(), curr.end(), 0LL);
    cout << sum % MOD * binexp(2,n-1) % MOD << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}