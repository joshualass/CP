#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int d = 30;
struct B {

    int sz = 0;
    array<int,d> basis = {};
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

    bool insert(int x) { //returns true if insert was successful
        // cout << "insert x : " << x << '\n';
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    sz++;
                    basis[bit] = x;
                    return 1;
                }
            }
        }
        return 0;
    }

    bool find(int x) { //return 0/1 if element is in the basis, does not insert. 
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

    int query() {
        int res = 0;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(((res >> bit) & 1) == 0) res ^= basis[bit];
        }
        return res;
    }

    int order(int x) { //finds the order that x has in the basis. 
        //check that x is in this basis
        assert(find(x));
        int res = 0, idx = sz - 1;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(basis[bit]) {
                if((x >> bit) & 1) {
                    res += 1 << idx;
                }
                idx--;
            }
        }
        return res;
    }

    int get(int order) { //given order, find the value in this basis. 
        assert(order < (1 << sz));
        int res = 0, idx = sz - 1;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(basis[bit]) {
                if(((order >> idx) & 1) != ((res >> bit) & 1)) {
                    res ^= basis[bit];
                }
                idx--;
            }
        }
        return res;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    ll res = 0;
    for(int i = 0; i < n; i++) {
        int r = n;
        B basis;
        int zc = 0;
        for(int j = i; j < n; j++) {
            if(a[j]) {
                if(basis.insert(a[j]) == 0) {
                    r = j;
                    break;
                }
            } else {
                zc++;
                if(zc == 2) {
                    r = j;
                    break;
                }
            }
        }
        res += n - r;
    }

    cout << res << '\n';

    return 0;
}
