#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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
    Tree<ll> tree(n);
    map<ll,ll> m; 
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        tree.update(i, num);
    }

    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        if(num > 1) {
            m[i] = num;
        }
    }

    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int type; cin >> type;
        if(type == 1) {
            ll i, x; cin >> i >> x;
            tree.update(i - 1, x);
        } else if(type == 2) {
            ll i, x; cin >> i >> x;
            m.erase(i - 1);
            if(x > 1) {
                m[i - 1] = x;
            }
        } else {
            ll l, r; cin >> l >> r;
            l--;
            ll res = 0;
            while(l != r) {
                map<ll,ll>::iterator lb = m.lower_bound(l);

                if(lb != m.end() && lb->first < r) {
                    res += tree.query(l, lb->first);
                    res = max(res + tree.at(lb->first), res * lb->second);
                    l = lb->first + 1;
                } else {
                    res += tree.query(l, r);
                    l = r;
                }

            }

            cout << res << '\n';

        }
    }

    return 0;
}