#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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
            if(curr & 1) { //non
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

void solve() {
    ll n, l; cin >> n >> l;
    vector<vector<ll>> v(n,vector<ll>(3));
    for(int i = 0; i < n; i++) {
        cin >> v[i][0] >> v[i][1];
        v[i][2] = i;
    }
    sort(v.begin(), v.end());
    map<int,int> m;
    for(int i = 0; i < n; i++) {
        m[v[i][2]] = i;
    }
    Tree<ll> treeM(n);
    Tree<int> treeC(n);

    int ans = 0;
    sort(v.begin(),v.end(), [](vector<ll> &lhs, vector<ll> &rhs) -> bool {
        return lhs[1] < rhs[1];
    });
    for(int i = 0; i < n; i++) {
        treeM.v.assign(treeM.size * 2, 0);
        treeC.v.assign(treeC.size * 2, 0);
        for(int j = i; j < n; j++) {
            ll left = l - (v[j][1] - v[i][1]);
            // cout << "left ? : " << left << '\n';
            treeM.update(m[v[j][2]],v[j][0]);
            treeC.update(m[v[j][2]],1);
            int lo = 0, hi = n;
            while(lo != hi) {
                int m = (lo + hi + 1) / 2;
                if(left - treeM.query(0,m) >= 0) {
                    lo = m;
                } else {
                    hi = m - 1;
                }
            }
            // cout << "i : " << i << " j : " << j << " val : " << treeC.query(0,lo) << '\n';
            // if(treeC.query(0,lo) == 3) {
            // }
            ans = max(ans, treeC.query(0,lo));
        }
    }
    cout << ans << '\n';
    // for(int hi = 1; hi <= n; hi++) {
    //     ll left = l - v[hi-1].second + v[0].second;
    //     sort(v.begin(),v.begin()+hi);
    //     int cnt = 0;
    //     for(int j = 0; j < hi; j++) {
    //         if(left - v[j].first >= 0) {
    //             left -= v[j].first;
    //             cnt++;
    //         } else {
    //             break;
    //         }
    //     }
    //     ans = max(ans,cnt);
    // }
    // cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}