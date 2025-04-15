#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
101

101 + 101 
1010

1010 + 1010
10100

10100 ^ 101
10001

10001 + 101
10110

10001 ^ 10110
111

111 ^ 101
10

111 + 10
1001

1010 ^ 1001
11

10 ^ 11
1

*/

const int d = 60;
struct B {

    vector<ll> basis;
    B(): basis(d) {}

    bool insert(ll x, vector<pair<array<ll,2>, char>> &a, set<ll> &s) { //return 0/1 if the insert failed. 
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    a.push_back({array<ll,2>{x, basis[bit]}, '^'});
                    x ^= basis[bit];
                    s.insert(x);
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
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll x; cin >> x;
    set<ll> s;
    B b;
    vector<pair<array<ll,2>, char>> a;

    auto add = [&](ll num) -> void {
        s.insert(num);
        b.insert(num, a, s);
    };

    add(x);

    while(s.count(1) == 0) {

        array<ll,2> c = {-1,-1};
        for(ll x : s) {
            for(ll y : s) {
                if(b.find(x + y) == 0 && x + y <= 1e18) {
                    c = {x, y};
                    goto done;
                }
            }
        }

    done:

        if(c[0] == -1) {
            cout << "no found additions to the xor basis.\n";
            cout << "basis : ";
            for(ll x : s) cout << x << ' ';
            cout << '\n';
            break;
        }

        a.push_back({{c[0], c[1]}, '+'});
        add(c[0] + c[1]);

    }

    cout << a.size() << '\n';
    for(auto op : a) {
        cout << op.first[0] << " " << op.second << " " << op.first[1] << '\n';
    }

    return 0;
}
