#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    buildsh();

    int n, k; cin >> n >> k;

    vector<string> a(n);
    for(int i = 0; i < k; i++) {
        string s; cin >> s;
        for(int j = 0; j < n; j++) {
            a[j].push_back(s[j]);
        }
    }

    map<ll, set<int>> mh;
    for(int i = 0; i < n; i++) {
        stringhash sh(a[i].substr(1));
        mh[sh.get_hash(0, k - 1)].insert(i);
    }

    vector<int> res(n);
    int ok = 1;

    for(int i = 0; i < n; i++) {
        stringhash sh(a[i].substr(0, k - 1));
        ll hs = sh.get_hash(0, k - 1);
        if(mh[hs].size()) {
            int to = *mh[hs].begin();
            mh[hs].erase(mh[hs].begin());
            res[i] = to;
        } else {
            ok = 0;
        }
    }

    if(ok) {
        cout << "YES\n";
        for(int i = 0; i < n; i++) {
            cout << res[i] + 1 << " \n"[i == n - 1];
        }
    } else {
        cout << "NO\n";
    }

    return 0;
}

/*

5 rows x columns

1
1
0
0
.


*/