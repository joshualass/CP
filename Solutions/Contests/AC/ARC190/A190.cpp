#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    // for(auto &x : v) os << x << " ";
    // return os;
    for(int i = 1; v.size() >= 1 << i; i++) {
        for(int j = 1 << (i - 1); 1 << i > j; j++) {
            // os << "i : " << i << " j : " << j << ' ';
            os << v[j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = {(int) 1e9, -1};
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        if(a[0] < b[0]) return a;
        return b;
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
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    bool isLeaf(int idx) {
        return idx >= size;
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
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<array<int,2>> a(m);
    for(auto &x : a) {
        cin >> x[0] >> x[1];
        x[0]--; x[1]--;
    }

    Tree<array<int,2>> tree(n);
    int lo = -1, hi = -1;
    for(int i = 0; i < m; i++) {
        if(tree.at(a[i][0])[0] > a[i][1]) {
            tree.update(a[i][0], {a[i][1], i});
            // cout << "upd i : " << i << '\n';
        }
        if(a[i][0] == 0 && a[i][1] == n - 1) {
            cout << "1\n";
            for(int j = 0; j < m; j++) {
                cout << (i == j) << " \n"[j == m - 1];
            }
            return 0;
        }
        if(a[i][0] == 0) {
            if(lo == -1 || a[i][1] > a[lo][1]) lo = i;
        }
        if(a[i][1] == n - 1) {
            if(hi == -1 || a[i][0] < a[hi][0]) hi = i;
        }
    }

    // cout << "tree\n" << tree.v << '\n';

    if(hi != -1 && lo != -1 && a[hi][0] - a[lo][1] <= 1) {
        cout << "2\n";
        for(int i = 0; i < m; i++) {
            cout << (i == hi || i == lo) << " \n"[i == m - 1];
        }
        return 0;
    }

    for(int i = 0; i < m; i++) {
        int l = a[i][0], r = a[i][1];
        if(tree.query(l, r + 1)[1] != i && tree.query(l, r + 1)[0] <= r) {
            // cout << "first\n";
            cout << "2\n";
            auto [_, j] = tree.query(l, r + 1);
            for(int k = 0; k < m; k++) {
                int o = 0;
                if(k == i) o = 1;
                if(k == j) o = 2;
                cout << o << " \n"[k == m - 1];
            }
            return 0;
        }
        if(tree.query(l + 1, r + 1)[0] <= r) {
            // cout << "second\n";
            cout << "2\n";
            auto [_, j] = tree.query(l + 1, r + 1);
            for(int k = 0; k < m; k++) {
                int o = 0;
                if(k == i) o = 1;
                if(k == j) o = 2;
                cout << o << " \n"[k == m - 1];
            }
            return 0;
        }
        if(tree.query(r + 1, n)[1] != -1) {
            // cout << "third\n";
            cout << "2\n";
            auto [_, j] = tree.query(r + 1, n);
            for(int k = 0; k < m; k++) {
                int o = 0;
                if(k == i) o = 2;
                if(k == j) o = 2;
                cout << o << " \n"[k == m - 1];
            }
            return 0;
        }
    }

    if(m < 3) {
        cout << "-1\n";
        return 0;
    }

    for(int i = 0; i < 8; i++) {
        vector<int> b(n);
        for(int j = 0; j < 3; j++) {
            if((i >> j) & 1) {
                for(int k = a[j][0]; k <= a[j][1]; k++) {
                    b[k] = 1;
                }
            } else {
                for(int k = 0; k < a[j][0]; k++) {
                    b[k] = 1;
                }
                for(int k = a[j][1] + 1; k < n; k++) {
                    b[k] = 1;
                }
            }
        }
        if(count(b.begin(), b.end(), 1) == n) {
            cout << "3\n";
            for(int j = 0; j < 3; j++) {
                if((i >> j) & 1) {
                    cout << 1 << " \n"[j == m - 1];
                } else {
                    cout << 2 << " \n"[j == m - 1];
                }
            }
            for(int j = 3; j < m; j++) {
                cout << 0 << " \n"[j == m - 1];
            }
            return 0;
        }
    }

    assert(0);

    return 0;
}