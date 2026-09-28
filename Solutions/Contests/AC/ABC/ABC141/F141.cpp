#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
we get the answer from 
x + (x oplus c) where c is the xor sum of the elements
we want to set as many bits as possible that are not set in c, thus, we form our basis over the unset bits in c, as those are the relevant ones
*/

const int d = 60;
struct B {

    vector<ll> basis;
    B(): basis(d) {}

    bool insert(ll x, ll c) { //return 0/1 if the insert failed. 
        for(int bit = d - 1; bit >= 0; bit--) {
            if(((c >> bit) & 1) == 0) {
                if((x >> bit) & 1) {
                    if(basis[bit]) {
                        x ^= basis[bit];
                    } else {
                        basis[bit] = x;
                        return 1;
                    }
                }
            }
        }
        return 0;
    }

    bool find(ll x) {
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

    ll queryLargest(ll c) {
        ll res = 0;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(((c >> bit) & 1) == 0) {
                if(((res >> bit) & 1) == 0) res ^= basis[bit];
            }
        }
        return res;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    B b;
    ll c = 0;
    vector<ll> a(n);
    for(ll &x : a) {
        cin >> x;
        c ^= x;
    }
    for(int i = 0; i < n; i++) {
        b.insert(a[i], c);
    }

    cout << b.queryLargest(c) + (c ^ b.queryLargest(c)) << '\n';

    return 0;
}
