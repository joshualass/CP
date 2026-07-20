#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
observe that we don't have to handle things online. => no more annoying treap impl
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

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

struct Tree {
    typedef array<ll,2> T;
    static constexpr T base = {};
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return {a[0] + b[0], max(a[1], a[0] + b[1])};
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    
    vector<array<int,4>> c; // {a, b, time, prev time to erase}
    for(int i = 0; i < n; i++) {
        c.push_back({a[i], b[i], i, -1});
    }

    vector<int> cur(n);
    iota(cur.begin(), cur.end(), 0);

    for(int qq = 0; qq < q; qq++) {
        int t, i, x; cin >> t >> i >> x;
        i--;
        if(t == 1) {
            a[i] = x;
        } else {
            b[i] = x;
        }
        c.push_back({a[i], b[i], n + qq, cur[i]});
        cur[i] = n + qq;
    }

    sort(c.rbegin(), c.rend(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[1] < rhs[1];
    }); //largest to smallest b
    vector<int> iid(n + q); //where in the array is the i'th op. 
    Tree tree(n + q);

    for(int i = 0; i < n + q; i++) {
        iid[c[i][2]] = i;
        if(c[i][2] < n) {
            tree.update(i, {c[i][0], c[i][0] + c[i][1]});
        }
    }

    auto pt = [&]() -> void {
        for(int i = 0; i < n + q; i++) {
            cout << tree.at(i) << " ";
        }
        cout << endl;
        cout << "query : " << tree.query(0, n + q) << endl;
    };

    // cout << "c : " << c << endl;
    // cout << "iid : " << iid << endl;

    // cout << "init tree" << endl;
    // pt();

    for(int qq = 0; qq < q; qq++) {
        int op = iid[n + qq];
        auto info = c[op];

        // cout << "qq : " << qq << " op : " << op << " info : " << info << endl;

        tree.update(iid[info[3]], {0, 0}); //clear out old
        tree.update(op, {info[0], info[0] + info[1]});

        // pt();

        cout << tree.query(0, n + q)[1] << '\n';
    }


    return 0;
}
