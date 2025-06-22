#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    ll res = 0;
    auto work = [&](char t, int os) -> void {

        int rc = 0;
        int tc = 0;
        Tree<ll> cnts(n * 2 + 1), sums(n * 2 + 1);

        for(int i = 0; i < n; i++) {
            cnts.update(rc + n, 1);
            sums.update(rc + n, -tc);

            rc += (s[i] == t ? 1 : -1);
            tc += s[i] == t;

            ll sum = sums.query(0, n + rc + os + 1);
            ll cnt = cnts.query(0, n + rc + os + 1);

            ll add = cnt * tc + sum;
            // cout << "t : " << t << " os : " << os << " i : " << i << " sum : " << sum << " cnt : " << cnt << " tc : " << tc << " add : " << add << '\n';
            res += add;

        }

    };

    work('0', 0);
    work('1', -1);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}