#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] += val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<array<int,2>>> adj(n);

    for(int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    vector<int> tin(n), tout(n), p(n - 1);
    int time = 0;

    auto dfs = [&](auto self, int i, int par) -> void {

        tin[i] = time++;

        for(auto [c, e] : adj[i]) {
            if(c != par) {
                self(self, c, i);
            } else {
                p[e] = i;
            }
        }

        tout[i] = time;

    };

    dfs(dfs, 0, -1);

    // cout << "tin : " << tin << '\n';
    // cout << "tout : " << tout << '\n';
    // cout << "p : " << p << '\n';

    Tree<int> tree(n);

    for(int i = 0; i < n; i++) tree.update(i, 1);

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int t; cin >> t;

        if(t == 1) {
            int x, w; cin >> x >> w;
            x--;
            tree.update(tin[x], w);
        } else {
            int y; cin >> y;
            y--;
            int idx = p[y];
            int rhs = tree.query(tin[idx], tout[idx]);
            int lhs = tree.query(0, n) - rhs;
            // cout << "y : " << y << " idx : " << idx << " lhs : " << lhs << " rhs : " << rhs << '\n';
            cout << abs(lhs - rhs) << '\n';
        }

    }


    return 0;
}
