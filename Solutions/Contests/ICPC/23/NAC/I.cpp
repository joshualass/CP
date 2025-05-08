#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;

#define rep(i, a, b) for(int i = 0; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

const ll inf = 1'000'000'000'000'000'005;

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / M * a * b);
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}

ull modpow(ull b, ull e, ull mod) {
    ull ans = 1;
    for(; e; b = modmul(b, b, mod), e /= 2)
        if(e & 1) ans = modmul(ans, b, mod);
    return ans;
}

bool MRisPrime(ull n) {
    if(n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022}, s = __builtin_ctzll(n-1), d = n >> s;
    for(ull a : A) {
        ull p = modpow(a % n, d, n), i = s;
        while(p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
        if(p != n - 1 && i != s) return 0;
    }
    return 1;
}

const ll N = 2e6;
vector<int> primes;
vector<int> isPrime(N, 1);

void sieve() {
    isPrime[0] = 0, isPrime[1] = 0;
    for(int i = 2; i <= N; i++) {
        if(isPrime[i]) {
            primes.push_back(i);
            for(int j = i + i; j <= N; j += i) isPrime[j] = 0;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    sieve();

    ll x; cin >> x;

    if(x == 1) {
        cout << "1\n";
        return 0;
    }

    auto get_p = [&](ll a, ll b) -> ll {
        ll res = 1;
        for(int i = 0; i < b; i++) {
            if(inf / a < res) res = inf;
            else res *= a;
        }
        return res;
    };

    for(ll p = 2; p <= 60; p++) {
        ll est = powl(x, 1.0 / p);
        while(get_p(est + 1, p) <= x) est++;
        while(get_p(est, p) > x) est--;
        if(get_p(est,p) != x) continue;
        ll cop = est;

        // cout << "p : " << p << " est : " << est << '\n';

        if(p == 2) {
            if(MRisPrime(est)) {
                cout << est << '\n';
                return 0;
            }
        } else {
            ll f = 1;
            for(ll p : primes) {
                ll c = 1;
                while(est % p == 0) {
                    est /= p;
                    c++;
                }
                f *= c;
            }
            if(f == p) {
                cout << cop << '\n';
                return 0;
            }
        }
    }

    cout << "-1\n";

    return 0;
}