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
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
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

int c = 0;

ll get_inv(vector<int> p, int n) {
    c++;
    Tree<int> tree(n);
    ll res = 0;
    for(int i = 0; i < p.size(); i++) {
        res += tree.query(p[i] + 1, n);
        tree.update(p[i], 1);
    }
    // cout << "p : " << p << '\n';
    // cout << "res : " << res << '\n';
    return res;
}

void solve() {

    int n, k; cin >> n >> k;
    c = 0;

    vector<int> a(n);
    for(int &x : a) {
        cin >> x;   
        x--;
    }

    Tree<int> tree(n);

    auto get_inv = [&](int l, int r) -> ll {
        tree.v.assign(tree.size * 2, 0);
        ll cnt = 0;
        for(int i = l; i < r; i++) {
            cnt += tree.query(a[i] + 1, n);
            tree.update(a[i], 1);
        }
        return cnt;
    };

    if(get_inv(0, n) % k != 0) {
        cout << n << '\n';
        return;
    }
    
    int res = -1;
    for(int r = 1; r <= n; r++) {
        if(get_inv(0,r) % k != 0) res = r;
    }
    for(int l = 0; l < n; l++) if(get_inv(l, n) % k != 0) res = max(res, n - l);

    while(a.size() && a.back() + 1 == a.size()) a.pop_back();
    reverse(a.begin(), a.end());
    int t = 0;
    while(a.size() && a.back() == t++) a.pop_back();
    reverse(a.begin(), a.end());

    // for(int l = 0; l < n; l++) {
    //     for(int r = l + 1; r <= n; r++) {
    //         if(get_inv(l, r) % k != 0) res = max(res, r - l);
    //     }
    // }


    for(int len = a.size(); len >= max(res, 1); len--) {
        for(int l = 0; l + len <= a.size(); l++) {
            if(get_inv(l, l + len) % k != 0) {
                cout << len << '\n';
                return;
            }
        }
    }

    cout << res << '\n';

    // cout << res << '\n';




    // cout << "-1\n";

    // cout << "c : " << c << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}