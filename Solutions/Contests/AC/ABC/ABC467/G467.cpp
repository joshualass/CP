#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

array<ll,2> operator+(const array<ll,2> &lhs, const array<ll,2> &rhs) {
    return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
}
array<ll,2> operator-(const array<ll,2> &lhs, const array<ll,2> &rhs) {
    return {lhs[0] - rhs[0], lhs[1] - rhs[1]};
}

struct seg {

    struct FT {
        vector<array<ll,2>> s;
        FT(int n = 0) : s(n) {}
        void init(int n) {
            s.resize(n);
        }
        void update(int pos, array<ll,2> dif) { // a[pos] += dif
            for (; pos < sz(s); pos |= pos + 1) s[pos] = s[pos] + dif;
        }
        array<ll,2> query(int pos) { // sum of values in [0, pos)
            array<ll,2> res = {};
            for (; pos > 0; pos &= pos - 1) res = res + s[pos-1];
            return res;
        }
    };

    vector<array<ll,2>> o;
    vector<pair<array<ll,2>, array<ll,2>>> c;
    FT ft;
    int p = 0, n, len;
    ll sum = 0;

    seg() {}
    void init(vector<vector<array<ll,2>>> &updates, int l, int r) {
        for(int i = l; i < r; i++) {
            for(auto x : updates[i]) {
                o.push_back(x);
            }
        }
        sort(o.begin(), o.end());
        n = sz(o), len = r - l;
        ft.init(n);
        for(int i = l; i < r; i++) {
            ft.update(lower_bound(o.begin(), o.end(), updates[i][0]) - o.begin(), {updates[i][0][0], 1});
            sum += updates[i][0][0];
            for(int j = 1; j < sz(updates[i]); j++) {
                c.push_back({updates[i][j-1], updates[i][j]});
            }
        }
        sort(c.begin(), c.end(), [&](const auto &lhs, const auto &rhs) -> bool {
            return lhs.second[1] < rhs.second[1];
        });
        // cout << "l : " << l << " r : " << r << " c : " << c << endl;
    }

    void update() {
        assert(p < sz(c));
        auto sub = c[p].first, add = c[p].second;
        ft.update(lower_bound(o.begin(), o.end(), sub) - o.begin(), {-sub[0], -1});
        ft.update(lower_bound(o.begin(), o.end(), add) - o.begin(), {add[0], 1});
        sum -= sub[0];
        sum += add[0];
        p++;
    }

    array<ll,2> query(ll threshold) {
        return array<ll,2>{sum, len} - ft.query(lower_bound(o.begin(), o.end(), array<ll,2>{threshold, 0}) - o.begin());
    }
};

struct Tree {
    typedef array<ll,2> T;
    static constexpr T base = {};
    vector<seg> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(vector<vector<array<ll,2>>> &a) {
        this->n = sz(a); //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        assert(n == sz(a));
        build(1, a, 0, size);
    }
    void build(int node, vector<vector<array<ll,2>>> &a, int l, int r) {
        // cout << "node : " << node << " l : " << l << " r : " << r << endl;
        v[node].init(a, l, min(r, n));
        if(l + 1 == r) return;
        int m = (l + r) / 2;
        build(node * 2, a, l, m);
        build(node * 2 + 1, a, m, r);
    }
    void update(int pos) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        while(curr) {
            // cout << "upd idx : " << curr << endl;
            v[curr].update();
            curr /= 2;
        }
    }
    // T at(int idx) {
    //     assert(idx >= 0 && idx < n);
    //     return v[idx + size];
    // }
    T query(int l, int r, ll t) {//queries in range [l,r)
        return _query(1,0,size,l,r,t);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr, ll t) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) {
            // return v[idx];
            // cout << "query idx : " << idx << endl;
            return v[idx].query(t);
        }
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr, t),
            _query(idx * 2 + 1, mid, currr, targetl, targetr, t)
        );
    }
};

template<typename T>
void eraseduplicates(vector<T> &a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<vector<array<ll,2>>> a(n);
    vector<ll> b;
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        a[i].push_back({x, i});
        b.push_back(x);
    }
    

    vector<array<ll,5>> upds(q);

    for(int qq = 0; qq < q; qq++) {
        for(auto &x : upds[qq]) cin >> x;
        upds[qq][0]--;
        upds[qq][2]--;
        a[upds[qq][0]].push_back({upds[qq][1], n + qq});
        b.push_back(upds[qq][1]);
    }

    eraseduplicates(b);

    Tree tree(a);

    for(int qq = 0; qq < q; qq++) {
        auto [c, x, l, r, k] = upds[qq];
        // cout << "qq : " << qq << " c : " << c << " x : " << x << " l : " << l << " r : " << r << " k : " << k << endl;
        tree.update(c);
        // cout << "update complete" << endl;
        int lo = 0, hi = sz(b);
        while(lo != hi) {
            int m = (lo + hi) / 2;
            // cout << "m : " << m << endl;
            auto res = tree.query(l, r, b[m]);
            // cout << "res : " << res << endl;
            if(res[0] >= k) {
                lo = m + 1;
            } else {
                hi = m;
            }
        }
        // cout << "lo : " << lo << endl;
        if(lo == 0) {
            cout << "-1\n";
        } else {
            auto res = tree.query(l, r, b[lo - 1]);
            ll extra = res[0] - k;
            res[1] -= extra / (b[lo - 1]);
            cout << res[1] << '\n';
        }
    }

    return 0;
}
