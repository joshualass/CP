//https://open.kattis.com/problems/tiles

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    ll n = a.size();

    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (ll i = 0; i < n; i += len) {
            cd w(1);
            for (ll j = 0; j < len / 2; j++) {
                cd u = a[i+j], v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd & x : a)
            x /= n;
    }
}

vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    ll n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (ll i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(n);
    for (ll i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}

const ll N = 5e6 + 1;

ll prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <ll> prime;

void sieve (ll n) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (ll i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
		    prime.push_back(i);
            prime_factor[i] = i;
        }
		for (ll j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << p.second << " " << p.first << " ";
    return os;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    sieve(N);
    vector<ll> v(N,0);
    v[1] = 1;
    for(ll i = 2; i < N; i++) {
        unordered_map<ll,ll> factors;
        ll a = i;
        while(a != 1) {
            if(factors.find(prime_factor[a]) == factors.end()) {
                factors[prime_factor[a]] = 1;
            } else {
                factors[prime_factor[a]]++;
            }
            a /= prime_factor[a];
        }
        ll poss = 1;
        for(auto x : factors) {
            poss *= x.second + 1;
        }
        v[i] = poss;
    }
    vector<ll> vv = v;
    vector<ll> ans = multiply(v,vv);

    ll q; cin >> q;
    for(ll i = 0; i < q; i++) {
        ll l, r; cin >> l >> r;
        pair<ll,ll> p = {-1,-1};
        for(ll j = l; j <= r;j++) {
            if(max(0LL,ans[j])> p.first) {
                p = {ans[j],j};
            }
        }
        cout << p << "\n";
    }


    return 0;
}