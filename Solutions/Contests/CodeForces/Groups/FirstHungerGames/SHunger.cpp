#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool insertBasis(vector<int> &basis, int x) {
    for(int bit = basis.size() - 1; bit >= 0; bit--) {
        if(x & (1 << bit)) {
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

int queryBasis(vector<int> &basis, int x, int cnt) {
    x--;
    int curr = 0;
    for(int bit = basis.size() - 1; bit >= 0; bit--) {
        if(basis[bit]) {
            cnt--;
            bool goup1 = x & (1 << cnt);
            bool goup2 = curr & (1 << bit);
            if(goup1 ^ goup2) {
                curr ^= basis[bit];
            }
        }
    }
    return curr;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<int> basis(30);

    int cnt = 0;

    for(int i = 0; i < n; i++) {
        int type; cin >> type;
        if(type == 1) {
            int k; cin >> k;
            cnt += insertBasis(basis, k);
        } else {
            int k; cin >> k;
            cout << queryBasis(basis,k, cnt) << '\n';
        }
    }

    return 0;
}