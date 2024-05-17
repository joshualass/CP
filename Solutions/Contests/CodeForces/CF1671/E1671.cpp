#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD;
ll b;
mt19937 rng;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    // for(auto &x : v) os << x << " ";
    // return os;
    for(int i = 1; v.size() >= 1 << i; i++) {
        for(int j = 1 << (i - 1); 1 << i > j; j++) {
            // os << "i : " << i << " j : " << j << ' ';
            os << v[j] << ' ';
        }
        os << '\n';
    }
    return os;
}

bool isprime(ll num) {
    if(num <= 1) return 0;
    if(num == 2 || num == 3) return 1;
    if(num % 2 == 0 || num % 3 == 0) return 0;
    for(int i = 5; i <= sqrt(num); i++) {
        if(num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

ll gen_hash(ll l, ll r) {
    while(1) {
        ll num = (rng() % (r - l + 1)) + l;
        if(isprime(num)) return num;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
    
    ll n; cin >> n;
    string s; cin >> s;

    MOD = gen_hash(9e8, 1e9);
    b = gen_hash(9e2,1e3);

    ll res = 1;
    vector<ll> hashes(1 << n);
    for(int i = (1 << n) - 1; i > 0; i--) {
        
        if(i >= (1 << (n - 1))) { //leaf
            hashes[i] = s[i-1] * b % MOD;
            // cout << "i : " << i << "leaf\n";
        } else {
            // cout << "i : " << i << " not leaf\n";
            ll lo = min(hashes[i * 2], hashes[i * 2 + 1]);
            ll hi = max(hashes[i * 2], hashes[i * 2 + 1]);
            hashes[i] = (s[i-1] * b + lo * lo + hi * hi % MOD * hi) % MOD;
            if(hashes[i * 2] != hashes[i * 2 + 1]) {
                // cout << "i : " << i << "\n";
                res *= 2;
                res %= 998244353;
            }
        }
    }
    cout << res << '\n';

    // cout << "h\n" << hashes << '\n';

    return 0;
}