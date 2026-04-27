#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#define rep(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

mt19937 rng;

bool isprime(ll num) {
    if(num <= 1) return 0;
    if(num == 2 || num == 3) return 1;
    if(num % 2 == 0 || num % 3 == 0) return 0;
    for(int i = 5; i <= sqrt(num); i++) {
        if(num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

ll gen_prime(ll l, ll r) { //generates a prime number [l,r]
    while(1) {
        ll num = (rng() % (r - l + 1)) + l;
        if(isprime(num)) return num;
    }
}

ll M1, M2, B1, B2;
struct stringhash {
    vector<ll> h1, h2;
    vector<ll> p1, p2;
    int n;

    stringhash(string s) {
        this->n = s.size();
        p1.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p1.push_back(p1.back() * B1 % M1);
        }
        p2.push_back(1);
        for(int i = 0 ; i < n; i++) {
            p2.push_back(p2.back() * B2 % M2);
        }
        h1.push_back(0);
        for(int i = 0; i < n; i++) {
            h1.push_back((h1[i] * B1 + s[i]) % M1);
        }
        h2.push_back(0);
        for(int i = 0; i < n; i++) {
            h2.push_back((h2[i] * B2 + s[i]) % M2);
        }
    }

    ll get_hash(int l, int r) { //[l,r) because that's the cool, Andwerp way
        ll num1 = (h1[r] - h1[l] * p1[r-l] % M1 + M1) % M1;
        ll num2 = (h2[r] - h2[l] * p2[r-l] % M2 + M2) % M2;
        return num1 + num2 * M1;
    }

};

void buildsh() {
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    M1 = gen_prime(900000000,1000000000);
    B1 = gen_prime(9000,10000);
    M2 = gen_prime(900000000,1000000000);
    B2 = gen_prime(9000,10000);
}

int better(stringhash& sh, string &s, int l1, int len1, int l2, int len2) {
    int min_len = min(len1, len2);

    if(sh.get_hash(l1, l1 + min_len) == sh.get_hash(l2, l2 + min_len)) {
        return len1 < len2;
    }

    int l = 0, r = min_len - 1;
    while(l != r) {
        int m = (l + r + 1) / 2;
        if(sh.get_hash(l1, l1 + m) == sh.get_hash(l2, l2 + m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    return s[l1 + l] < s[l2 + l];
}

void solve() {
    
    ll n, l, k; cin >> n >> l >> k;
    string s; cin >> s;

    if(1LL * l * k > n) {
        cout << "NO\n";
        return;
    }

    auto get_len = [&](ll idx) -> ll {
        if(idx > 0 && idx < l) return -1;
        ll need = k - 1;
        if(idx) {
            need -= max(1LL, min(need, idx / l));
        }
        if(need < 0) return -1;
        ll after = n - idx;
        after -= need * l;
        if(after < l) return -1;
        return after;
    };

    stringhash sh(s);

    int bl = -1, blen = -1;

    for(int i = 0; i < n; i++) {
        int len = get_len(i);
        if(len != -1) {
            if(bl == -1 || better(sh, s, bl, blen, i, len)) {
                bl = i;
                blen = len;
            }
        }
    }

    assert(bl != -1);
    cout << "YES\n";
    cout << s.substr(bl, blen) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    buildsh();

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}