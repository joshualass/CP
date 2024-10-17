#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
a good amount of thinking was done to solve this problem. 
we want to remove all n terms. 
Then, we need to find solutions of the form l(l-1) equiv 0 mod n. 
Need to study CRT more. 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <int> prime;

void sieve (int n = N) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (int i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
		    prime.push_back(i);
            prime_factor[i] = i;
        }
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

//O(sqrt(n)), approx. cuberoot(n) factors. 
vector<ll> find_divisors(int num) {
    // map<int,int> factors;
    vector<ll> factors;
    // cout << "num: " << num << " ";
    for(ll i = 0; i < prime.size() && prime[i] * prime[i] <= num; i++) {
        bool first = 1;
        while(num % prime[i] == 0) {
            if(first) {
                factors.push_back(prime[i]);
                first = 0;
            } else {
                factors.back() *= prime[i];
            }
            num /= prime[i];
        }
    }
    if(num != 1) {
        factors.push_back(num);
    }
    return factors;
}

//regular 
ll gcd ( ll a, ll b ) {
    while ( b ) {
        a = a % b;
        swap ( a, b );
    }
    return a;
}

//extended 
ll ext_gcd ( ll A, ll B, ll *X, ll *Y ){
    ll x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1; y2 = 0;
    x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }
    *X = x2; *Y = y2;
    return r2;
}

pair<ll, ll> chinese_remainder_theorem( vector<ll> A, vector<ll> M ) {
    if(A.size() != M.size()) return {-1,-1}; /** Invalid input*/
 
    ll n = A.size();
 
    ll a1 = A[0];
    ll m1 = M[0];
    /** Initially x = a_0 (mod m_0)*/
 
    /** Merge the solution with remaining equations */
    for ( ll i = 1; i < n; i++ ) {
        ll a2 = A[i];
        ll m2 = M[i];
 
        ll g = gcd(m1, m2);
        if ( a1 % g != a2 % g ) return {-1,-1}; /** No solution exists*/
 
        /** Merge the two equations*/
        ll p, q;
        ext_gcd(m1/g, m2/g, &p, &q);
 
        ll mod = m1 / g * m2; /** LCM of m1 and m2*/
 
        /** We need to be careful about overflow, but I did not bother about overflow here to keep the code simple.*/
        ll x = (a1*(m2/g)*q + a2*(m1/g)*p) % mod;
 
        /** Merged equation*/
        a1 = x;
        if (a1 < 0) a1 += mod; /** Result is not suppose to be negative*/
        m1 = mod;
    }
    return {a1, m1};
}

void solve() {
    ll n; cin >> n;
    vector<ll> M = find_divisors(n);

    // cout << "M : " << M << '\n';

    vector<ll> res;
    vector<ll> A(M.size());

    for(int i = 0; i < 1 << M.size(); i++) {
        for(int j = 0; j < M.size(); j++) {
            A[j] = ((i >> j) & 1);
        }
        // cout << "A : " << A << '\n';
        // cout << "M : " << M << '\n';
        auto [ans, mod] = chinese_remainder_theorem(A, M);
        // cout << "ans : " << ans << '\n';
        res.push_back((n - 1) * ans + 1);
    }

    sort(res.begin(), res.end());

    for(auto r : res) {
        if(r > 1 && r < n * (n + 1)) {
            cout << r << " ";
        }
    }

    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}