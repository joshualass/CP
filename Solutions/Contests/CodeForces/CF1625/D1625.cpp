#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int d = 30;

int trie[10000000][2];
int p = 0;

void insert(int root, int x, int idx) {
    for(int i = d - 1; i >= 0; i--) {
        int bit = (x >> i) & 1;
        if(trie[root][bit] == 0) {
            trie[root][bit] = p++;
        }
        root = trie[root][bit];
    }
    trie[root][0] = idx;
}

array<int,2> query(int root, int x) {
    int res = 0;
    for(int i = d - 1; i >= 0; i--) {
        int bit = ((x >> i) & 1) ^ 1;
        if(trie[root][bit]) {
            res += 1 << i;
        } else {
            bit ^= 1;
        }
        root = trie[root][bit];
    }
    return {res, trie[root][0]};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<int> res;
    if(k) {
        int msb = 32 - __builtin_clz(k);
        map<int,vector<int>> m;
        for(int i = 0; i < n; i++) {
            int x = a[i];
            m[x>>msb].push_back(i);
        }
        int bm = (1 << (msb + 1)) - 1;
        for(auto [ub, b] : m) {
            int root = p++;
            vector<int> c = {b[0]};
            for(int x : b) {
                insert(root, a[x] & bm, x);
                auto [val, id] = query(root, a[x] & bm);
                if(val >= k) {
                    c = {id, x};
                }
            }
            for(int x : c) res.push_back(x);
        }
    } else {
        for(int i = 0; i < n; i++) res.push_back(i);
    }

    if(res.size() <= 1) {
        cout << "-1\n";
    } else {
        cout << res.size() << '\n';
        for(int i = 0; i < res.size(); i++) cout << res[i] + 1 << " \n"[i == res.size() - 1];
    }

    return 0;
}
