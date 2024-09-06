#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
Not to tricky to determine the max number of operations. 
However, it can be tricky to determine the min monsters to do operations on so that we can do an operation of type 2 to finish.
We story at each index i, a monster with health >= i. And we try to minimize this sum while maximizing the # of monsters.
Doing Amortized analysis allows us to replace a monster with any monster in its range repeatedly. Like amortized 2 cost to do this apparently

Proof by AC :(

*/

template<typename T>
struct Tree {
    static constexpr T base = {-MOD,-1};
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        if(a[0] > b[0]) {
            return a;
        } else if(a[0] < b[0]) {
            return b;
        } else if(a[1] > b[1]) {
            return a;
        } else {
            return b;
        }
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

void solve() {
    int n; cin >> n;
    Tree<array<int,2>> tree(n);
    for(int i = 0; i < n; i++) {
        tree.update(i,{MOD,i});
    }
    ll sum = 0, in = 0;
    for(int i = 0; i < n; i++) {
        int cur; cin >> cur;

        if(tree.query(0,cur)[0] == MOD) {
            in++;
            sum += cur;
            int idx = tree.query(0,cur)[1];
            // cout << "idx : " << idx << endl;
            tree.update(idx,{cur,idx});
        } else {
            while(1) {
                auto [val, idx] = tree.query(0,cur);
                if(val <= cur) break;
                tree.update(idx, {cur,idx});
                sum += cur;
                sum -= val;
                cur = val;
            }
        }

        cout << sum - in * (in + 1) / 2 << " \n"[i == n - 1];

    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// void solve() {
//     int n; cin >> n;
//     set<int> s;
//     for(int i = 1; i <= n; i++) {
//         s.insert(i);
//     }
//     ll sum = 0;
//     for(int i = 0; i < n; i++) {
//         int a; cin >> a;
//         if(s.upper_bound(a) != s.begin()) {
//             sum += a;
//             s.erase(--s.upper_bound(a));
//         }
//         ll ops = n - s.size();
//         cout << sum - ops * (ops + 1) / 2 << " \n"[i == n - 1];
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }