#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
thinking of a way to solve this problem didn't take too long.

First thoughts were trying to binary search the split, but by knowing our desired answer doesn't really help us with queries.

Solution : Fix the split in the array and try to find a way to make both sides as close as possible
We can do this with some sort of binary search where we binary search the number of elements that Monocarp uses and let Polycarp use the remainder. 
We binary search the highest time monocarp can get without exceeded polycarp and vice versa
Just need some sort of DS that stores the sum of the minimum x elements. 
Use some DS to do this.
Sort elements in list and index them based off their sorted order.
Then, we set some of the bits on and off depending on whether they are on the left or right side. we use segtree and find lowest index that has x set bits.
Then, we look at a value segtree and query the sum of the values in that range. 



*/

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

    int findL(int cnt) {
        return _findL(1, 0, size, cnt);
    }

    int _findL(int idx, int curl, int curr, int needed) {
        if(isLeaf(idx)) {
            if(needed) {
                return curr;
            } else {
                return curr - 1;
            }
        }
        int leftsize = v[idx * 2];
        int mid = (curl + curr) / 2;
        if(leftsize >= needed) {
            return _findL(idx * 2, curl, mid, needed);
        } else {
            return _findL(idx * 2 + 1, mid, curr, needed - leftsize);
        }
    }
};

void solve() {
    int n, k; cin >> n >> k;
    vector<array<ll,2>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0];
        a[i][1] = i;
    }

    sort(a.begin(), a.end());

    vector<int> idxs(n);
    for(int i = 0; i < n; i++) {
        idxs[a[i][1]] = i;
    }

    Tree<int> lidxs(n), ridxs(n);
    Tree<ll> lvals(n), rvals(n);
    for(int i = 0; i < n; i++) {
        ridxs.update(i,1);
        rvals.update(i, a[i][0]);
    }

    ll res = LLONG_MAX;
    for(int i = 0; i < n; i++) {
        int rem = idxs[i];
        ll val = a[rem][0];

        lidxs.update(rem,1);
        lvals.update(rem,val);

        ridxs.update(rem,0);
        rvals.update(rem,0LL);

        int leftsize = i + 1;
        int rightsize = n - (i + 1);

        int l = max(0, k - rightsize), r = min(k,i + 1);
        while(l != r) {
            int m = (l + r + 1) / 2;
            int lidx = lidxs.findL(m);
            int ridx = ridxs.findL(k - m);

            ll ltime = lvals.query(0, lidx);
            ll rtime = rvals.query(0, ridx);

            if(ltime <= rtime) {
                l = m;
            } else {
                r = m - 1;
            }
        }

        int lidx = lidxs.findL(l);
        int ridx = ridxs.findL(k - l);

        ll ltime = lvals.query(0, lidx);
        ll rtime = rvals.query(0, ridx);

        // cout << "i : " << i << " l : " << l << " r : " << r << " lidx : " << lidx << " ridx : " << ridx << " ltime : " << ltime << " rtime : " << rtime << '\n';

        res = min(res, max(ltime, rtime));

        l = max(0, k - leftsize), r = min(k,n - (i + 1));

        while(l != r) {
            int m = (l + r + 1) / 2;
            int ridx = ridxs.findL(m);
            int lidx = lidxs.findL(k - m);

            ll ltime = lvals.query(0, lidx);
            ll rtime = rvals.query(0, ridx);

            if(rtime <= ltime) {
                l = m;
            } else {
                r = m - 1;
            }
        }

        ridx = ridxs.findL(l);
        lidx = lidxs.findL(k - l);

        rtime = rvals.query(0, ridx);
        ltime = lvals.query(0, lidx);

        // cout << "i : " << i << " l : " << l << " r : " << r << " lidx : " << lidx << " ridx : " << ridx << " ltime : " << ltime << " rtime : " << rtime << '\n';

        res = min(res, max(ltime, rtime));

    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Tree<int> test(5);
    // test.update(1,1);
    // test.update(3,1);

    // cout << "1 : " << test.findL(1) << '\n';
    // cout << "2 : " << test.findL(2) << '\n';

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}