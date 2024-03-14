#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
//solvable without a 5th element
template<typename T>
struct Tree {
    static constexpr T base = {0,0,0,0,INT_MIN};
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        // return a + b;
        ll prefmax = max(a[0],a[3] + b[0]);
        ll suffmax = max(b[1],b[3] + a[1]);
        ll overallmax = max({a[2],b[2],a[1] + b[0]});
        ll sum = a[3] + b[3];
        ll maxval = max(a[4],b[4]);
        return {prefmax,suffmax,overallmax,sum,maxval};
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, ll val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = {max(0LL,val),max(0LL,val),max(0LL,val),val,val};
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<pair<ll,ll>>> events(n+1); //idx, {pos, val}
    for(int i = 0; i < m; i++) {
        ll l, r, x; cin >> l >> r >> x;
        l--;
        events[l].push_back({i,x});
        events[r].push_back({i,0});
    }

    int q; cin >> q;
    vector<vector<array<ll,3>>> queries(n);
    for(int i = 0; i < q; i++) {
        ll k, s, t; cin >> k >> s >> t;
        k--;
        s--;
        queries[k].push_back({i,s,t});
    }
    Tree<array<ll,5>> tree(m,{0,0,0,0,0});
    vector<ll> res(q);
    for(int i = 0; i < n; i++) {
        for(pair<ll,ll> event : events[i]) {
            tree.update(event.first,event.second);
        }
        for(array<ll,3> query : queries[i]) {
            array<ll,5> arr = tree.query(query[1],query[2]);
            // cout << "q[0] " << query[0] << '\n';
            // for(ll x : arr) cout << x << " ";
            // cout << '\n';
            if(arr[4] < 0) {
                res[query[0]] = arr[4];
            } else {
                res[query[0]] = arr[2];
            }
        }
    }
    for(ll &x : res) cout << x << '\n';

    return 0;
}