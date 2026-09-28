#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int d = 60;
struct B {

    array<ll,d> basis = {};
    B(): basis({}) {}

    B& operator=(const B& other) {
        this->basis = other.basis;
        return *this;
    }

    B operator+(const B& other) const {
        B res;
        res.basis = this->basis;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(other.basis[bit]) res.insert(other.basis[bit]);
        }
        return res;
    }

    bool insert(ll x) { //return 0/1 if the insert failed. 
        // cout << "insert x : " << x << '\n';
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    basis[bit] = x;
                    return 1;
                }
            }
        }
        return 0;
    }

    bool find(ll x) { //return 0/1 if element is in the basis, does not insert. 
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    return 0;
                }
            }
        }
        return 1;
    }

    ll query() {
        ll res = 0;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(((res >> bit) & 1) == 0) res ^= basis[bit];
        }
        return res;
    }
};

void solve() {
    int n; cin >> n;

    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    string s; cin >> s;
    int res = 0;
    B b;
    for(int i = s.size() - 1; i >= 0; i--) {
        if(s[i] == '0') b.insert(a[i]);
        else if(b.find(a[i]) == 0) res = 1;
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}