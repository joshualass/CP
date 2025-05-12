#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//supports 2 operations
// 1 - only able to handle addition and subtraction operations ...
// 2 - query for a single element
template<typename T>
struct InvertedTree {
    static constexpr T base = 0;
    T f(T a, T b) {
        return a + b; //update this function for different types of queries, currently sum
    }
    vector<T> s; int n;
    InvertedTree(int n = 0, T def = base) : s(n*2,def), n(n) {}
    void set(int pos, T val) {
        s[pos + n] = val;
    }
    void update(int l, int r, T u) { //increases values in [l,r) by u
        for(l += n, r += n; l < r; l /= 2, r /= 2) {
            if(l & 1) {
                s[l] = f(s[l],u);
                l++;
            }
            if(r & 1) {
                r--;
                s[r] = f(s[r],u);
            }
        }
    }
    T query(int pos) { //queries the value of element at pos
        T ans = s[pos += n];
        while(pos /= 2) {
            ans = f(ans,s[pos]);
        }
        return ans;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n * 2);
    vector<int> p(n * 2);
    for(int i = 0; i < m; i++) {   
        int u, v; cin >> u >> v;
        u--; v--;
        a[v] = u;
        p[u] = 1;
        p[v] = 1;
    }

    for(int i = 1; i < n * 2; i++) p[i] += p[i-1];

    vector<vector<array<int,2>>> q(n * 2);
    int Q; cin >> Q;
    for(int i = 0; i < Q; i++) {
        int c, d; cin >> c >> d;
        c--; d--;
        q[d].push_back({c, i});
    }

    InvertedTree<int> tree(n * 2);

    vector<int> res(Q);
    for(int i = 0; i < n * 2; i++) {
        if(i & 1) {
            if(a[i]) {
                tree.update(0, a[i], 1);
            }
        } else {
            for(auto [l, id] : q[i]) {
                // cout << "i : " << i << " l : " << l << " query : " << tree.query(l) << '\n';
                res[id] = p[i] - p[l] - 2 * tree.query(l);
            }
        }
    }

    for(int x : res) cout << x << '\n';

    return 0;
}
