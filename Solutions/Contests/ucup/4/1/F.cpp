#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

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

template<typename T>
struct Tree {
    static constexpr T base = {-inf, -1};
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a, b);
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

template<typename T>
void eraseduplicates(vector<T> &a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> ip(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ip[x] = i;
    }

    Tree<array<int,2>> L(m), R(m);

    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        L.update(i, {l, i});
        R.update(i, {-r, i});
    }

    int comps = m;
    ll res = 0;

    auto merge = [&](int i, int j, int cost) -> void {
        // cout << "i : " << i << " j : " << j << " cost : " << cost << endl;
        int maxl = max(L.at(i)[0], L.at(j)[0]);
        int minr = max(R.at(i)[0], R.at(j)[0]);

        L.update(i, {maxl, i});
        L.update(j, {-inf, -1});

        R.update(i, {minr, i});
        R.update(j, {-inf, -1});
        comps--;
        res += cost;
    };

    for(int i = 0; i < n; i++) {
        int z = ip[i];
        vector<int> pool;
        vector<array<int,2>> fix;

        // cout << "i : " << i << endl;

        while(1) {
            auto first = L.query(0, m);
            if(first[1] != -1 && first[0] > z) {
                pool.push_back(first[1]);
                fix.push_back(first);
                L.update(first[1], {-inf,-1});
                // cout << "add to pool idx L : " << first[1] << endl;
            } else {
                break;
            }
        }
        for(auto f : fix) L.update(f[1], f);
        fix.clear();
        while(1) {
            auto first = R.query(0, m);
            // cout << "first : " << first << endl;
            if(first[1] != -1 && -first[0] < z) {
                pool.push_back(first[1]);
                fix.push_back(first);
                R.update(first[1], {-inf, -1});
                // cout << "add to pool idx R : " << first[1] << endl;
            } else {
                break;
            }
        }
        
        for(auto f : fix) R.update(f[1], f);

        eraseduplicates(pool);

        for(int j = 1; j < sz(pool); j++) {
            merge(pool[0], pool[j], i);
        }
    }

    //handle ranges that include everything
    res += (comps - 1) * n;

    cout << res << '\n';

    return 0;
}
