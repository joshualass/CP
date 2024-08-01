#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
We see that permutation of length k, there are some internal inversions that we must calculate. Other than that, the order of q does not affect inversions between other blocks of length k.
To calculate inversions from blocks of length k on each other. We have to count the number of values in the permutation earlier as well as how many powers of 2 they differ by. Each value
is uniquely determined so we can look see how many powers of 2 it takes for an element to overpower another element and then calculate the inversions by looking at differences in powers of 2. 
*/

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

ll calcinversions1(vector<ll> &q) {
    ll res = 0;
    Tree<int> tree(q.size());
    for(int i = 0; i < q.size(); i++) {
        res += tree.query(q[i], q.size());
        tree.update(q[i], 1);
    }
    return res % MOD;
}

ll calcinversions2(ll diff, ll k) {
    ll res = 0;
    ll curr = 0;
    for(int i = 0; i < k; i++) {
        while(curr != k && i - diff > curr) {
            curr++;
        }
        res += curr;
    }
    return res;
}

void solve() {

    int n, k; cin >> n >> k;

    ll maxdiff = __lg(2 * n - 1) + 1;

    vector<ll> p(n), q(k);
    for(ll &x : p) cin >> x;
    for(ll &x : q) cin >> x;
    
    vector<ll> unders(maxdiff); //before is less
    vector<ll> overs(maxdiff); //before is larger

    for(int i = 0; i < maxdiff; i++) {
        unders[i] = calcinversions2(i, k);
        overs[i] = calcinversions2(-1 - i, k);
    }

    // cout << "unders : " << unders << '\n';
    // cout << "overs : " << overs << '\n';

    ll res = 0;

    Tree<int> tree(n * 2);

    for(int i = 0; i < n; i++) {
        ll currhi = p[i];
        ll currlo = p[i];
        for(int j = 0; j < maxdiff; j++) {

            // cout << "i : " << i << " j : " << j << " under part : " << tree.query((currlo + 1) / 2, currlo) << '\n';
            // cout << "i : " << i << " j : " << j << " over part : " << tree.query(currhi, min(currhi * 2, 2LL * n)) << '\n';

            res += tree.query((currlo + 1) / 2, currlo) * unders[j];
            res += tree.query(currhi, min(currhi * 2, 2LL * n)) * overs[j];

            currlo = (currlo + 1) / 2;
            currhi = min(currhi * 2, 2LL * n);

        }
        res %= MOD;
        tree.update(p[i],1);

    }

    // cout << "inversion1 : " << calcinversions1(q) * n << '\n';
    // cout << "res : " << res << '\n';

    cout << (calcinversions1(q) * n + res) % MOD << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}