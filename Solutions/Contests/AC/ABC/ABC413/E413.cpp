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
    static constexpr T base = {INT_MAX, -1};
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a[0] < b[0] ? a : b;
    }
    Tree(int n, T def = base) {
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
    
    int n; cin >> n;
    vector<int> p(1 << n);  
    Tree<array<int,2>> tree(1 << n);

    for(int i = 0; i < 1 << n; i++) {
        cin >> p[i];
        tree.update(i, {p[i], i});
    }

    // cout << "p : " << p << '\n';

    vector<int> res(1 << n);

    auto dfs = [&](auto self, int rl, int rr, int cl, int cr) -> void {
        // cout << "rl : " << rl << " rr : " << rr << " cl : " << cl << " cr : " << cr << '\n';
        if(cl + 1 == cr) {
            res[rl] = p[cl];
            return;
        }
        int midr = (rl + rr) / 2;
        int midc = (cl + cr) / 2;
        // cout << "query : " << tree.query(cl, cr)[1] << '\n';
        if(tree.query(cl, cr)[1] < midc) {
            self(self, rl, midr, cl, midc);
            self(self, midr, rr, midc, cr);
        } else {
            self(self, rl, midr, midc, cr);
            self(self, midr, rr, cl, midc);
        }
    };

    dfs(dfs, 0, 1 << n, 0, 1 << n);

    for(int i = 0; i < 1 << n; i++) {
        cout << res[i] << " \n"[(i + 1) == 1 << n];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// void solve() {
    
//     int n; cin >> n;
//     vector<int> p(1 << n);
//     for(int &x : p) cin >> x;

//     for(int l = 0; l < 1 << n; l++) {
//         int lo = p[l], lo_a = -1, lo_b = -1;
//         for(int a = l, b = 0; (a + 1) << b <= 1 << n && __builtin_ctz(l) >= b; a /= 2, b++) {
//             if(p[((a + 1) << b) - 1] < lo) {
//                 lo = p[((a + 1) << b) - 1];
//                 lo_a = a;
//                 lo_b = b;
//             }
//         }
//         if(lo_b != -1) {
//             reverse(p.begin() + (lo_a << lo_b), p.begin() + ((lo_a + 1) << lo_b));
//             break;
//         }
//     }

//     for(int i = 0; i < 1 << n; i++) {
//         cout << p[i] << " \n"[(i + 1) == 1 << n];
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }