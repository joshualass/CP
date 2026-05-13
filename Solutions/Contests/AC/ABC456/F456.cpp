#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ll inf = 1e18;

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
    static constexpr T base = {inf, inf, inf, 0};
    T lbase = {inf, inf, 0, 0}, rbase = {inf, 0, inf, 0};
    vector<T> v;
    int n, size;
    T f(T l, T r) { //change this when doing maximum vs minimum etc.
        array<ll,4> res = {inf, inf, inf, inf};

        for(int i = 0; i < 2; i++) {
            for(int j = 0; i + j < 2; j++) {
                res[0] = min(res[0], l[i * 2] + r[j]);
            }
        }

        for(int i = 0; i < 2; i++) {
            for(int j = 0; i + j < 2; j++) {
                res[1] = min(res[1], l[i * 2 + 1] + r[j]);
            }
        }

        for(int i = 0; i < 2; i++) {
            for(int j = 0; i + j < 2; j++) {
                res[2] = min(res[2], l[i * 2] + r[j + 2]);
            }
        }

        for(int i = 0; i < 2; i++) {
            for(int j = 0; i + j < 2; j++) {
                res[3] = min(res[3], l[i * 2 + 1] + r[j + 2]);
            }
        }

        return res;
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
        if(currr <= targetl || currl >= targetr) {
            if(currr <= targetl) {
                return lbase;
            } else {
                return rbase;
            }
        }
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

void solve() {
    
    int n, k; cin >> n >> k;
    vector<array<ll,4>> a;

    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        a.push_back({x, x, x, 0LL});
    }

    Tree<array<ll,4>> tree(a);
    ll res = inf;

    // cout << "tree : " << tree.v << endl;

    for(int i = 0; i < 2; i++) {
        for(int l = 0; l + i + k <= n; l++) {
            res = min(res, tree.query(l, l + i + k)[0]);
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}