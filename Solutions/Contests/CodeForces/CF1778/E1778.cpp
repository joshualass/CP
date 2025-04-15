#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*

spent time debuggint the following rte
overriding the comb function made it recursive. need a different function name

build a segment tree of the basis for each node to merge fast. use lca to figure out stuff. 

optimize logn; we dont need you, sir. 

might be the worst implementer, something dmot would say. 

took 3hr i think :(

*/

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

const int d = 30;
struct B {

    array<int,d> basis = {};
    B(): basis({}) {}

    B& operator=(const B& other) {
        this->basis = other.basis;
        return *this;
    }

    bool insert(int x) { //return 0/1 if the insert failed. 
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
};

B merge(B lhs, B rhs) {
    for(int i = d - 1; i >= 0; i--) if(rhs.basis[i]) lhs.insert(rhs.basis[i]);
    // cout << "comb return lhs : " << lhs.basis << endl;
    return lhs;
}

void solve() {

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<array<int,20>> lifts(n); //BLG
    vector<int> depths(n);
    vector<B> bases(n); //basis of node's subtree
    vector<map<int,int>> pc(n);

    auto dfs0 = [&](auto self, int i, int p, int d) -> void {

        depths[i] = d;
        lifts[i][0] = p;

        B b;
        b.insert(a[i]);

        for(int c : adj[i]) {
            if(c != p) {
                // cout << "gogo i : " << i << " c : " << c << endl;
                self(self, c, i, d + 1);
                // cout << "imma done gogo i : " << i << " c : " << c << endl;
                b = merge(b, bases[c]);
            }
        }
        bases[i] = b;
        pc[i][p] = bases[i].query();
        // cout << "i : " << i << " done computing basis : " << bases[i].basis << '\n';
    };

    dfs0(dfs0, 0, -1, 0);

    // cout << "print earlier\n";
    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " basis[i] : " << bases[i].basis << '\n';
    // }

    auto go = [&](int idx, int b) -> int {
        if(idx >= 0) return lifts[idx][b];
        return -1;
    };

    auto go_k = [&](int idx, int k) -> int {
        for(int i = 19; i >= 0; i--) {
            if((k >> i) & 1) idx = go(idx, i);
        }
        return idx;
    };

    for(int i = 1; i < 20; i++) {
        for(int j = 0; j < n; j++) {
            lifts[j][i] = go(go(j, i - 1), i - 1);
        }
    }

    auto dfs1 = [&](auto self, int i, int p, B bpar) -> void {

        adj[i].erase(remove(adj[i].begin(), adj[i].end(), p), adj[i].end());
        vector<B> pre(adj[i].size()), suf(adj[i].size());

        B pb;
        for(int j = 0; j < adj[i].size(); j++) {
            pre[j] = pb;
            pb = merge(pb, bases[adj[i][j]]);
        }

        B sb;
        for(int j = ((int) adj[i].size()) - 1; j >= 0; j--) {
            suf[j] = sb;
            sb = merge(sb, bases[adj[i][j]]);
        }

        bpar.insert(a[i]);
        for(int j = 0; j < adj[i].size(); j++) {
            B nb = merge(merge(pre[j], suf[j]), bpar);
            pc[i][adj[i][j]] = nb.query();
            self(self, adj[i][j], i, nb);
        }
    };

    B bs;

    dfs1(dfs1, 0, -1, bs);

    // cout << "print later\n";
    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " basis[i] : " << bases[i].basis << '\n';
    // }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int r, v; cin >> r >> v;
        r--; v--;

        int rd = depths[r], vd = depths[v];
        int res = -1;
        if(r == v) {
            res = bases[0].query();
        } else if(rd <= vd || v != go_k(r, rd - vd)) {
            res = pc[v][lifts[v][0]];
        } else {
            res = pc[v][go_k(r, rd - vd - 1)];
        }

        cout << res << '\n';

    }
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}