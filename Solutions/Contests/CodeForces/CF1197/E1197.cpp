#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, map<T,D> m) {
    for(auto &x: m) os << x.first << " " << x.second << " | ";
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
    static constexpr T base = {0,0}; //{volume, cnt}
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        if(a[0] == b[0]) {
            return {a[0], ((a[1] + b[1]) % MOD)};
        } else if(a[0] > b[0]) {
            return a;
        } else {
            return b;
        }
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
        v[curr] = comb(v[curr], val);
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
    
    int n; cin >> n;
    //{in, out}
    vector<array<int,2>> a(n);
    map<int,int> m;
    m[0];
    for(int i = 0; i < n; i++) {
        cin >> a[i][1] >> a[i][0];
        m[a[i][0]];
        m[a[i][1]];
    }

    int cnt = 0;
    for(auto &p : m) {
        p.second = cnt++;
    }

    sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) {
        return lhs[0] < rhs[0];
    });

    Tree<array<ll,2>> tree(m.size());
    tree.update(0, {0,1});

    ll maxin = 0;
    for(int i = 0; i < n; i++) {
        ll in = m[a[i][0]];
        ll out = m[a[i][1]];
        array<ll,2> q = tree.query(0,in + 1);
        q[0] += a[i][1] - a[i][0];
        tree.update(out, q);
        maxin = max(maxin, in);
    }

    // cout << "compression : " << m << '\n';
    // cout << "final tree : \n" << tree.v << '\n';

    ll res = 0;
    ll minempty = LLONG_MAX;
    for(auto p : m) {
        if(p.second > maxin) {
            array<ll,2> v = tree.at(p.second);
            ll es = p.first - v[0];
            // cout << "p : " << p << " es : " << es << '\n';
            if(es == minempty) {
                res += v[1];
            } else if(es < minempty) {
                minempty = es;
                res = v[1];
            }
        }
    }
    // cout << "me : " << minempty << '\n';
    cout << res << '\n';

    return 0;
}