#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool find(vector<int> &basis, int x) {
    for(int bit = 19; bit >= 0; bit--) {
        if(x & (1 << bit)) {
            if(basis[bit] == -1) {
                return 0;
            } else {
                x ^= basis[bit];
            }
        }
    }
    return 1;
}

//maintain a basis with distinct f(v)
bool insert(vector<int> &basis, int x) {
    for(int bit = 19; bit >= 0; bit--) {
        if(x & (1 << bit)) {
            if(basis[bit] == -1) {
                basis[bit] = x;
                return 1;
            } else {
                x ^= basis[bit];
            }
        }
    }
    return 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    vector<int> a(n);

    for(int &x : a) cin >> x;

    vector<vector<array<int,2>>> queries(n);

    for(int i = 0; i < q; i++) {
        int l, x; cin >> l >> x;
        queries[l - 1].push_back({x, i});
    }

    vector<int> res(q);

    vector<int> basis(20, -1);
    ll mult = 1;

    for(int i = 0; i < n; i++) {
        if(!insert(basis, a[i])) {
            mult = (mult * 2) % MOD;
        }
        for(array<int,2> query : queries[i]) {
            if(find(basis, query[0])) {
                res[query[1]] = mult;
            }
        }
    }

    for(int i = 0; i < q; i++) {
        cout << res[i] << '\n';
    }

    return 0;
}