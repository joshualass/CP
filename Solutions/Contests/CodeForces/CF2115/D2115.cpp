#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
intuition - for each msb, we see who gets to decide / or who has the last say with each bit. 

thoughts
like most nim problems, we should try working from the back

observe - we kind of maintain a basis of possible elements that can be formed by each suffix. 
we can see that any element that is already in the basis will converge to the same value. 
from this, we can see that adding elements to this basis will have no affect to the converging value. 

then, we should only consider the operations that contribute to the basis. 

we see who gets say for each bit by looking at the xor basis, at each msb, they will independently act greedily

xor basis intution ++
*/

const int d = 60;
struct B {

    array<ll,d> basis = {};
    array<int,d> type = {};
    B(): basis({}) {}

    // B operator+(const B& other) const {
    //     B res;
    //     res.basis = this->basis;
    //     for(int bit = d - 1; bit >= 0; bit--) {
    //         if(other.basis[bit]) res.insert(other.basis[bit]);
    //     }
    //     return res;
    // }

    bool insert(ll x, int t) { //return 0/1 if the insert failed. 
        // cout << "insert x : " << x << '\n';
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    basis[bit] = x;
                    type[bit] = t;
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

    ll query(ll res) {
        for(int bit = d - 1; bit >= 0; bit--) {
            if(type[bit] != ((res >> bit) & 1)) res ^= basis[bit];
        }
        return res;
    }
};

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;
    string s; cin >> s;

    ll x = 0;
    for(int i = 0; i < n; i++) {
        x ^= b[i];
        a[i] ^= b[i];
    }

    B basis;
    for(int i = n - 1; i >= 0; i--) {
        basis.insert(a[i], s[i] - '0');
    }

    cout << basis.query(x) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}