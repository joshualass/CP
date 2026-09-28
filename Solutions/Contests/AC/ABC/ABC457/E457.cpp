#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     // for(auto &x : v) os << x << " ";
//     // return os;
//     for(int i = 1; v.size() >= 1 << i; i++) {
//         for(int j = 1 << (i - 1); 1 << i > j; j++) {
//             // os << "i : " << i << " j : " << j << ' ';
//             os << v[j] << ' ';
//         }
//         os << '\n';
//     }
//     return os;
// }

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    Tree(vector<T> a) {
        this->n = sz(a); //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        assert(n == sz(a));
        for(int i = 0; i < n; i++) {
            v[i + size] = a[i];
        }
        for(int i = size - 1; i >= 1; i--) {
            v[i] = f(v[i * 2], v[i * 2 + 1]);
        }
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

    int n, m; cin >> n >> m;
    vector<vector<int>> ls(n), rs(n);

    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        ls[l].push_back(r);
        rs[r].push_back(l);
    }

    int q; cin >> q;
    vector<array<int,2>> qs(q);
    vector<int> has2(q);
    vector<vector<array<int,2>>> zz(n);

    for(int qq = 0; qq < q; qq++) {
        int s, t; cin >> s >> t;
        s--; t--;
        qs[qq] = {s, t};
        zz[s].push_back({t, qq});
    }

    Tree<int> tree(n);
    int cnt = 0;

    for(int i = n - 1; i >= 0; i--) {
        sort(ls[i].begin(), ls[i].end());
        sort(rs[i].begin(), rs[i].end());

        for(int r : ls[i]) {
            tree.update(r, 1);
            cnt++;
        }

        // cout << "l : " << i << endl;

        for(auto [r, qid] : zz[i]) {
            // cout << "r : " << r << " qid " << qid << endl;
            // cout << "tree\n" << tree.v << endl;
            if(cnt - tree.query(r + 1, n) >= 2) {
                has2[qid] = 1;
            }
        }
    }

    // cout << "h2 : " << has2 << endl;

    for(int qq = 0; qq < q; qq++) {
        auto [l, r] = qs[qq];
        auto lit = upper_bound(ls[l].begin(), ls[l].end(), r);
        auto rit = lower_bound(rs[r].begin(), rs[r].end(), l);

        // cout << "qq : " << qq << " l : " << l << " r : " << r << endl;

        int f = 0;
        if(lit != ls[l].begin() && rit != rs[r].end()) {
            if((*--lit) + 1 >= (*rit) && (*rit) != l) {
                f = 1;
                // cout << "true 0" << endl;
                // cout << "lval : " << (*--lit) << " rval : " << (*rit) << endl;
            }
        }
        if(rit != rs[r].end() && *rit == l) {
            if(has2[qq]) {
                f = 1;
                // cout << "true 1" << endl;
            }
        }

        cout << (f ? "Yes" : "No") << '\n';
    }

    return 0;
}
