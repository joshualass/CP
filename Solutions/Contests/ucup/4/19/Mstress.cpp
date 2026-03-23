#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
    return os;
}

const int lim = 32;

struct Tree {
    typedef vector<array<int,2>> T;
    T base = {};
    vector<T> v;
    int n, size;

    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        if(a.empty()) return b;
        if(b.empty()) return a;

        vector<array<int,2>> res;
        int ai = 0, bi = 0;
        while(ai < sz(a) || bi < sz(b)) {
            int k, v;
            if(ai < sz(a) && (bi == sz(b) || a[ai][0] > b[bi][0])) {
                k = a[ai][0], v = a[ai][1];
                ai++;
            } else {
                k = b[bi][0], v = b[bi][1];
                bi++;
            }
            int done = 0;
            while(!done) {
                if(res.empty()) {
                    res.push_back({k, v});
                    done = 1;
                } else if(res.back()[0] == k + 1 && res.back()[1] != v) {
                    res.pop_back();
                    v *= -1;
                } else if(res.back()[0] == k) {
                    if(res.back()[1] == v) {
                        res.pop_back();
                        k++;
                    } else {
                        res.pop_back();
                        done = 1;
                    }
                } else {
                    //there should be no case where it is less than at this point. 
                    res.push_back({k, v});
                    done = 1;
                }
            }
        }
        while(sz(res) > lim) res.pop_back();
        return res;
    }
    Tree(int n, T def) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
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

void solve() {
    
    // int n, q; cin >> n >> q;
    int n = 500000, q = 500000;
    Tree tree(n, {});
    auto get_map = [&](int i, int val) -> vector<array<int,2>> {
        int neg = 1;
        if(val < 0) {
            neg = -1;
            val *= -1;
        }
        vector<array<int,2>> res;
        while(val) {
            if(val & 1) {
                res.push_back({i, neg});
            }
            i++;
            val >>= 1;
        }
        reverse(res.begin(), res.end());
        return res;
    };
    for(int i = 0; i < n; i++) {
        // int x; cin >> x;
        int x = 1000000000;
        // cout << "i : " << i << " map : " << get_map(i, x) << endl;
        tree.update(i, get_map(i, x));
    }
    for(int qq = 0; qq < q; qq++) {
        // int type; cin >> type;
        int type = (qq % 2 == 0 ? 1 : 2);
        if(type == 1) {
            // int i, val; cin >> i >> val;
            // i--;
            int i = qq, val = 1000000000;
            tree.update(i, get_map(i, val));
        } else {
            // int l, r; cin >> l >> r;
            // l--;
            int l = 0, r = n;
            auto res = tree.query(l, r);
            // cout << "final res : " << res << endl;
            if(res.empty()) {
                cout << "0\n";
            } else {
                cout << res[0][1] << '\n';   
            }
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    clock_t tStart = clock();

    int casi; cin >> casi;
    while(casi-->0) solve();
    
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    return 0;
}