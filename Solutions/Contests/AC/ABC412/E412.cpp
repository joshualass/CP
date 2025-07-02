#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
	ll ret = a * b - M * ull(1.L / M * a * b);
	return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
	ull ans = 1;
	for (; e; b = modmul(b, b, mod), e /= 2)
		if (e & 1) ans = modmul(ans, b, mod);
	return ans;
}

bool isPrime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ull l, r; cin >> l >> r;
    ll res = 1;

    set<ll> s;
    for(ll p = 3; p <= 48; p++) {
        ll i = 2;
        while(1) {
            ll r = 1;
            if(isPrime(i)) {
                for(ll j = 0; j < p; j++) {
                    r *= i;
                    r = min(r, (ll)1e15);
                }

                if(r <= 1e14) {
                    s.insert(r);
                } else {
                    break;
                }
            }
            i++;
        }
    }

    auto is_square = [&](ll x) -> ll {
        ll sq = sqrt(x);
        while(sq * sq < x) sq++;
        while(sq *sq > x) sq--;
        return sq * sq == x && isPrime(sq);
    };

    for(ull i = l + 1; i <= r; i++) {
        if(is_square(i) || s.count(i) || isPrime(i)) res++;
    }

    cout << res << '\n';

    return 0;
}